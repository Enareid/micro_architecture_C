#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#define nul 0
#define adresse 1
#define reg 2
#define valeur 3

typedef struct instruction {
    char * inst_ASM;
    uint8_t code_op;
    int taille_code_op;
    int nb_operande;
    int type_op1;
    int taille_op1;
    int type_op2;
    int taille_op2;
    int use;
} instruction_t;

extern instruction_t instructions[18];


#endif