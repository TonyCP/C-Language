// Author: Tonae Patterson (22 October 2020)				//
// Project 1 description: (Token-Ring Communication Network)		//
// Write a program that uses multiple processes executing in parallel 	//
// to simulate the operation of the token-ring protocol. The processes  //
// should be organized in a ring configuration, using pipes for         //
// communication and coordination. Signals may be used (depending on 	//
// your design) to coordinate the behavior of processes in the ring.	//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX 1024
#define READ 0
#define WRITE 1
#define CURR 0
#define NEXT 1
#define MAXPROCESS 100

// Function Definition //
void signalHandler(int signal);

// Structure passed process to process via pipes //
struct tokenMsg {
	int dest;
	char msg[MAX];
	int flag;
};

// Global variables //
int numProcesses; // num of processes
int processId = 0; // process id for position
int fd[MAXPROCESS][2]; // process file descriptors
pid_t pid[2]; // keeping track of pid

// Main function //
int main() {
	char *input = (char*)malloc(sizeof(char)*MAX);
	int parentPID = getpid();

	// Install signal handler //
	signal(SIGINT, signalHandler);

	// Prompt user for process # //
	printf("Provide number of processes: ");
	numProcesses = atoi(fgets(input, MAX, stdin));
	if(numProcesses < 2) {
		printf("Invalid process number. Initializing to 3..\n");
		numProcesses = 3;
	}
	printf("Number of processes %d\n", numProcesses);
	
	// This current process //
	pid[CURR] = getpid();
	// Pipe creation for ring //
	int i = 0;
	while(i < numProcesses) {
		printf("Pipe #%d initialized..\n", i);
		if(pipe(fd[i]) < 0) {
			perror("Pipe error");
			exit(1);
		}
		i++;
	}


	i = 0;
	while(i < numProcesses) {
		if((pid[NEXT] = fork()) < 0) {
			printf("Fork error");
			exit(2);
		}
		// If parent, leave loop //
		if(pid[NEXT]) {
			i = numProcesses;
		}
		// If child, stay in loop //
		// If last process link with first process //
		if(!pid[NEXT]) {
			i++;
			processId = i;
			if(i == (numProcesses - 1)) {
				pid[NEXT] = parentPID;
				i = numProcesses;
			}
		}
		
	}

	// Close pipes unrelated to current process //
	int closePipe = 0;
	while(closePipe < numProcesses) {
		// Pipe two nearby //
		if(closePipe == processId || closePipe == (processId+numProcesses-1)%numProcesses) {
			break;
		}
		close(fd[closePipe][READ]);
		close(fd[closePipe][WRITE]);
		closePipe++;
	}

	// Close read (write side) & write (sender side) //
	close(fd[processId][READ]);
	close(fd[(processId+numProcesses-1)%numProcesses][WRITE]);


	// For parent process //
	if(!processId) {
		// Initializing tokenMsg struct //
		struct tokenMsg token;
		token.flag = 0;
		sleep(1);

		// User input -> Message //
		char buffer[MAX];
		printf("Enter Message: ");
		if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
			perror("Failed: user input");
			exit(1);
		}
		strcpy(token.msg, buffer);

		// User input -> Destination //
		char destBuffer[MAX];
		printf("Enter Destination: ");
		if(fgets(destBuffer, sizeof(destBuffer), stdin) == NULL) {
			perror("Failed: user input");
			exit(1);
		}

		//strcpy(token.msg, buffer);
		token.dest = atoi(destBuffer);

		printf("(PID: %d) (Process number: %d) (PPID: %d)\n", getpid(), processId, getppid());

		// Check destination input - self(zero) //
		if(token.dest == processId) {
			sleep(1);
			printf("Token info being cleared.. Ctrl + C to exit safely.\n");
			strcpy(token.msg, "");
			token.dest = -1;
		}

		printf("\tI Wrote: %s", token.msg);
		printf("--------------------------------------------------------------\n");
		// Pass token next process //
		sleep(1);
		token.flag += 1;
		write(fd[processId][WRITE],(struct tokenMsg*) &token, MAX);
		kill(pid[NEXT], SIGUSR1);
	}

	// All processes loop waiting for signal //
	while(1) {
		signal(SIGUSR1, signalHandler);
		pause();
	}

	free(input);
}

// Signal Handling Function //
void signalHandler(int signal) {

	// Signal recieved by process //
	if(signal == SIGUSR1) {
		char buffer[MAX];
		struct tokenMsg *rToken;
		int readPipe = (processId+numProcesses-1)%numProcesses;
		int bufNum = read(fd[readPipe][READ], (struct tokenMsg*) buffer, MAX);
		if(bufNum > MAX) {
			perror("Pipe read error\n");
			exit(1);
		}

		// Token being held by process //
		rToken = (struct tokenMsg*) buffer;
		if(rToken->flag == processId) {
			printf("The token passed to process #%d is PID: %d with CPID %d\n", processId, getpid(), pid[NEXT]);

			// Token destination is root //
			if(rToken->dest == 0) {
				printf("Token info being cleared.. Ctrl + C to exit safely.\n");
				strcpy(rToken->msg, "");
				rToken->dest = -1;

			// Token reached intended destination //
			}else if(rToken->dest == processId) {
				rToken->dest = 0;
				printf("(PID: %d) (Process number: %d) (PPID: %d)\n", getpid(), processId, getppid());
				printf("\tI Read: %s", rToken->msg);
				printf("-------------------------------------------------------------\n");


			}else {
				
				printf("Not for me, passing token.\n");
			}
		}

		sleep(1);
		rToken->flag += 1;

		// Check for last process - set zero //
		if(rToken->flag == numProcesses) {
			rToken->flag = 0;
		}

		// Pass token next process //
		write(fd[processId][WRITE], (struct tokenMsg*) rToken, MAX);
		kill(pid[NEXT], SIGUSR1);
	}

	// Exit signal Ctrl + C //
	if(signal == SIGINT) {
		int status; // child process status

		// Close all pipes //
		int closePipe = 0;
		while(closePipe < numProcesses) {
			close(fd[closePipe][READ]);
			close(fd[closePipe][WRITE]);
			closePipe++;
		}
	
		// Wait for child process //
		wait(&status);
		printf("\nProcess number: %d, shutting down..\n", processId);
		sleep(1);
		exit(0);
	}
	
}



