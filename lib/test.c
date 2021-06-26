#include <stdio.h>
#include <string.h>
#include "test.h"
#include <stdbool.h>
#define ABS(x) (((x) > 0) ? (x) : -(x))

bool isEqualChar(char a, char b)
{
   return (a==b);
}

bool isEqualUChar(unsigned char a, unsigned char b)
{
   return (a==b);
}

bool isEqualShortInt(short int a, short int b)
{
   return (a==b);
}

bool isEqualUShortInt(unsigned short int a, unsigned short int b)
{
   return (a==b);
}

bool isEqualInt(int a, int b)
{
   return (a==b);
}

bool isEqualUInt(unsigned int a, unsigned int b)
{
   return (a==b);
}


bool isEqualLongInt(long int a, long int b)
{
   return (a==b);
}

bool isEqualULongInt(unsigned long int a, unsigned long int b)
{
   return (a==b);
}

bool isEqualFloat(float a, float b, float e)
{
	if (ABS(a-b) < e)
	{
		return true;
	}	
	return false;
}

bool isEqualDouble(double a, double b, double e)
{
   if (ABS(a-b) < e)
   {
   		return true;
   }	
   return false;
}

bool isEqualLongDouble(long double a, long double b, long double e)
{
   if (ABS(a-b) < e)
   {
   		return true;
   }	
   return false;
}

bool isEqualString(char *a, char *b)
{
   if(a == b)
   {
      return true;
   }

   if(!strcmp(a, b))
   {
      return true;
   }
   return false;
}

bool isEqualCharMatrix(char** a, char** b)
{
	for (int i = 0; a[i] != NULL; i++)
	{
		for (int e = 0; a[i][e] != '\0'; i++)
		{
			if (a[i][e] != b[i][e])
			{
				return false;
			}
		}
	}
	return true;
}


void printString(char *str)
{
   int i = 0;

   if(str == NULL)
   {
      return;
   }

   while(str[i] != '\0')
   {
      if(str[i] == '\n')
      {
         printf("\\n");
      }
      else if(str[i] == '\t')
      {
         printf("\\t");
      }
      else
      {
         printf("%c", str[i]);
      }

      i++;
   }
}

void printListOfStrings(char** lst)
{
	int i = 0;
	while (lst[i] != NULL)
	{
		printf("%s\n", lst[i]);
		i++;
	}
}

bool isEqualLongDoubleArray(long double *v1, long double *v2, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (v1[i] != v2[i])
		{
			return false;
		}
	}
	return true;
}

bool isEqualStringArray(char** v1, char** v2)
{
	for (int i = 0; v1[i] != NULL; i++)
	{
		if (v2[i] == NULL)
		{
			return false;
		}
		if (v1[i] != v2[i])
		{
			return false;
		}
	}
	return true;
}
