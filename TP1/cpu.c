#include "cpu.h"
#include <string.h>
#include <stdlib.h>

CPU_t CPU;

void
init_CPU()
{
    memset(&CPU, 0, sizeof(CPU_t));
    CPU.PC = 0;
    CPU.adresse_latch = 0;
    CPU.adresse_bus = 0;
    CPU.data_bus = 0;
    CPU.RI = 0;
    CPU.registre.index = 0;
    for (int i = 0; i < NB_REGITRE; i++) {
        CPU.registre.registre[i] = 0;
    }
}