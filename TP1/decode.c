#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "instructions.h"
#include "cpu.h"
#include "function.c"

instruction_t
decode_instruction(int instruction, int taille)
{
    int nb_instructions = sizeof(instructions)/sizeof(instructions[0]);
    int nb_instructions_restantes = sizeof(instructions)/sizeof(instructions[0]);
	int i, j;
    instruction_t res;
    j = taille;
    while (nb_instructions_restantes != 1 && instruction != 0) {
        for(i = 0; i < nb_instructions; i++) {
            if (instructions[i].use) {
                for (int s = instructions[i].taille_code_op - 1; s >= 0; s--) {
                    int code_sieme_bit = (((instructions[i].code_op)>>s)&1);
				    int instruction_jieme_bit = (((instruction)>>j)&1);
                    if (code_sieme_bit != instruction_jieme_bit) {
                        instructions[i].use = 0;
                    }
                    j--;
                }
            }
            j = taille;
            if (instructions[i].use == 0) {
                nb_instructions_restantes--;
            }
        }
    }    
	for (i=0;i<nb_instructions;i++){
        if (instructions[i].use){
            res = instructions[i];
        }
        instructions[i].use = 1;
	}
    next_addr();
    return res;
}


void 
load_instructions(const char *filename) {
    FILE * file = fopen(filename, "r");
    if (!file) {
        perror("Erreur ouverture fichier");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    int indice = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        unsigned int address;
        int values[3];
        int count = sscanf(line, "%x: %x %x %x", &address, &values[0], &values[1], &values[2]);
        if (count >= 2) { // Minimum : une adresse et une valeur
            for (int i = 0; i < count - 1; i++) {
                if (address + i < RAM_SIZE) {
                    CPU.RAM[address + i] = (unsigned char)values[i];
                }
            }
        }
        if (indice == 0) {
            CPU.RI = values[0];
            CPU.adresse_latch = address;
        }
        indice++;
    }
    fclose(file);
}

void
execute()
{
    printf("Execute\n");
    int instruction = decode_instruction(CPU.RI, 7).code_op;
    fflush(stdout);
    while(CPU.RI != 0) {
        switch(instruction) {
            case 0b111:
                SWP((CPU.RI >> 3) && 0x07, CPU.RI & 0x07);
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b110:
                AND((CPU.RI >> 3) && 0x07, CPU.RI & 0x07);
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b101:
                SUB((CPU.RI >> 3) && 0x07, CPU.RI & 0x07);
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b100:
                ADD((CPU.RI >> 3) && 0x07, CPU.RI & 0x07);
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b01101:
                NOT(CPU.RI & 0x07);
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b01100:
                INC(CPU.RI & 0x07);
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b01011:
                DEC(CPU.RI & 0x07);
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b01010:
                MV(CPU.RI & 0x07);
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b01001:
                LD(CPU.RI & 0x07);
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b01000:
                ST(CPU.RI & 0x07);
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b011111:
                LD2(CPU.RI & 0x07);
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b011110:
                ST2(CPU.RI & 0x07);
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b01110011:
                JMP2(CPU.RI & 0x07);
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b01110010:
                JC();
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b01110001:
                JZ();
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
            case 0b01110000:
                JMP();
                next_instru();
                instruction = decode_instruction(CPU.RI, 7).code_op;
                break;
        }
    }
    printf("Execution terminée\n");
}

void
txt_to_s(const char *filename)
{
    char buf[20];
    int indice;
    FILE * file = fopen(filename, "r");
    int file2 = open("test.txt", O_WRONLY | O_TRUNC);
    if (!file) {
        perror("Erreur ouverture fichier");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        unsigned int address;
        int values[3];
        int count = sscanf(line, "%x: %x %x %x", &address, &values[0], &values[1], &values[2]);
        instruction_t inst = decode_instruction(values[0], 7);
        char * instruction_char = inst.inst_ASM;
        for (indice = 0; indice < strlen(instruction_char); indice ++) {
            buf[indice] = instruction_char[indice];
        }
        write(file2, buf, indice);
        write(file2, " ", 1);
        switch(inst.nb_operande) {
            case 0:
                break;
            case 1:
                switch(inst.type_op1) {
                    sprintf(buf, "%d", values[1]); // Convert integer to string
                    printf("%s\n", buf);
                    break; 
                }
        }
    }
}


int 
main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fichier_instructions>\n", argv[0]);
        return EXIT_FAILURE;
    }
    load_instructions(argv[1]);
    printf("valeur registre 1 : %d\n", CPU.registre.registre[1]);
    printf("valeur registre 2 : %d\n", CPU.registre.registre[2]);
    execute();
    printf("valeur registre 1 : %d\n", CPU.registre.registre[1]);
    printf("valeur registre 2 : %d\n", CPU.registre.registre[2]);
    txt_to_s(argv[1]);
}