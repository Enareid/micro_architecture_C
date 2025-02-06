#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#define nul 0
#define adresse 1
#define reg 2
#define valeur 3
#define RAM_SIZE 2048
#define NB_REGITRE 8

typedef struct instruction {
    char * inst_ASM;
    int code_op;
    int taille_code_op;
    int nb_operande;
    int type_op1;
    int taille_op1;
    int type_op2;
    int taille_op2;
    int use;
} instruction_t;

extern instruction_t instructions[17];

struct registre {
    int index;
    uint8_t registre[NB_REGITRE];
};


struct proc {
    uint8_t RAM[RAM_SIZE];
    struct registre registre;
    uint8_t RI;
    uint8_t PC;
    uint8_t adresse_latch;
    uint8_t adresse_bus;
    uint8_t data_bus;
};

#endif