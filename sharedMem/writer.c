/****************************************************************
 * Programming Assignment
 * Lab 5: Writer class
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

// Shared memory segment size//
#define SHM_SIZE 4096

// Signal handler //
void signalHandler(int);

// Data handling //
int shmId, input = 1;
char *shmPtr;
key_t shmKey;

typedef struct {
	int turn, count;
	char message[1024];
} sharedData;

// Main function //
int main() {
	sharedData data;
	data.turn = 0;
	data.count = 0;
	signal(SIGINT, signalHandler);

	// Shared memory key //
	shmKey = ftok(".", 1);

	// Create shared memory segment //
	if((shmId = shmget(shmKey, SHM_SIZE, IPC_CREAT|S_IRUSR|S_IWUSR))
			< 0) {
		perror("Cant create shared memory..\n");
		exit(1);
	}

	// Attatch shared memory //
	if((shmPtr = shmat(shmId, 0, 0)) == (void *)-1) {
		perror("Cant attach..\n");
		exit(1);
	}

	while(input) {
		// Check for writer turn //
		while(data.turn) {
			memcpy(&data, shmPtr, sizeof(sharedData));
		}

		// Critical section //
		printf("Enter message now: ");
		fgets(data.message, 1024, stdin);

		if(strncmp(data.message, "quit", 4) == 0 ){
			input = 0;
		}


		// Exit CS //
		printf("Written to memory: %s", data.message);
		data.turn = 1;
		memcpy(shmPtr, &data, sizeof(sharedData));

	};

	// Deatch on quit //
	if(shmdt(shmPtr) < 0) {
		perror("Cant detach..\n");
		exit(1);
	}

	return 0;
}

// Signal Handler Function //
void signalHandler(int signal) {
	printf("Interrupt signal received..\n");

	// Detach shared memory //
	if(shmdt(shmPtr) < 0) {
		perror("Cant detach..\n");
		exit(1);
	}

	// Exit Success //
	exit(0);
}


