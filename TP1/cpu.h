#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#define RAM_SIZE 2048
#define NB_REGITRE 8

#define DEBORDEMENT 1
#define NUL 2

struct registre {
    int index;
    uint8_t registre[NB_REGITRE];
};



struct ALU {
    uint8_t X;
    uint8_t Y;
    uint8_t res;
    uint8_t flags;
};

/* rajouter les flags pour éviter les débordement des oppérations */

typedef struct {
    uint8_t RAM[RAM_SIZE];
    struct registre registre;
    uint8_t RI;
    uint16_t PC;
    uint8_t PCH;
    uint8_t PCL;
    uint16_t adresse_latch;
    uint16_t adresse_bus;
    uint8_t data_bus;
    uint8_t DLatch;
    struct ALU alu;
} CPU_t;

extern CPU_t CPU;

void init_CPU();

#endif