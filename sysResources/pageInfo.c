#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/resource.h>
#include <time.h>
#include <sys/sysinfo.h>
#include <stdlib.h>

// Main functions //
int main(int argc, char const *argv[]) {
	
	// Page size (bytes) //
	long pSize = sysconf(_SC_PAGESIZE);
	printf("%ld \n", pSize);

	// # of physical pages //
	long numPages = sysconf(_SC_PHYS_PAGES);
	printf("%lu \n", numPages);

	// Max num of processes per user //
	printf("%ld \n", sysconf(_SC_CHILD_MAX));
	return 0;
}
