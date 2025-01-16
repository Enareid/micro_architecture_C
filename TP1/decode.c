#include "instructions.h"
#include <stdio.h>

instruction_t *
decode_instruction(short int code)
{
    int i;
    for (i = 0; i < 18; i++) {
        short int masked_code = code & ((1 << instructions[i].taille) - 1);
        if (masked_code == instructions[i].code_op) {
            return &instructions[i];
        }
    }
    return NULL;
}

int
main(argc, argv)
    int argc;
    char ** argv;
{
    if (argc != 2) {
        printf("Usage: %s <code_op>\n", argv[0]);
        return 1;
    }
    short int code = atoi(argv[1]);
    instruction_t * inst = decode_instruction(code);
    if (inst != NULL) {
        printf("Instruction trouvée: %s\n", inst->inst_ASM);
        printf("Code opératoire: %d\n", inst->code_op);
        printf("Nombre d'opérandes: %d\n", inst->nb_operande);
    }
    else {
        printf("Instruction non trouvée\n");
    }
    return 0;
}