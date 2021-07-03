#include <stdio.h>
#include <ctype.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "lib/calc.h"
#include "lib/stack.h"
#include "lib/queue.h"
int main(int argc, char* argv[])
{
   if (argc == 1)
   {
      printf("no arguments and no expressions to calc. aborting.\n");
      exit(1);
   }
   bool lpflag = false; //flag that makes the program a loop
   bool inflag = false; //flag that makes the program ask for input once
   bool fflag = false; //flag that makes the program check a file for expressions
   int fileIndex;
   for (int i = 1; i < argc; i++)
   {
      if (!strcmp(argv[i],"-l"))
      {
         lpflag = true; inflag = false; fflag = false; 
      }
      else if (!strcmp(argv[i], "-i"))
      {
         inflag = true; lpflag = false; fflag = false;
      }
      else if (!strcmp(argv[i], "-f"))
      {
         fflag = true; inflag = false; lpflag = false;
         fileIndex = i+1;
      }
   }

   if (inflag)
   {
      char* str = malloc(MAX_LINE_LEN*sizeof(str)); //raw string
      fgets(str, MAX_LINE_LEN, stdin);
      char* exp = removeNewline(str); //string after the \n is removed
      char** tokens = tokenize(exp); //unsorted tokens
      queue* q = resort(tokens); //sorted tokens
      long double result = calc(q); //final result
      printf("%.2Lf\n", result);
      return 0;
   }
   else if (lpflag)
   {
      char* str = malloc(MAX_LINE_LEN*sizeof(char));
      while (printf("> ") && fgets(str, MAX_LINE_LEN, stdin) && strcmp(str, "exit\n"))
      {
         char* rmstr = removeNewline(str); 
		 char** exp = tokenize(rmstr); 
		 printf("got here!2\n");
         queue* q = resort(exp);
         long double result = calc(q); 
         printf("%.2Lf\n\n", result); 
      }
   }
   else if (fflag)
   {
      FILE* file = fopen(argv[fileIndex], "r");
      char* str = malloc(MAX_LINE_LEN*sizeof(char));
      while (fgets(str, MAX_LINE_LEN, file))
      {
         char* exp = removeNewline(str);
         char** tokens = tokenize(exp);
         queue* q = resort(tokens);
         long double result = calc(q);
         printf("%.2Lf", result);
      }
   }
   else
   {
      for (int i = 1; i < argc; i++)
      {
         char* str = removeNewline(argv[i]);
         char** exp = tokenize(str);
         queue* q = resort(exp);
         long double result = calc(q);
         printf("%.2Lf\n", result);
      }
   }
   //unused flags
   bool eqflag = false; //flag that makes the program an equation solver.

   return 0;
}
