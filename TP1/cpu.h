#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#define RAM_SIZE 2048
#define NB_REGITRE 8

struct registre {
    int index;
    uint8_t registre[NB_REGITRE];
};

typedef struct {
    uint8_t RAM[RAM_SIZE];
    struct registre registre;
    uint8_t RI;
    uint8_t PC;
    uint8_t adresse_latch;
    uint8_t adresse_bus;
    uint8_t data_bus;
} CPU_t;

extern CPU_t CPU;

void init_CPU();

void free_CPU();

#endif