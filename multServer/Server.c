/***************************************************************
 * CIS452 LAB04
 * @Author Tonae Patterson
 * Description: This program will simulate a multi-threaded
 * file server.
 * ************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

#define MAX 100

// Prototypes //
void *worker(void *arg);
void signalHandler(int signal);

// Global variables //
int f_requested = 0;
int threadsServed = 0;

// Main Function //
int main() {

	// Local variables //
	int status;
	char buffer[256];
	pthread_t thread;
	signal(SIGINT, signalHandler);

	char *fileInp = buffer;

	// Dispatch thread //
	while(1) {
		printf("Please enter filename: ");
		fgets(buffer, MAX, stdin);

		// Spawn child thread //
		if((status = pthread_create(&thread, NULL, worker, 
						(void*)fileInp)) != 0) {
			fprintf(stderr, "Thread creation error %d: %s\n", 
					status, strerror(status));
			exit(1);
		}
		f_requested++;
	}
	return 0;
}

// Worker Thread Functionality //
void *worker(void *arg) {
	char *fstring = malloc(strlen( (char*) arg)+1);
	strcpy(fstring, (char*)arg);
	srand(time(NULL));

	// 80/20 probablity //
	int random = (rand() % 10) + 1;
	if(random < 8) {
		sleep(1);
	} else {
		random = (rand() % 4) + 7;
		sleep(random);
	}

	printf("\nName of file accessed: : %s\n", fstring);
	threadsServed++;

	free(fstring);
	return NULL;
}


// Signal Handler //
void signalHandler(int signal) {

	// Interrupt handling //
	if(signal == SIGINT) {
		// Statistics //
		printf("\nTotal # of file requests received: %d\n", 
				f_requested);
		sleep(1);
		printf("Exiting...\n");
		exit(0);
	}
}






