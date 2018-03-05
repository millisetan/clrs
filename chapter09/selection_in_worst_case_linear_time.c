#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Item {
        int value, index;
};
struct Item *array;

struct Item _select_nth(struct Item a[], int low, int high, int select_idx);

struct Item medium_of_5(struct Item a[], int low)
{
        struct Item b[3];
        memcpy(b, a+low, sizeof(b));
        int i;
        for (i=0; i<3; ++i) {
                if (a[low+3].value < b[i].value) b[i]=a[low+3];
        }
        for (i=0; i<3; ++i) {
                if (a[low+4].value < b[i].value) b[i]=a[low+4];
        }
        struct Item ret = b[0];
        if (b[1].value > ret.value) ret = b[1];
        if (b[2].value > ret.value) ret = b[2];
        return ret;
}

int select_pivot(struct Item a[], int low, int high)
{
        int size = (high-low)/5 + 1;
        struct Item mediums[size];
        struct Item _mediums[size];
        int i, j=0;
        for (i=low; i<=high; i+=5) {
                if (i+4>high) {
                        _mediums[j] = a[i];
                        mediums[j].value = _mediums[j].value;
                        mediums[j].index = j;
                } else {
                        _mediums[j] = medium_of_5(a, i);
                        mediums[j].value = _mediums[j].value;
                        mediums[j].index = j;
                }
                ++j;
        }
        if (size <= 2) return mediums[0].index;
        return _mediums[_select_nth(mediums, 0, size-1, size/2).index].index;
}
	
int partition(struct Item a[], int low, int high)
{
        
        struct Item k;
        int candidate;
	candidate = select_pivot(a, low, high);
	int pivot = a[candidate].value;
        k = a[candidate]; a[candidate] = a[low]; a[low] = k;
	int i=low, j=high;
	while (1) {
		while ((i<=j) && (a[i].value <= pivot)) ++i;
		while ((i<=j) && (a[j].value > pivot)) --j;
		if (i >= j) break;
		k = a[i]; a[i]=a[j]; a[j]=k;
	}
	k=a[low]; a[low]=a[j]; a[j]=k;
	return j;
}

struct Item _select_nth(struct Item a[], int low, int high, int select_idx)
{
	if (low >= high) return a[low];
	int mid = partition(a, low, high);
	if (mid == select_idx) return a[mid];
	if (mid > select_idx) return _select_nth(a, low, mid-1, select_idx);
	return _select_nth(a, mid+1, high, select_idx);
}

int select_nth(int b[], int low, int high, int select_idx)
{
        array = malloc((high+1)*sizeof(struct Item));
        int i;
        for (i=low; i<=high; ++i) {
                array[i].index = i;
                array[i].value = b[i];
        }
	return _select_nth(array, low, high, select_idx).index;
}

int test1()
{
	int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 20, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 8, 21};
	int idx = select_nth(a, 0, 21, 5);
        printf("%d\n", idx);
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
		int size = rand() % 10000 ? : 1;
		int size_s = size;
		int *a = malloc(sizeof(int)*size);
		int *b = malloc(sizeof(int)*size);
		int i;
		for (i=0; i<size; ++i) {
			a[i] = rand() % 100000;
		}
		memcpy(b, a, sizeof(int)*size);
		int idx = rand() % size;
		int res_idx = select_nth(a, 0, size-1, idx);
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

