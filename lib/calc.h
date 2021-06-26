#ifndef CALC_H
#define CALC_H

#define MAX_LINE_LEN 256	
#include "queue.h"
char* removeNewline(char* string);
char* removeWhitespaces(char* string);
char** tokenize(char* string);
queue* resort(char** tokens);
long double calc(queue* q);
#endif // CALC_H
