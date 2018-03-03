#include <stdlib.h>
#include <stdio.h>

int max_size;
int *elems;
int head=0, end=0;

void overflow()
{
	printf("oops! overflow\n");
	exit(1);
}

void underflow()
{
	printf("oops! underflow\n");
	exit(1);
}

int create_queue(int size)
{
	max_size = size;
	elems = malloc(size*sizeof(int));
	return elems != NULL;
}

void destroy_stack()
{
	free(elems);
}

void enqueue(int elem)
{
	if (((head+max_size-end) % max_size) == 1) overflow();
	elems[end++] = elem;
	end = (end) % max_size;
}

int dequeue()
{
	if (end == head) underflow();
	if (head == max_size) {
		head = 0;
		return elems[max_size];
	}
	return elems[++head];
}

int main()
{
	create_queue(4);
	int i;
	enqueue(0);
	enqueue(1);
	enqueue(2);
	dequeue();
	dequeue();
	enqueue(4);
	enqueue(0);
	//enqueue(1);
}

