#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void merge(int a[], int low, int mid, int high)
{
	int *b = malloc(sizeof(int) * (high - low + 1));
	int i=low, j=mid+1, k=0;
	while (1) {
		if (i > mid) {
			while (j <= high) b[k++] = a[j++];
			break;
		}
		if (j > high) {
			while (i <= mid) b[k++] = a[i++];
			break;
		}
		if (a[i] <= a[j]) {
			b[k++] = a[i++];
		} else {
			b[k++] = a[j++];
		}
	}
	memcpy(a+low, b, sizeof(int) * (high - low + 1));
	free(b);
}

void merge_sort(int a[], int low, int high)
{
	if (low >= high)
		return;
	int mid = (low + high)/2;
	merge_sort(a, low, mid);
	merge_sort(a, mid+1, high);
	merge(a, low, mid, high);
}

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
		merge_sort(a, 0, size-1);
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

