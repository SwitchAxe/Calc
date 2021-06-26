#ifndef QUEUE_H
	#define QUEUE_H
	typedef struct
	{
		int used;
		int size;
		char** queue;
	} queue;

	queue* createQueue(int size);
	void queuePush(queue* q, char* token);
	char* queuePop(queue* q);
	void printQueue(queue* q);
	void freeQueue(queue* q);
#endif
