#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>

#define nul 0
#define adresse 1
#define reg 2
#define valeur 3

union Functions {
    void (*fonction)(void);
    void (*fonction1)(uint8_t);
    void (*fonction2)(uint8_t, uint8_t);
};

typedef struct instruction {
    char * inst_ASM;
    uint8_t code_op;
    int taille_code_op;
    int nb_operande;
    int use;
    union Functions fonctions;
} instruction_t;


extern instruction_t instructions[17];


#endif