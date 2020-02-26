/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero and Isaac Wolfe                                */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;
   unsigned int uiDispLo;
   unsigned int uiDispHi;
         
   uiInstr = 0x10000000;
   
   uiInstr |= uiReg;
    
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   uiDispLo = uiDisp & 0x3;
   uiDispLo = uiDispLo << 29;
   uiInstr |= uiDispLo;
   
   uiDispHi = uiDisp >> 2;
   uiDispHi = uiDispHi << 5;
   uiDispHi &= 0x00ffffe0;
   uiInstr |= uiDispHi;
   
   return uiInstr;
}

unsigned int MiniAssembler_mov(unsigned int uiReg,
   unsigned int uiImmed)
{
   unsigned int uiInstr;

   uiInstr = 0x52800000;

   uiInstr |= uiReg;

   uiImmed = uiImmed << 5;
   uiImmed &= 0x001fffe0;

   uiInstr |= uiImmed;

   return uiInstr;
}

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
   unsigned int uiToReg)
{
   unsigned int uiInstr;

   uiInstr = 0x39000000;

   uiInstr |= uiFromReg;

   uiToReg = uiToReg << 5;
   uiInstr |= uiToReg;

   return uiInstr;
}

unsigned int MiniAssembler_b(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;

   uiInstr = 0x14000000;

   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   uiDisp = uiDisp/4;
   uiDisp &= 0x03ffffff;
   uiInstr |= uiDisp;

   return uiInstr;
}
