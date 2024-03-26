#include <stdio.h>
#include <stddef.h>

float dotProduct(float* a, float* b, size_t size) {
	float sum = 0.0;
	
	for (size_t i = 0; i < size; i++) {
		sum += *a * *b;
		a++;
		b++;
	}

	return sum;
}