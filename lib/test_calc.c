#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "test.h"

void test_removeNewline(char* str, char* expected, int line, char* description)
{
	printf("removeNeline(): %s\n", description);
	printf("\tinput string: ");
    printString(str);
	printf("\n\texpected string: %s\n", expected);

	removeNewline(str); 

	printf("\tresult string: %s\n", str);

	if(isEqualString(str, expected))
	{	
		printf("\ttest case in line %d: passed\n", line);
	}
	else
	{
		printf("\ttest case in line %d: failed\n", line);
	}

	printf("\n");
}

void test_removeWhitespaces(char* str, char* expected, int line, char* description)
{
	printf("removeWhitespaces(): %s\n", description);
	printf("\tinput string: ");
	printString(str);
	printf("\n\texpected string: %s\n", expected);

	removeWhitespaces(str);
	printf("\tresult string: %s\n", str);

	if(isEqualString(str, expected))
	{	
		printf("\ttest case in line %d: passed\n", line);
	}
	else
	{
		printf("\ttest case in line %d: failed\n", line);
	}
	printf("\n");
}

/*
void test_charToString(char c, char* expected, int line, char* description)
{
	printf("running test case in line %d: %s\n", line, description);
	printf("	starting char: '%c'\n", c);
	printf("	expected value: \"%s\"\n", expected);
	char* value = charToString(c);

	if(isEqualString(value, expected))
	{
		printf("	charToString: success\n");
	}	
	else
	{
		printf("	charToString: failed\n");
	}
}
*/

void test_tokenize(char* string,
	 char** expected, int line, char* description)
{
	printf("tokenize(): %s", description);
	printf("\tinput string: %s", string);
	printf("\n\texpected value: \n");
	printListOfStrings(expected);
	//printCharMatrix(expected);

	char** result = tokenize(string);
	printf("\n\tactual result: \n");
	printListOfStrings(result);
	int i = 0; 
	while (true)
	{
		
		if (result[i] == NULL)
		{
			break;
		}
		
		if (!(isEqualString(result[i],expected[i])))
		{
			printf("\ttest case in line %d: failed\n", line);		
			return;
		}
		i++;
	}
	printf("\ttest case in line %d: passed\n", line);
	/*
	if (isEqualCharMatrix(tokenize(string), expected))
	{
		printf("\ttest case in line %d: passed", __LINE__);
	}
	else
	{
		printf("\ttest case in line %d: failed", __LINE__);
	}
	*/
}

void test_calc(queue* q, long double expected, int line, char* description)
{
	printf("calc(): %s", description);
	printf("\n\tinput queue:\n");
	printQueue(q);	
	printf("\n\texpected value: %Lf\n", expected);
		
	long double result = calc(q);
	printf("\n\tactual result: %Lf\n", result);	
	if (isEqualLongDouble(result, expected, 0.00001))
	{
		printf("\ttest case in line %d: passed", line);		
	}
	else
	{
		printf("\ttest case in line %d: failed", line);
	}
}


void test_resort(char** tokens, queue* expect_value, 
				int lineNumber, char* description)
{
	queue* q;
	printf("resort(): %s", description);
	printf("\n\tinput string:\n");
	printListOfStrings(tokens);
	printf("\n\texpected value:\n");
	printQueue(expect_value);
	q = resort(tokens);
	printf("actual result: \n");
	printQueue(q);
	if (isEqualStringArray(q->queue, expect_value->queue))
	{
		printf("test case in line %d: passed", lineNumber);
	}
	else
	{
		printf("test case in line %d: failed", lineNumber);
	}
}
