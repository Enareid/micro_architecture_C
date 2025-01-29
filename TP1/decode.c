#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructions.h"

instruction_t * 
decode_instruction(int instruction, int taille)
{
    int nb_instructions = sizeof(instructions)/sizeof(instructions[0]);
    instruction_t * res;
    res = NULL;
	int i, j;
    j = taille;
    while (nb_instructions != 1) {
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
                nb_instructions--;
            }
        }
    }    
	for (i=0;i<17;i++){
        if (instructions[i].use){
            res = instructions+i;
        }
        instructions[i].use = 1;
	}
	return res;
}

void
decode(int instruction, int taille){
    instruction_t * inst = decode_instruction(instruction, taille);

}

int 
main(int argc, char *argv[])
{
    
    int taille = strlen(argv[1])*4;
    int instruction = strtol(argv[1], NULL, 16);
    instruction_t * res = decode_instruction(instruction, taille-1);
    if (res == NULL){
        printf("Instruction non reconnue\n");
    }
    else{
        printf("Instruction reconnue : %s\n", res->inst_ASM);
    }
    return 0;
}