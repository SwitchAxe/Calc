#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "calc.h"
#include "stack.h"
#include "queue.h"
#define NEW_TOKEN mati++; matj = 0; m[mati][matj] = str[i]
#define EXT_TOKEN matj++; m[mati][matj] = str[i]
#define TOK_ERROR \
for (int i = 0; i < MAX_LINE_LEN; i++)\
{ \
	free(m[i]); \
} \
free(m); \
return NULL
/*
	the above macro equals to
	for (...)
		free(m[i]);
	free(m)

*/


char* removeNewline(char* string)
{
	char* rmstr = malloc((strlen(string)+1)*sizeof(char));
	if(string == NULL)
	{
		return NULL;
	}

	for (size_t i = 0; i < strlen(string); i++)
	{
		if (string[i] == '\n')
		{
			rmstr[i] = '\0';
			break;
		}
		else
		{
			rmstr[i] = string[i];
		}
	}

   return rmstr;
}

char* removeWhitespaces(char* string)
{
	char* str = (char*) malloc((strlen(string)+1)*sizeof(char));

	if (string == NULL)
	{
		return NULL;
	}

	int write = 0; //writing index
	for (int read = 0; string[read] != '\0'; read++)
	{
		if (string[read] == ' ')
		{
			continue;
		}
		str[write] = string[read];
		write++;
	}
	str[write] = '\0';
	return str;
}


	// tokenize algorithm concept <<<
	      // if ( then check last type
	      //      if last nothing  then new token
	      //      if last operator then new token
	      //      if last opening  then new token
	      //      if last closing  then ERROR
	      //      if last number   then ERROR
	      //      if last sign     then new token
	      //      if last fpoint   then ERROR
	      // if ) then check last type
	      //      if last nothing  then ERROR
	      //      if last operator then ERROR
	      //      if last opening  then ERROR
	      //      if last closing  then new token
	      //      if last number   then new token
	      //      if last sign     then ERROR
	      //      if last fpoint   then ERROR
	      // if /* then check last type
	      //      if last nothing  then ERROR
	      //      if last operator then ERROR
	      //      if last opening  then ERROR
	      //      if last closing  then new token
	      //      if last number   then new token
	      //      if last sign     then ERROR
	      //      if last fpoint   then ERROR
	      // if -+ then check last type
	      //      if last nothing  then this is sign of new number, set fpoint flag false
	      //      if last operator then this is sign of new number, set fpoint flag false
	      //      if last opening  then this is sign of new number, set fpoint flag false
	      //      if last closing  then this is an operator
	      //      if last number   then this is an operator
	      //      if last sign     then ERROR
	      //      if last fpoint   then ERROR
	      // if 0-9 then check last type
	      //      if last nothing  then number means new number, set fpoint flag false
	      //      if last operator then number means new number, set fpoint flag false
	      //      if last opening  then number means new number, set fpoint flag false
	      //      if last closing  then ERROR
	      //      if last number   then extend number token
	      //      if last sign     then extend number token
	      //      if last fpoint   then extend number token
	      // if . then check last type
	      //      if last nothing  then ERROR
	      //      if last operator then ERROR
	      //      if last opening  then ERROR
	      //      if last closing  then ERROR
	      //      if last number   then check fpoint flag
	      //            if fpoint flag true  then ERROR
	      //            if fpoint flag false then extend number, set fpoint flag true
	      //      if last sign     then ERROR
	      //      if last fpoint   then ERROR
	      //      >>>

enum types
{
	t_fpoint,
	t_digit,
	t_opening,
	t_closing,
	t_operator,
	t_sign,
	t_nothing
};

char** tokenize(char* Exp)
{
	if (Exp == NULL) { return NULL; }
	int mati = -1;
	int matj = 0;
	bool fpointFlag = false;
	enum types lastType = t_nothing;
	char** m = (char**) malloc(MAX_LINE_LEN*sizeof(int*));
	for (int i = 0; i < MAX_LINE_LEN; i++)
	{
		m[i] = (char*) malloc(MAX_LINE_LEN*sizeof(int));
	}
	char* str = removeWhitespaces(Exp);

	for (int i = 0; str[i] != '\0'; i++)
	{

		if (str[i] == '(')
		{
			switch(lastType)
			{
				case t_fpoint:   TOK_ERROR;  break;
				case t_digit:    TOK_ERROR;  break;
				case t_opening:  NEW_TOKEN;  break;
				case t_closing:  TOK_ERROR;  break;
				case t_operator: NEW_TOKEN;  break;
				case t_sign:     NEW_TOKEN;  break;
				case t_nothing:  NEW_TOKEN;  break;
				default:         TOK_ERROR;  break;
			}
			lastType = t_opening;
		}
		else if (str[i] == ')')
		{
			switch(lastType)
			{
				case t_fpoint:   TOK_ERROR;  break;
				case t_digit:    NEW_TOKEN;  break;
				case t_opening:  TOK_ERROR;  break;
				case t_closing:  NEW_TOKEN;  break;
				case t_operator: TOK_ERROR;  break;
				case t_sign:     TOK_ERROR;  break;
				case t_nothing:  TOK_ERROR;  break;
				default:         TOK_ERROR;  break;
			}
			lastType = t_closing;
		}
		else if ((str[i] == '/') || (str[i] == '*'))
		{
			switch (lastType)
			{
				case t_fpoint:   TOK_ERROR;  break;
				case t_digit:  	 NEW_TOKEN;	 break;
				case t_opening:  TOK_ERROR;	 break;
				case t_closing:	 NEW_TOKEN;	 break;
				case t_operator: TOK_ERROR;	 break;
				case t_sign:	 TOK_ERROR;	 break;
				case t_nothing:	 TOK_ERROR;	 break;
				default: 		 TOK_ERROR;  break;
			}
			lastType = t_operator;
		}
		else if ((str[i] == '+') || (str[i] == '-'))
		{
			switch (lastType)
			{
				case t_fpoint:    TOK_ERROR; 						 break;
				case t_digit:     NEW_TOKEN; lastType = t_operator;  break;
				case t_opening:   NEW_TOKEN;
								  fpointFlag = false;
								  lastType = t_sign;
								  break;
				case t_closing:   NEW_TOKEN; lastType = t_operator;  break;
				case t_operator:  NEW_TOKEN;
								  fpointFlag = false;
								  lastType = t_sign;
								  break;
				case t_sign:      TOK_ERROR; 					     break;
				case t_nothing:   NEW_TOKEN;
								  fpointFlag = false;
								  lastType = t_sign;
								  break;
				default:          TOK_ERROR; 						 break;
			}
		}
		else if (isdigit(str[i]))
		{
			switch(lastType)
			{
				case t_fpoint:   EXT_TOKEN;  break;
				case t_digit:    EXT_TOKEN;  break;
				case t_opening:  NEW_TOKEN;
							     fpointFlag = false;
								 break;
				case t_closing:	 TOK_ERROR;  break;
				case t_operator: NEW_TOKEN;
								 fpointFlag = false;
								 break;
				case t_sign:     EXT_TOKEN;  break;
				case t_nothing:  NEW_TOKEN;
								 fpointFlag = false;
								 break;
			}
			lastType = t_digit;
		}
		else if (str[i] == '.')
		{
			switch (lastType)
			{
				case t_fpoint:  TOK_ERROR;   break;
				case t_digit:
								if (fpointFlag)
								{
									TOK_ERROR;
								}
								else
								{
									fpointFlag = true;
									EXT_TOKEN;
								}
							 	break;
				case t_opening:  TOK_ERROR;  break;
				case t_closing:	 TOK_ERROR;  break;
				case t_operator: TOK_ERROR;  break;
				case t_sign:     TOK_ERROR;  break;
				case t_nothing:  TOK_ERROR;  break;
			}
		}

	}
	m[++mati] = NULL;
	return m;
}
int calcPrecedence(char operator)
{
	switch(operator)
	{
		case '-':
			return 1;
		case '+':
			return 2;
		case '/':
			return 3;
		case '*':
			return 4;
		default:
			return 0;
	}
}

bool isOperator(char* c)
{
	char* endptr;
	strtol(c, &endptr, 10);
	if (c == NULL) { return false; }
	if (endptr != c) { return false; }


	switch (c[0])
	{
	case '*':
	case '/':
	case '+':
	case '-':
		return true;
	default:
		return false;
	}
}

queue* no_resort(char** tokens)
{
/*	while there are tokens to be read:
	    read a token.
	    if the token is a number, then:
	        push it to the output queue.
	    else if the token is an operator then:
	        while ((there is an operator at the top of the operator stack)
	              and ((the operator at the top of the operator stack has greater precedence)
	                  or (the operator at the top of the operator stack has equal precedence and the token is left associative))
	              and (the operator at the top of the operator stack is not a left parenthesis)):
	            pop operators from the operator stack onto the output queue.
	        push it onto the operator stack.
	    else if the token is a left parenthesis (i.e. "("), then:
	        push it onto the operator stack.
	    else if the token is a right parenthesis (i.e. ")"), then:
	        while the operator at the top of the operator stack is not a left parenthesis:
	            pop the operator from the operator stack onto the output queue.
	        // If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. //
	        if there is a left parenthesis at the top of the operator stack, then:
	            pop the operator from the operator stack and discard it
	        if there is a function token at the top of the operator stack, then:
	            pop the function from the operator stack onto the output queue.
	// After while loop, if operator stack not null, pop everything to output queue //
	if there are no more tokens to read then:
	    while there are still operator tokens on the stack:
	        // If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. //
	        pop the operator from the operator stack onto the output queue.
	exit. */
	stack* stk = createStack(256);
	queue* q = createQueue(256);
	int i = 0;
	char* endptr;
	while (tokens[i] != NULL)
	{
		// if (stk->used == 0)
		// {
		// 	int i = 0;
		// 	while (tokens[i] != NULL)
		// 	{
		// 		if (isOperator(tokens[i]))
		// 		{
		// 			stackPush(stk, tokens[i]);
		// 			break;
		// 		}
		// 		i++;
		// 	}
		// }

		strtold(tokens[i], &endptr);
		if (endptr != tokens[i])
		{
			queuePush(q, tokens[i]);
		}
		else if (isOperator(tokens[i]))
		{
			while (stk->used > 0 &&
				   (stk->stack[stk->used-1] != NULL)  &&
				   (calcPrecedence(stk->stack[stk->used-1][0]) >
				   calcPrecedence(tokens[i][0])) &&
				   (stk->stack[stk->used-1][0] != '('))
			{
				queuePush(q, stackPop(stk));
			}
			stackPush(stk, tokens[i]);
		}
		else if (!strcmp(tokens[i], "("))
		{
			stackPush(stk, tokens[i]);
		}
		else if (!strcmp(tokens[i], ")"))
		{
			while (strcmp(stk->stack[stk->used-1], "("))
			{
				queuePush(q, stackPop(stk));
			}
			if (!strcmp(stk->stack[stk->used-1], "("))
			{
				stackPop(stk);
			}
		}
		i++;
	}
	stackPop(stk);
	for (int e = stk->used;e --> 0;)
	{
		queuePush(q, stackPop(stk));
	}
	freeStack(stk);
	return q;
}

// resort <<<
queue* resort(char** tokens)
{
	/*
	while there are tokens to be read:
	read a token.
	if the token is a number, then:
	push it to the output queue.
	else if the token is an operator then:
	while ((there is an operator at the top of the operator stack)
	and ((the operator at the top of the operator stack has greater precedence)
	or (the operator at the top of the operator stack has equal precedence and the token is left associative))
	and (the operator at the top of the operator stack is not a left parenthesis)):
	pop operators from the operator stack onto the output queue.
	push it onto the operator stack.
	else if the token is a left parenthesis (i.e. "("), then:
	push it onto the operator stack.
	else if the token is a right parenthesis (i.e. ")"), then:
	while the operator at the top of the operator stack is not a left parenthesis:
	pop the operator from the operator stack onto the output queue.
	// If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. //
	if there is a left parenthesis at the top of the operator stack, then:
	pop the operator from the operator stack and discard it
	if there is a function token at the top of the operator stack, then:
	pop the function from the operator stack onto the output queue.

	// After while loop, if operator stack not null, pop everything to output queue //
	while there are still operator tokens on the stack:
	// If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. //
	pop the operator from the operator stack onto the output queue.
	*/

	stack* stk = createStack(256);
	queue* q = createQueue(256);

	int i = 0;
	char* endptr;

	while (tokens[i] != NULL) // while there are tokens to be read <<<
	{
		/* if (stk->used == 0) */
		/* { */
		/*    int i = 0; */
		/*    while (tokens[i] != NULL) */
		/*    { */
		/*       if (isOperator(tokens[i])) */
		/*       { */
		/*          stackPush(stk, tokens[i]); */
		/*          break; */
		/*       } */
		/*       i++; */
		/*    } */
		/* } */

		strtold(tokens[i], &endptr); // read a token
		if (endptr != tokens[i]) // if the token is a number <<<
		{
			queuePush(q, tokens[i]);
		} // >>>
		else if (isOperator(tokens[i])) // if the token is an operator <<<
		{
			while (stk->used > 0 &&
				  (stk->stack[stk->used-1] != NULL)  &&
				  (calcPrecedence(stk->stack[stk->used-1][0]) >
				  calcPrecedence(tokens[i][0])) &&
				  (stk->stack[stk->used-1][0] != '('))
			{
				queuePush(q, stackPop(stk)); // pop operators from the operator stack onto the output queue
			}
			stackPush(stk, tokens[i]); // push it onto the operator stack
		} // >>>
		else if (!strcmp(tokens[i], "(")) // if the token is a left parenthesis <<<
		{
			stackPush(stk, tokens[i]); // push it onto the operator stack
		} /// >>>
		else if (!strcmp(tokens[i], ")")) // if the token is a right parenthesis
		{
			while (strcmp(stk->stack[stk->used-1], "(")) // while the operator at the top of the operator stack is not a left parenthesis
			{
				queuePush(q, stackPop(stk)); // pop the operator from the operator stack onto the output queue
			}
			if (!strcmp(stk->stack[stk->used-1], "(")) // if there is a left parenthesis at the top of the operator stack
			{
				stackPop(stk); // pop the operator from the operator stack and discard it
			}
			/* if (stk->stack[stk->used-1] != NULL) */
			/* { */
			/*    queuePush(q, stackPop(stk)); */
			/* } */
		}
		i++;
	} // >>>

	/* stackPop(stk); */

	for(int e = stk->used;e --> 0;)
	{
		queuePush(q, stackPop(stk));
	}
	freeStack(stk);

	return q;
} // >>>

long double calc(queue* q)
{
	char* endptr;
	stack* numbers = createStack(q->size);
	for (size_t i = 0, len = q->used; i < len; i++)
	{
		char* current_token = q->queue[0];
		strtold(current_token, &endptr);
		if (endptr != current_token) //the item on the top is a number
		{
			stackPush(numbers, current_token);
		}
		else
		{
			long double first_number = strtold(stackPop(numbers), &endptr);
			long double second_number = strtold(stackPop(numbers), &endptr);
			char* temp = (char*) malloc(MAX_LINE_LEN*sizeof(char));
			switch (current_token[0])
			{
				case '+':
				{
					sprintf(temp, "%Lf", first_number + second_number);
					break;
				}
				case '-':
				{
					sprintf(temp, "%Lf", first_number - second_number);
					break;
				}
				case '*':
				{
					sprintf(temp, "%Lf", first_number * second_number);
					break;
				}
				case '/':
				{
					sprintf(temp, "%Lf", first_number / second_number);
					break;
				}
			}
			stackPush(numbers, temp);
		}
		queuePop(q);
	}
	return strtold(stackPop(numbers), &endptr);
}

