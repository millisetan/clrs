#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int get_radix(int val, int radix)
{
	while (radix--) val /= 10;
	return val % 10;
}

void stable_sort(int a[], int size, int radix)
{
	int k = 9;
	int *b = calloc(k+1, sizeof(int));
	int *c = malloc(sizeof(int)*size);
	memcpy(c, a, sizeof(int)*size);
	int i;
	for (i=0; i<=k; ++i) {
		b[i] = 0;
	}
	for (i=0; i<size; ++i) {
		++b[get_radix(c[i], radix)];
	}
	for (i=1; i<=k; ++i) {
		b[i] += b[i-1];
	}
	for (i=size-1; i>=0; --i) {
		a[--b[get_radix(c[i], radix)]] = c[i];
	}
	free(c);
	free(b);
}

int radix_sort(int a[], int size, int max_radix)
{
	int radix = 0;
	do {
		stable_sort(a, size, radix);
	} while (++radix <= max_radix);
}

int test1()
{
	int a[] = {5211, 95368, 2567, 56429, 65782, 21530, 22862};
	radix_sort(a, sizeof(a)/sizeof(int), 7);
	int i;
	for (i=0; i<sizeof(a)/sizeof(int); ++i) {
		printf("%d\n", a[i]);
	}
}

int test2()
{
	int loop = 1000;
	while (loop--) {
		int size = rand() % 10 + 1;
		int size_s = size;
		int *a = malloc(sizeof(int)*size);
		int i;
		for (i=0; i<size; ++i) {
			a[i] = rand() % 100000;
			printf("a[%d]: %d\n", i, a[i]);
		}
		radix_sort(a, size, 7);
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
