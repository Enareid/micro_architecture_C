#include "cpu.h"

void 
PCin()
{
    CPU.PC = CPU.adresse_bus;
    CPU.PCH = 
}

void

void
Xin()
{
    CPU.alu.X = CPU.data_bus;
}

void
Yin()
{
    CPU.alu.Y = CPU.data_bus;
}

void
IRin()
{
    CPU.RI = CPU.data_bus;
}

void
Rin()
{
    CPU.registre.registre[CPU.registre.index] = CPU.data_bus;
}

void
SR(int i)
{
    CPU.registre.index = i;
}

void
Rout()
{
    CPU.data_bus = CPU.registre.registre[CPU.registre.index];
}

void
ALUout()
{
    CPU.data_bus = CPU.alu.res;
}

void
addition()
{
    if (CPU.alu.X + CPU.alu.Y > 255 || CPU.alu.X + CPU.alu.Y < 0)
        CPU.alu.flags = DEBORDEMENT;
    CPU.alu.res = CPU.alu.X + CPU.alu.Y;
}

void
soustraction()
{
    if (CPU.alu.X + CPU.alu.Y > 255 || CPU.alu.X + CPU.alu.Y < 0)
        CPU.alu.flags = DEBORDEMENT;
    CPU.alu.res = CPU.alu.X - CPU.alu.Y;
}

void
JMP(uint8_t i, uint8_t j)
{
    
}

void
ADD(uint8_t i, uint8_t j)
{
    SR(j);
    Rout();
    Xin();
    SR(i);
    Rout();
    Yin();
    addition();
    ALUout();
    SR(j);
    Rin();
}

void
SUB(uint8_t i, uint8_t j)
{
    SR(j);
    Rout();
    Xin();
    SR(i);
    Rout();
    Yin();
    soustraction();
    ALUout();
    SR(j);
    Rin();
}