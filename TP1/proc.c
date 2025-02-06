#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define RAM_SIZE 2048
#define NB_REGITRE 8

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