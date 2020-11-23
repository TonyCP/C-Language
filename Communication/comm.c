#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
/* Program using linux signal handler functions 
 * Directions: Compile and run two seperate programs */

void signal_handler(int);

int main() {
	pid_t parent = getpid();
	pid_t child = fork();
	int status;

	// Install user-defined signals //
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	signal(SIGINT, signal_handler);


	// Child creation error checking //
	if ( child  < 0 ) {
		perror("forked failed... exiting");
		exit(1); 

	// Parent process //
	} else if( !child ) {
		printf("waiting...	");
		fflush(stdout);
		pause();
	//	while(1) {
	//		printf("waiting...	");
	//		fflush(stdout);
	//		pause();
	//	}
	//	waitpid(-1, &status, 0);
		
	// Child creation success //
	} else {
		int sigs[2] = {SIGUSR1, SIGUSR2};
		srand(time(0));

		// First print statement - child PID //
		printf("Spawned child PID# %d \n", getpid());

		while(1) {
			int randIndex = rand() % 2;
			int randTime = rand() % 5 + 1;
			// sleep for rand seconds //
			sleep(randTime);
			// send parent signal //
			kill(parent, sigs[randIndex]);
		}
	}

	return 0;
}

// Signal control - reports type sent //
void signal_handler(int sigNum) {

	if (sigNum == SIGUSR1) {
		// Display signal recieved //
		printf("received a SIGUSR1 signal\n");
	}

	else if (sigNum == SIGUSR2) {
		// Display signal recieved //
		printf("received a SIGUSR2 signal\n");
	}

	else if (sigNum == SIGINT) {
		// Display signal recieved //
		printf("^C receieved. \n");
		sleep(1);
	 	printf("That's it, Im shutting you down...\n");
		exit(0);
	}

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);	
}
