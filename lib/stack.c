#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
stack* createStack(int len)
{
	stack *stk = (stack*) malloc(sizeof(stack));
	stk->size = len;
	stk->used = 0;
	stk->stack = malloc(len*sizeof(char*));
	stk->stack[0] = NULL;
	return stk;
}

void freeStack(stack* stk)
{
	free(stk->stack);
	free(stk);
}

void stackPush(stack* stk,char*  elem)
{
	if (stk->used+1 == stk->size)
	{
		stk->size += 10;
		stk->stack = realloc(stk->stack, stk->size*sizeof(char*));
	}
	stk->stack[stk->used] = elem;
	stk->used++;
	stk->stack[stk->used] = NULL;
}

// void stackPush(stack* stk, char* elem)
// {
// 	if (stk->used+1 == stk->size)
// 	{
// 		stk->size += 10;
// 		stk->stack = realloc(stk->stack, stk->size*sizeof(char*));
// 	}
// 	//shifting each element to the right by one
// 	for (size_t i = 0; i < stk->used - 1; ++i)
// 		stk->stack[i+1] = stk->stack[i];
// 	stk->stack[0] = elem;
// }


char* stackPop(stack* stk)
{
	if (stk->used == 0)
	{
		return NULL;
	}

	char* r = stk->stack[stk->used-1];
	stk->used--;
	return r;
}

// char* stackPop(stack* stk)
// {
// 	if (stk->used == 0)
// 		return NULL;
// 	char* r = stk->stack[0];
// 	for (int i = 1; i < stk->used; ++i)
// 	{
// 		stk->stack[i-1] = stk->stack[i];
// 	}
// 	return r;
// }

void printStack(stack* stk)
{
	for (int i = 0; i < stk->used; i++)
	{
		printf("%d:%s\n", i,  stk->stack[i]);
	}
}

