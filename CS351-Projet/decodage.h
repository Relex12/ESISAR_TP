#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct ligneCode{
  char opcode[5];
  char op1[5];
  char op2[5];
  char op3[5];
};
//typedef ligneCode ligneCode;

char * codeR[16]={"ADD","AND","DIV","JR","MFHI","MFLO","MULT","NOP","OR","ROTR","SLL","SLT","SRL","SUB","SYSCALL","XOR"};
char * codeI[8]={"ADDI","BEQ","BGTZ","BLEZ","BNE","LUI","LW","SW"};
char * codeJ[2]={"J","JAL"};
int codeEqR[]={0x20,0x24,0x1A,0x08,0x10,0x12,0x18,0x00,0x25,0x02,0x00,0x2A,0x02,0x22,0x0C,0x26};
int codeEqI[]={0x08,0x04,0x07,0x06,0x05,0x0F,0x23,0x2B};
int codeEqJ[]={0x02,0x03};
