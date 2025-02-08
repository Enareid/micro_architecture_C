#include "cpu.h"

void 
AAout()
{
    CPU.adresse_latch = CPU.adresse_latch + 1;
}

void
DLout()
{
    CPU.data_bus = CPU.DLatch;
}

void
DLin()
{
    CPU.DLatch = CPU.data_bus;
}

void 
PCin()
{
    CPU.PC = CPU.adresse_bus;
    CPU.PCH = (CPU.PC >> 8) & 0xFF;  // Récupère les 8 bits de poids fort
    CPU.PCL = CPU.PC & 0xFF;         // Récupère les 8 bits de poids faible
}

void
PCout()
{
    CPU.adresse_bus = CPU.PC;
}

void 
PCHin()
{
    CPU.PCH = CPU.data_bus;
}

void 
PCLin()
{
    CPU.PCL = CPU.data_bus;
}

void
ALin()
{
    CPU.adresse_latch = CPU.adresse_bus;
}

void
Read()
{
    CPU.DLatch = CPU.RAM[CPU.adresse_latch];
}

void
Write()
{
    CPU.RAM[CPU.adresse_latch] = CPU.DLatch;
}

void
RepX()
{
    CPU.alu.res = CPU.alu.X;
}

void 
RepY()
{
    CPU.alu.res = CPU.alu.Y;
}

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
JMP()
{
    Read();
    DLout();
    Xin();
    AAout();
    ALin();
    Read();
    DLout();
    PCHin();
    RepX();
    ALUout();
    PCLin();
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