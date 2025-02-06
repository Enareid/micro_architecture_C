#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructions.h"

struct proc * CPU;

void 
decode_instruction(int instruction, int taille)
{
    int nb_instructions = sizeof(instructions)/sizeof(instructions[0]);
    int nb_instructions_restantes = sizeof(instructions)/sizeof(instructions[0]);
    instruction_t * res;
    res = NULL;
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
            CPU -
            printf("Instruction reconnue : %d\n", instructions[i].code_op);
        }
        instructions[i].use = 1;
	}
	return res;
}

int 
main(int argc, char *argv[])
{
    
    int taille = strlen(argv[1])*4;
    int instruction = strtol(argv[1], NULL, 16);
    decode_instruction(instruction, taille-1);
    return 0;
}