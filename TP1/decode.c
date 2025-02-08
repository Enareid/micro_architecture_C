#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructions.h"
#include "cpu.h"
#include "function.c"

void 
decode_instruction(int instruction, int taille)
{
    int nb_instructions = sizeof(instructions)/sizeof(instructions[0]);
    int nb_instructions_restantes = sizeof(instructions)/sizeof(instructions[0]);
	int i, j;
    j = taille;
    while (nb_instructions_restantes != 1) {
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
            printf("Instruction reconnue : %s\n", instructions[i].inst_ASM);
            CPU.RI = instructions[i].code_op;
            printf("Code opération : %d\n", CPU.RI);
        }
        instructions[i].use = 1;
	}
}


void 
load_instructions(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur ouverture fichier");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        unsigned int address;
        int values[3];
        int count = sscanf(line, "%x: %x %x %x", &address, &values[0], &values[1], &values[2]);
        printf("value %d", values[1]);
        decode_instruction(values[0], 7);
        if (count >= 2) { // Minimum : une adresse et une valeur
            for (int i = 0; i < count - 1; i++) {
                if (address + i < RAM_SIZE) {
                    CPU.RAM[address + i] = (unsigned char)values[i];
                }
            }
        }
    }

    fclose(file);
}


int 
main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fichier_instructions>\n", argv[0]);
        return EXIT_FAILURE;
    }
    load_instructions(argv[1]);

    // Exemple d'affichage du contenu de la mémoire après chargement
    for (int i = 0; i < RAM_SIZE; i++) {
        if (CPU.RAM[i] != 0) {
            printf("%04X: %02X\n", i, CPU.RAM[i]);
        }
    }
    return 0;
}

/*
int 
main()
{
    CPU.registre.registre[0] = -5;
    CPU.registre.registre[1] = -10;
    ADD(0,1);
    printf("%d\n", CPU.registre.registre[1]);
    return 0;
}
    */