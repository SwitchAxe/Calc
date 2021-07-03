#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
queue* createQueue(int size)
{
	queue* q = (queue*) malloc(sizeof(queue));
	q->used = 0;
	q->size = size;
	q->queue = malloc(size*sizeof(char*));
	return q;
}

void queuePush(queue* q, char* token)
{
	if (q->used == q->size)
	{
		q->size += 10;
		q->queue = realloc(q->queue, q->size*sizeof(char*));
	}
	q->queue[q->used] = token;
	q->used++;
}

char* queuePop(queue* q)
{
	if (q->used == 0)
	{
		return NULL;
	}
	char* ret = q->queue[0];
	for (int i = 1; i < q->used; i++)
	{
		q->queue[i-1] = q->queue[i];
	}
	q->used--;
	return ret;
}

void printQueue(queue* q)
{
	for (int i = 0; i < q->used; i++)
	{
		printf("%d:%s\n", i, q->queue[i]);
	}
}

void freeQueue(queue* q)
{
	free(q->queue);
	free(q);
}
