#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp (const void * elem1, const void * elem2) {
	double f = *(double *)elem1;
	double s = *(double *)elem2;
	if (f > s) return 1;
	if (f < s) return -1;
	return 0;
}

//any k in a, 0<=k<1;
void bucket_sort(double a[], int size)
{
	int bucket_size[size];
	double *bucket[size];
	double b[size];
	int i;
	for (i=0; i<size; ++i) {
		bucket_size[i] = 0;
	}
	for (i=0; i<size; ++i) {
		++bucket_size[(int)(a[i]*size) / size];
	}
	for (i=0; i<size; ++i) {
		if (i == 0) {
			bucket[0] = b;
		} else {
			bucket[i] = bucket[i-1] + bucket_size[i-1];
		}
	}
	memset(bucket_size, 0, sizeof(bucket_size));
	for (i=0; i<size; ++i) {
		bucket[(int)(a[i]*size) / size][bucket_size[(int)(a[i]*size) / size]++] = a[i];
	}
	for (i=0; i<size; ++i) {
		qsort(bucket[i], bucket_size[i], sizeof(double), comp);
	}
	memcpy(a, b, sizeof(b));
}
		
int test1()
{
	double a[] = {3.7, 3.5, 2.3, 8.6, 4.2, 5.7, 1.2, 1.1, 9.8, 6.7};
	bucket_sort(a, sizeof(a)/sizeof(double));
	int i;
	for (i=0; i<sizeof(a)/sizeof(double); ++i) {
		printf("%f\n", a[i]);
	}
}

int test2()
{
	int loop = 1000;
	while (loop--) {
		int size = rand() % 10000 + 1;
		int size_s = size;
		double *a = malloc(sizeof(double)*size);
		int i;
		for (i=0; i<size; ++i) {
			a[i] = rand() % 100000 * 1.0 / 100000;
		}
		bucket_sort(a, size);
		while (--size) {
			if (a[size] < a[size-1]) {
				printf("size:%d, failed\n", size);
				break;
			}
		}
		printf("size:%d, succeed\n", size_s);
		free(a);
	}
}

int main()
{
	test2();
}
