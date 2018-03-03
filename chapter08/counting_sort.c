#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//any x in a, x <= k.
void counting_sort(int a[], int size, int k)
{
	int *b = calloc(k+1, sizeof(int));
	int *c = malloc(sizeof(int)*size);
	memcpy(c, a, sizeof(int)*size);
	int i;
	for (i=0; i<size; ++i) {
		++b[c[i]];
	}
	for (i=1; i<=k; ++i) {
		b[i] += b[i-1];
	}
	for (i=size-1; i>=0; --i) {
		a[--b[c[i]]] = c[i];
	}
	free(b);
	free(c);
}

int test1()
{
	int a[] = {3, 1, 2, 8, 4, 5};
	counting_sort(a, sizeof(a)/sizeof(int), 10);
	int i;
	for (i=0; i<sizeof(a)/sizeof(int); ++i) {
		printf("%d\n", a[i]);
	}
}

int test2()
{
	int loop = 1000;
	while (loop--) {
		int size = rand() % 10000 + 1;
		int size_s = size;
		int *a = malloc(sizeof(int)*size);
		int i;
		for (i=0; i<size; ++i) {
			a[i] = rand() % 100000;
			if (!i) printf("%d\n", a[0]);
		}
		counting_sort(a, size, 100000);
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
