#include <stdio.h>
#include <stdlib.h>
#include <string.h>


select_pivot(int a[], int low, int high)
{
	

int partition(int a[], int low, int high)
{
	int candidate = select_pivot(a, low, high);
	int pivot = a[candidate];
	a[candidate] = a[low];
	a[low] = pivot;
	int i=low, j=high, k;
	while (1) {
		while ((i<=j) && (a[i] <= pivot)) ++i;
		while ((i<=j) && (a[j] > pivot)) --j;
		if (i >= j) break;
		k = a[i]; a[i]=a[j]; a[j]=k;
	}
	a[low]=a[j]; a[j]=pivot;
	return j;
}

int select_nth(int a[], int low, int high, int select_idx)
{
	if (low >= high) return low;
	int mid = random_partition(a, low, high);
	if (mid == select_idx) return mid;
	if (mid > select_idx) return select_nth(a, low, mid-1, select_idx);
	return select_nth(a, mid+1, high, select_idx);
}

int test1()
{
	int a[] = {3, 1, 0, 4, 2};
	int b[] = {3, 1, 0, 4, 2};
	int idx = selectn(a, 0, 4, 3);
	printf("%d's least value is %d, index is %d\n", 4, b[idx], idx);
}

int comp (const void * elem1, const void * elem2)
{
	int f = *(int *)elem1;
	int s = *(int *)elem2;
	if (f > s) return 1;
	if (f < s) return -1;
	return 0;
}

int test2()
{
	int loop = 1000;
	while (loop--) {
		int size = rand() % 10 ? : 1;
		int size_s = size;
		int *a = malloc(sizeof(int)*size);
		int *b = malloc(sizeof(int)*size);
		int i;
		for (i=0; i<size; ++i) {
			a[i] = rand() % 100000;
		}
		memcpy(b, a, sizeof(int)*size);
		int idx = rand() % size;
		int res_idx = selectn(a, 0, size-1, idx);
		qsort(b, size, sizeof(int), comp);
		if (a[res_idx] == b[idx]) printf("succeed\n");
		else printf("succeed\n");
		free(a);
		free(b);
	}
}

int main()
{
	test2();
}
