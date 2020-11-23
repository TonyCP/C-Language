/* Time & Math lab */
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

int main()
{
	int i;
	double time_taken;
	clock_t begin, end;
	int num_iter = 100000000;

	// clean screen for prog results //
	system("clear");
	printf("Program is running ... \n\n");


	// Invoke power function <math.h> & time it //
	begin = clock();
	for(i = 0; i < num_iter; i++){
		pow(1000.5, 222.5);
	}

	end = clock();
	time_taken = ((double)(end-begin))/CLOCKS_PER_SEC*1000;
	printf("CPU time to invoke pow() %d times: %.3fms\n", num_iter, time_taken);

	// Invoke square root function <math.h> & time it //
	begin = clock();
	for(i = 0; i < num_iter; i++){
		sqrt(100);
	}

	end = clock();
	time_taken = ((double)(end-begin))/CLOCKS_PER_SEC*1000;
	printf("CPU time to invoke sqrt() %d times: %.3fms\n", num_iter, time_taken);

	return 0;
}
