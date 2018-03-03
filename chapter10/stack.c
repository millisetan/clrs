#include <stdlib.h>
#include <stdio.h>

int max_size;
int *elems;
int top=0;

void overflow()
{
	exit(1);
}

void underflow()
{
	exit(1);
}

int create_stack(int size)
{
	max_size = size;
	elems = malloc(size*sizeof(int));
	return elems != NULL;
}

void destroy_stack()
{
	free(elems);
}

void push(int elem)
{
	if (top >= max_size) overflow();
	elems[top++] = elem;
}

int pop()
{
	if (top == 0) underflow();
	return elems[--top];
}

