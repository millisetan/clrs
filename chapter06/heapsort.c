#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

void relax(int a[], int size, int idx)
{
	do {
		int min_idx = idx, left_idx = 2*idx, right_idx=left_idx+1;
		if ((left_idx <= size) && (a[min_idx-1] > a[left_idx -1])) {
			min_idx = left_idx;
		}
		if ((right_idx <= size) && (a[min_idx-1] > a[right_idx-1])){
			min_idx = right_idx;
		}
		if (min_idx == idx)
			break;
		int tmp = a[idx-1];
		a[idx-1]=a[min_idx-1];
		a[min_idx-1]=tmp;
		idx = min_idx;
	} while (1);
}

void build_heap(int a[], int size)
{
	int cur_idx = size/2;
	while (cur_idx) {
		relax(a, size, cur_idx);
		cur_idx--;
	}
}

void heapsort(int a[], int size)
{
	int *b = malloc(sizeof(int)*size);
	memcpy(b, a, sizeof(int)*size);
	int i=0;
	build_heap(b, size);
	do {
		a[i++] = b[0];
		b[0] = b[--size];
		relax(b, size, 1);
	} while (size);
	free(b);
}

int test1()
{
	int a[] = {3, 1, 2, 8, 4, 5};
	heapsort(a, sizeof(a)/sizeof(int));
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
		}
		heapsort(a, size);
		while (--size) {
			if (a[size] < a[size-1]) {
				printf("size:%d, failed\n", size);
				break;
			}
		}
		printf("size:%d, succeed\n", size_s);

	}
}

int main()
{
	test2();
}
