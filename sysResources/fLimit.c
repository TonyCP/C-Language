#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>


int main() {
	struct rlimit rl;
	struct rlimit r2;

	getrlimit(RLIMIT_NOFILE, &rl);

	printf("Soft limit: %lld \n", (long long int)rl.rlim_cur);
	printf("Hard limit: %lld \n", (long long int)rl.rlim_max);

	getrlimit(RLIMIT_FSIZE, &r2);
//	printf("Max file size: %lld \n", (long long int)r2.rlim_cur);

	return 0;
}

