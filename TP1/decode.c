#include <stdio.h>
#include <stdlib.h>

typedef struct instruction {
    unsigned char * inst_ASM;
    short int code_op;
    short int taille;
    short int nb_operande;
    int op1;
    int op2;
} instruction_t;

instruction_t donnee[20];

int
init()
{
    /* première instruction */
    donnee[0] = {"NOP", 00000000, 8, 0, 0, 0};
    return 0;
}

void
main()
{
    int i = init();
    printf("%hhn\n", donnee[0].inst_ASM);
}

/* 0100 1010 0000 0000 0000 0001 */