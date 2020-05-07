#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <wait.h>
#include <ctype.h>
#include <unistd.h>

#define INP_BUFF_SZ 256

int main(int argc, char* argv[]) 
{
	char buffer[INP_BUFF_SZ];
	char src[255];
	char dest[15];
	int word = 0;
	int status = 0;
	long prevSec = 0;
	long prevUsec = 0;
	long prevSwitch = 0;
	struct rusage ru;


	// Welcome user //
	printf("Welcome to Simple Shell!\n");
	
	while(1) {

		// Prompt user for input //
		printf("Input command or 'quit' to exit: ");

		// Get and parse user input //
		fgets(buffer, INP_BUFF_SZ, stdin);

		// Trim whitespace for buffer comparison //
		buffer[strcspn(buffer, "\n")] = 0;

		// Continue program if no input //
		if(strlen(buffer) <= 0) {
			continue;
		}

		// Check for user exit //
		if(strcmp(buffer, "quit") == 0) {
			puts("Exiting program..");
			break;
		}

	
		// Count number of tokens in user input //
		char temp[strlen(buffer)];
		for(int i = 0; i < strlen(buffer); i++) {
			temp[i] = buffer[i];
		}

		// Tokenize input string //
		char *vector = strtok(temp, " ");
		while(vector != NULL) {
			word++;
			vector = strtok(NULL, " ");
		}

		char *args[word];
		char *command = strtok(buffer, " ");
		args[0] = command; // User input command 
		
		for(int i = 1; i < word; i++) {
			args[i] = strtok(NULL, " ");
		}
		args[word] = NULL;


		// Create child process //
		pid_t child_pid = fork();

		// Error code  //
		if(child_pid < 0) {

			perror("Fork failure");
			exit(1);
		
		// Child code //
		} else if(child_pid == 0) {

			if(execvp(command, args) < 0){
				strcpy(src, command);
				strcpy(dest, "\nSimpleShell: ");
				strcat(dest, src);
				perror(dest);
				exit(1);

			}else {
				exit(0);
			}
		
		// Parent code //
		} else {


			// Resource usage statistics //
			child_pid = wait(&status);
			if(getrusage(RUSAGE_CHILDREN, &ru) < 0) {
				printf("Unable to return resource usage stats\n");
			} else {
				printf("\nUser CPU time used:\t\t%ld seconds, %ld mircroseconds\n", ru.ru_utime.tv_sec - prevSec, ru.ru_utime.tv_usec - prevUsec);
				printf("Involuntary context switches:\t%ld\n\n",ru.ru_nivcsw - prevSwitch);

				prevSec = ru.ru_utime.tv_sec;
				prevUsec = ru.ru_utime.tv_sec;
				prevSwitch = ru.ru_nivcsw;
			}
		}
	}
	return 0;
}


		
	










