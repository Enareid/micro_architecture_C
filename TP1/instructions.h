#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

typedef struct instruction {
    char * inst_ASM;
    short int code_op;
    short int taille;
    short int nb_operande;
    int op1;
    int op2;
} instruction_t;

extern const instruction_t instructions[18];

#endif