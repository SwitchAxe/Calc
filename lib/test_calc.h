#ifndef TEST_CALC_H
	#define TEST_CALC_H
	#include "queue.h"

	void test_removeNewline(char* str, char* expect_value,
						 int lineNumber, char* description);
	void test_removeWhitespaces(char* str, char* expect_value,
							 int lineNumber, char* description);
	void test_tokenize(char* string, char** expect_value,
					int lineNumber, char* description);
	void test_calc(queue* tokens, long double expect_value,
				int lineNumber, char* description);
	void test_resort(char** tokens, queue* expect_value, 
				int lineNumber, char* description);

#endif // TEST_CALC_H
