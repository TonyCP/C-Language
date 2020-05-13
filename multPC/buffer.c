/* Class buffer.c */

#include "buffer.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <semaphore.h>
#include <signal.h>

void *producer(void *param);
void *consumer(void *param);
void signalHandler(int signal);

int itemCount = 0, produced = 0, consumed = 0;
int a, b, c, d;
pthread_mutex_t mutex;
sem_t full, empty;

/* Main Function */
int main(int argc, char *argv[]) {
	if( argc != 3) {
		printf("Error: Must provide 2 arguments\n");
		exit(1);
	}

	int status;
	signal(SIGINT, signalHandler);	
	//  argv[1] = Producer Delay time in milliseconds //
	a = atoi(argv[1]);
	// argv[2] = Consumer Delay time in milliseconds //
	d = atoi(argv[2]);
	// # of producer threads //
	b = 5;
	// # of consumer threads //
	c = 5;

	// Declare consumer / producer threads //
	pthread_t pThread[b];
	pthread_t cThread[c];

	// Initialize //
	srand(time(NULL));
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, BUFF_SIZE);
	sem_init(&full, 0, 0);

	// Create producer threads //
	for(int i = 0; i < b; i++) { 
		if((status = pthread_create(&pThread[i], NULL, producer, 
						NULL)) != 0) {
			fprintf(stderr, "Thread creation error: %s\n",
				       	strerror(status));
			exit(1);
		}
	}
	// Create consumer threads //
	for(int i = 0; i < c; i++) {
		if((status = pthread_create(&cThread[i], NULL, consumer,
						NULL)) != 0) {
			fprintf(stderr, "Thread creation error: %s\n",
				       	strerror(status));
			exit(1);
		}
	
	}

	// Join threads //
	for(int i = 0; i < b; i++) {
		if((status = pthread_join(pThread[i], NULL)) != 0) {
			fprintf(stderr, "Join error %s\n", strerror(status));
			exit(1);
		}
	}
	for(int i = 0; i < c; i++) {
		if((status = pthread_join(cThread[i], NULL)) != 0) {
			fprintf(stderr, "Join error %s\n", strerror(status));
			exit(1);
		}
	}
				

	// De-Initialize //
	sem_destroy(&empty);
	sem_destroy(&full);
	pthread_mutex_destroy(&mutex);
	return 0;
}

/* Consumer & Producer Function */
void *producer(void *param) {
	buff_item item;
	while(1) {
		// sleep for random time //
		sleep(rand() % 5 + 1);
		// Generate random number //
		item = rand();
		if(insert_item(item))
			printf("Error occured\n");
		else
			printf("Thread %ld produced: %d \n", pthread_self(), item);
	}
	pthread_exit(NULL);
}

void *consumer(void *param) {
	buff_item item;
	while(1) {
		// sleep for random time //
		sleep(rand() %5 + 1);
		if(remove_item(&item))
			printf("Error occured\n");
		else
			printf("Thread %ld consumed: %d \n", pthread_self(), item);	
	}
	pthread_exit(NULL);
}


/* Buffer Functions */
int insert_item(buff_item item) {
	int status;
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);

	if(itemCount != BUFF_SIZE) {
		buffer[produced] = item;
		produced = (produced + 1) % BUFF_SIZE;
		itemCount++;
		status = 0;
	}
	else 
		status = -1;

	// Producer Delay converted to milliseconds //
	usleep(a*1000);

	pthread_mutex_unlock(&mutex);
	sem_post(&full);
	return status;
}

int remove_item(buff_item *item) {
	int status;
	sem_wait(&full);
	pthread_mutex_lock(&mutex);

	if(itemCount != 0) {
		*item = buffer[consumed];
		consumed = (consumed + 1) % BUFF_SIZE;
		itemCount--;
		status = 0;
	}
	else
		status = -1;

	// Consumer Delay converted to milliseconds // 
	usleep(d*1000);

	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	return status;
}

/* Signal Handler */
void signalHandler(int signal) {
	if(signal == SIGINT) {
		printf("\n# Produced: %d. # Consumed: %d\n", produced, consumed);
		printf("Exiting..\n");
		exit(0);
	}
}

