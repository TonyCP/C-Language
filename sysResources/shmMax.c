#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/stat.h>


int main(int argc, char* argv[]) {
	int shmid;

	if((shmid = shmget(IPC_PRIVATE, 25267159099, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) {
		perror("I cant.. \n");
		exit(1);
	}

	if(shmctl(shmid, IPC_RMID, 0) < 0){
		perror("cant delete..\n");
		exit(1);
	}
	return 0;
}
