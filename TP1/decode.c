#include <stdio.h>
#include <stdlib.h>

typedef struct instruction {
    unsigned char inst_ASM[5];
    short int code_op;
    short int taille;
    short int nb_operande;
    int op1;
    int op2;
} instruction_t;

instruction_t donnee[20];
donnee[0].inst_asm = "NOP";

int
main()
{
    printf("%s\n", donnee[0].code_op);
    return 0;
}


/* 0100 1010 0000 0000 0000 0001 */