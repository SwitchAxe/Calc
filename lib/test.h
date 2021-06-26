#ifndef TEST_H
#define TEST_H
#include <stdbool.h>


bool isEqualChar(char a, char b);
bool isEqualUChar(unsigned char a, unsigned char b);

bool isEqualShortInt(short int a, short int b);
bool isEqualUShortInt(unsigned short int a, unsigned short int b);

bool isEqualInt(int a, int b);
bool isEqualUInt(unsigned int a, unsigned int b);

bool isEqualLongInt(long int a, long int b);
bool isEqualULongInt(unsigned long int a, unsigned long int b);

bool isEqualFloat(float a, float b, float epsilon);
bool isEqualDouble(double a, double b, double epsilon);
bool isEqualLongDouble(long double a, long double b, long double epsilon);

bool isEqualString(char *a, char *b);
bool isEqualLongDoubleArray(long double *v1, long double *v2, int size);
//this one doesn't need a size because i assume the arrays are
//terminated by NULL
bool isEqualStringArray(char** v1, char** v2);
void printString(char *str);
void printListOfStrings(char** lst);
#endif // TEST_H
