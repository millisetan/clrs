#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int partition(int a[], int low, int high)
{
	int pivot = a[low];
	int i=low, j=high;
	while (1) {
		while ((i<=j) && (a[i] <= pivot)) ++i;
		while ((j>=i) && (a[j] > pivot)) --j;
		if (i > j) break;
		int tmp = a[i]; a[i] = a[j]; a[j] = tmp;
	}
	a[low] = a[j];
	a[j] = pivot;
	return j;
}

void quicksort(int a[], int low, int high)
{
	if (low >= high) return;
	int mid = partition(a, low, high);
	quicksort(a, low, mid-1);
	quicksort(a, mid+1, high);
}

/*
int main()
{
	int a[] = {3, 1, 2, 8, 4, 5};
	quicksort(a, 0, sizeof(a)/sizeof(int)-1);
	int i;
	for (i=0; i<sizeof(a)/sizeof(int); ++i) {
		printf("%d\n", a[i]);
	}
}
*/

int main()
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
		quicksort(a, 0, size-1);
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
