/****************************************************************
 * Programmming Assignment
 * Lab 5: The Reader(s)
 *
 * @author Tonae Patterson
 * *************************************************************/
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Shared memory segment size //
#define SHM_SIZE 4096

// Signal Handler //
void signalHandler(int);

// Shared Data Handling //
int shmId, input = 1;
char *shmPtr;
key_t shmKey;

typedef struct {
	int turn, count;
	char message[1024];
} sharedData;


// Main Function //
int main() {
	sharedData data;
	data.turn = 0;
	signal(SIGINT, signalHandler);

	// Shared system key //
	shmKey = ftok(".", 1);

	// Call shmget w/o IPC_CREAT flag //
	if((shmId = shmget(shmKey, SHM_SIZE, S_IRUSR|S_IWUSR)) < 0 ) {
		perror("Cant create shared memory..\n");
		exit(1);
	}

	// Attach shared memory //
	if((shmPtr = shmat(shmId, 0, 0)) == (void *)-1) {
		perror("Cant attach.. \n");
		exit(1);
	}

	
	while(input) {
		// Check for reader(s) turn //
		while(!data.turn) {
			memcpy(&data, shmPtr, sizeof(sharedData));
		}

		// Critical section //
		data.count++;
		sleep(1);
		fprintf(stderr, "Read from shared memory: %s\n", data.message);
		sleep(1);

		data.count--;
		while(data.count > 0) { ; }

		if(strncmp(data.message, "quit", 4) == 0) {
			input = 0;
		}

		data.turn = 0;
		memcpy(shmPtr, &data, sizeof(sharedData));

	};

	// Deallocate//
	if(shmctl(shmId, IPC_RMID, NULL) < 0) {
		perror("Cant deallocate..\n");
		
	}

	return 0;
}


// Singal Handler Function //
void signalHandler(int signal) {
	printf("Interrupt signal received\n");

	// Deallocate shared memory //
	if(shmctl(shmId, IPC_RMID, NULL) < 0) {
		perror("Cant deallocate..\n");
		exit(1);
	}

	// Exit Success //
	exit(0);
}

