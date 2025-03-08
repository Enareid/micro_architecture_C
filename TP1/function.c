#include "cpu.h"

void 
AAout()
{
    CPU.adresse_bus = CPU.adresse_latch + 1;
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
    CPU.PCL = (CPU.PC & 0xFF00) | CPU.data_bus;
}

void
ALin()
{
    CPU.adresse_latch = CPU.adresse_bus;
}

void
ALLin()
{
    CPU.ALL = (CPU.adresse_latch & 0xFF00) | CPU.data_bus;
}

void
ALHin()
{
    CPU.ALH = CPU.data_bus;
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
    CPU.alu.flags = 0; // Réinitialise les flags
    if (CPU.alu.X + CPU.alu.Y > 255 || CPU.alu.X + CPU.alu.Y < 0)
        CPU.alu.flags = DEBORDEMENT;
    if (CPU.alu.X + CPU.alu.Y == 0) {
        CPU.alu.flags = NUL;
    }
    CPU.alu.res = CPU.alu.X + CPU.alu.Y;
}

void
soustraction()
{
    CPU.alu.flags = 0; // Réinitialise les flags
    if (CPU.alu.X - CPU.alu.Y > 255 || CPU.alu.X - CPU.alu.Y < 0)
        CPU.alu.flags = DEBORDEMENT;
    if (CPU.alu.X - CPU.alu.Y == 0) {
        CPU.alu.flags = NUL;
    }
    CPU.alu.res = CPU.alu.X - CPU.alu.Y;
}

void
next_addr()
{
    AAout();
    ALin();
}

void
next_instru()
{
    PCout();
    ALin();
    Read();
    AAout();
    PCin();
    DLout();
    IRin();
}

void
update_pc()
{
    CPU.PC = (CPU.PCH << 8) | CPU.PCL;
}

void
update_al()
{
    CPU.adresse_latch = (CPU.ALL << 8) | CPU.ALH;
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
    PCLin();
    RepX();
    ALUout();
    PCHin();
    update_pc();
}

void
JZ()
{
    if (CPU.alu.flags == NUL){
        JMP();
    }
    else {
        next_instru();
        next_instru();
    }
}

void
JC()
{
    if (CPU.alu.flags == DEBORDEMENT){
        JMP();
    }
    else {
        next_instru();
        next_instru();
    }
}

void
JMP2(uint8_t i)
{
    SR(i*2);
    Rout();
    PCLin();
    SR(i*2+1);
    Rout();
    PCHin();
    update_pc();
}

void
ST2(uint8_t i)
{
    SR(i*2);
    Rout();
    ALLin();
    SR(i*2+1);
    Rout();
    ALHin();
    SR(0);
    Rout();
    DLin();
    Write();
}

void
LD2(uint8_t i)
{
    SR(i*2);
    Rout();
    ALLin();
    SR(i*2+1);
    Rout();
    ALHin();
    Read();
    SR(0);
    DLout();
    Rin();
}

void
ST(uint8_t i)
{
    Read();
    DLout();
    Xin();
    AAout();
    ALin();
    Read();
    DLout();
    Yin();
    AAout();
    PCin();
    RepX();
    ALUout();
    ALLin();
    RepY();
    ALUout();
    ALHin();
    update_al();
    SR(i);
    Rout();
    DLin();
    Write();
    PCout();
    ALin();
}

void
LD(uint8_t i)
{
    Read();
    DLout();
    Xin();
    AAout();
    ALin();
    Read();
    DLout();
    Yin();
    AAout();
    PCin();
    RepX();
    ALUout();
    ALLin();
    RepY();
    ALUout();
    ALHin();
    update_al();
    Read();
    DLout();
    SR(i);
    Rin();
    PCout();
    ALin();
}

void 
MV(uint8_t i)
{
    Read();
    AAout();
    PCin();
    DLout();
    SR(i);
    Rin();
}

void
DEC(uint8_t i)
{
    SR(i);
    Rout();
    Xin();
    CPU.alu.Y = 1;
    soustraction();
    ALUout();
    SR(i);
    Rin();
}

void
INC(uint8_t i)
{
    SR(i);
    Rout();
    Xin();
    CPU.alu.Y = 1;
    addition();
    ALUout();
    SR(i);
    Rin();
}

void
NOT(uint8_t i)
{
    SR(i);
    Rout();
    Xin();
    CPU.alu.Y = 0xFF;
    CPU.alu.X = CPU.alu.res;
    soustraction();
    ALUout();
    SR(i);
    Rin();
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
    SR(i);
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

void
AND(uint8_t i, uint8_t j)
{
    SR(j);
    Rout();
    Xin();
    SR(i);
    Rout();
    Yin();
    CPU.alu.res = CPU.alu.X & CPU.alu.Y;
    ALUout();
    SR(i);
    Rin();
}

void
MV2(uint8_t i, uint8_t j)
{
    SR(j);
    Rout();
    Xin();
    SR(i);
    Rin();
}

void
SWP(uint8_t i, uint8_t j)
{
    SR(j);
    Rout();
    Xin();
    SR(i);
    Rout();
    SR(j);
    Rin();
    SR(i);
    RepX();
    ALUout();
    Rin();
}