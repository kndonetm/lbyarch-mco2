#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

//! Change the definition of TEST_SIZE to adjust the size of the vectors created for the benchmark
//! TEST_1_SIZE: 2^20
//! TEST_2_SIZE: 2^24
//! TEST_3_size: 2^29
#define TEST_SIZE TEST_1_SIZE

// 2^20
#define TEST_1_SIZE 1048576  
// 2^24
#define TEST_2_SIZE 16777216
// 2^29S
// not enough ram for 2^30 :( ey it actually loaded XD
#define TEST_3_SIZE 536870912

extern float dotProduct();
extern float asmDotProduct();

void benchmark() {
	time_t previousSeedTime = time(0);
	srand(previousSeedTime);

	double times[30];
	double asmTimes[30];
	double averageTime = 0.0;
	double averageAsmTime = 0.0;
	printf("Iteration   :        C Time |     ASM Time |     C Answer |   ASM Answer\n");
	printf("========================================================================\n");

	for (int iteration = 0; iteration < 30; iteration++) {
		printf("Iteration %02d: ", iteration + 1);
		time_t currentTime = time(0);
		
		// prevent repeating test cases from being generated
		if (currentTime != previousSeedTime) {
			previousSeedTime = currentTime;
			srand(previousSeedTime);
		}

		// alloc arrays for test
		float* a = (float*)malloc(TEST_SIZE * sizeof(float));
		float* b = (float*)malloc(TEST_SIZE * sizeof(float));

		// fill the vectors with random numbers
		for (unsigned long long int i = 0; i < TEST_SIZE; i++) {
			// fill a and b with random numbers between -1 and 1
			a[i] = (float)rand() / (float)(RAND_MAX / 2) - 1.0;
			b[i] = (float)rand() / (float)(RAND_MAX / 2) - 1.0;
		}

		// compute c time
		clock_t timeTaken = clock();
		float sum = dotProduct(a, b, TEST_SIZE);
		timeTaken = clock() - timeTaken;
		times[iteration] = (double)timeTaken / (double)CLOCKS_PER_SEC;

		// compute assembly time
		clock_t asmTimeTaken = clock();
		float asmSum = asmDotProduct(a, b, TEST_SIZE);
		asmTimeTaken = clock() - asmTimeTaken;
		asmTimes[iteration] = (double)asmTimeTaken / (double)CLOCKS_PER_SEC;

		printf(" %12.6lf | %12.6lf | %12.6f | %12.6f \n", times[iteration], asmTimes[iteration], sum, asmSum);

		free(a);
		free(b);
	}

	for (int i = 0; i < 30; i++) {
		averageTime += times[i];
		averageAsmTime += asmTimes[i];
	}
	averageTime /= 30.0;
	averageAsmTime /= 30.0;

	printf("\nAverage time taken\nC: %.6lf\nAsm: %.6lf", averageTime, averageAsmTime);
}

int main() {
	benchmark();

	return 0;

}