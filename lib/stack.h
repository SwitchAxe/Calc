#ifndef STACK_H
	#define STACK_H
	typedef struct
	{
		int used; 
		int size;
		char **stack;
	} stack;
	
	stack* createStack(int len);
	void freeStack(stack* stk);
	void stackPush(stack* stk, char* elem);
	char* stackPop(stack* stk);
	void printStack(stack* stk);
#endif 
