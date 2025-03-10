#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "instructions.h"
#include "cpu.h"

int nb_line = 0;
int prev_break = 0;

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
execute(int nb_instr)
{
    instruction_t instruction = decode_instruction(CPU.RI, 7);
    while(CPU.RI != 0 && nb_instr != 0) {
        nb_instr--;
        if (instruction.nb_operande == 0) {
            instruction.fonctions.fonction();
        }
        if (instruction.nb_operande == 1) {
            instruction.fonctions.fonction1(CPU.RI & 0x07);
        }
        if (instruction.nb_operande == 2) {
            instruction.fonctions.fonction2((CPU.RI >> 3) && 0x07, CPU.RI & 0x07);
        }
        next_instru();
        instruction = decode_instruction(CPU.RI, 7);
    }
}

void 
txt_to_s(const char *filename) {
    FILE *input_file = fopen(filename, "r");
    if (!input_file) {
        perror("Erreur ouverture fichier");
        return;
    }
    FILE *output_file = fopen("output.s", "w");
    if (!output_file) {
        perror("Erreur ouverture fichier de sortie");
        fclose(input_file);
        return;
    }
    fprintf(output_file,".data\nres: .quad 0\n.text\n.globl _start\n_start:\n");
    char line[256];
    while (fgets(line, sizeof(line), input_file)) {
        unsigned int address;
        int values[3];
        int count = sscanf(line, "%x: %x %x %x", &address, &values[0], &values[1], &values[2]);
        fprintf(output_file, "label_%04X:\n ", address);
        if (count >= 2) {
            unsigned int instruction = values[0];
            int opcode = decode_instruction(instruction, 7).code_op;
            switch (opcode) {
                case 0b00000000:
                    fprintf(output_file, "nop\n");
                    break;
                case 0b111:
                    fprintf(output_file, "xchg %%r1%d, %%r1%d\n", (instruction >> 3) & 0x07, instruction & 0x07);
                    break;
                case 0b110:
                    fprintf(output_file, "and %%r1%d, %%r1%d\n", (instruction >> 3) & 0x07, instruction & 0x07);
                    break;
                case 0b101:
                    fprintf(output_file, "sub %%r1%d; %%r1%d\n", (instruction >> 3) & 0x07, instruction & 0x07);
                    break;
                case 0b100:
                    fprintf(output_file, "add %%r1%d, %%r1%d\n", (instruction >> 3) & 0x07, instruction & 0x07);
                    break;
                case 0b01101:
                    fprintf(output_file, "not %%r1%d\n", instruction & 0x07);
                    break;
                case 0b01100:
                    fprintf(output_file, "inc %%r1%d\n", instruction & 0x07);
                    break;
                case 0b01011:
                    fprintf(output_file, "dec %%r1%d\n", instruction & 0x07);
                    break;
                case 0b01010:
                    fprintf(output_file, "mov $%d, %%r1%d\n", values[1], instruction & 0x07);
                    break;
                case 0b01001:
                    fprintf(output_file, "ld %%r%d\n", instruction & 0x07);
                    break;
                case 0b01000:
                    fprintf(output_file, "mov %%r1%d, res(%%rip)\n", instruction & 0x07);
                    break;
                case 0b011111:
                    fprintf(output_file, "ld R%d\n", instruction & 0x07);
                    break;
                case 0b011110:
                    fprintf(output_file, "ST R%d\n", instruction & 0x07);
                    break;
                case 0b01110011:
                    fprintf(output_file, "jmp RX%01X\n", values[1]);
                    break;
                case 0b01110010:
                    fprintf(output_file, "jc label_%02X%02X\n", values[1], values[2]);
                    break;
                case 0b01110001:
                    fprintf(output_file, "jz label_%02X%02X\n", values[1], values[2]);
                    break;
                case 0b01110000:
                    fprintf(output_file, "jmp label_%02X%02X\n", values[1], values[2]);
                    break;
            }
        }
    }  
    fprintf(output_file, "exit:\nmov $60, %%rax\nmov $0, %%rdi\nsyscall\n");
    fclose(input_file);
    fclose(output_file);
}

void
print_file(const char *filename) {
    int count;
    count = 1;
    FILE *input_file = fopen(filename, "r");
    if (!input_file) {
        perror("Erreur ouverture fichier");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), input_file)) {
        printf("%d: %s",count, line);
        count++;
    }
    printf("\n");
    fclose(input_file);
}

void 
run(const char *filename) {
    load_instructions(filename);
    execute(nb_line - 1);
    nb_line = 0;
}

void
info_register() {
    printf("PC: %04X\n", CPU.PC);
    printf("PCH: %02X\n", CPU.PCH);
    printf("PCL: %02X\n", CPU.PCL);
    printf("RI: %02X\n", CPU.RI);
    printf("ALL: %02X\n", CPU.ALL);
    printf("ALH: %02X\n", CPU.ALH);
    printf("Adresse bus: %04X\n", CPU.adresse_bus);
    printf("Data bus: %02X\n", CPU.data_bus);
    printf("DLatch: %02X\n", CPU.DLatch);
    printf("X: %d\n", CPU.alu.X);
    printf("Y: %d\n", CPU.alu.Y);
    printf("Res: %d\n", CPU.alu.res);
    printf("Flags: %02X\n", CPU.alu.flags);
    for (int i = 0; i < NB_REGITRE; i++) {
        printf("R%d: %d\n", i, CPU.registre.registre[i]);
    }
}



void
debugger(const char *filename) {
    load_instructions(filename);
    while(1) {
        printf("(db) : ");
        char cmd[256];
        fgets(cmd, sizeof(cmd), stdin);
        if (strcmp(cmd, "quit\n") == 0) {
            exit(EXIT_SUCCESS);
        }
        if (strcmp(cmd, "list\n") == 0) {
            print_file(filename);
        }
        if (strcmp(cmd, "run\n") == 0) {
            printf("Starting program\n");
            run(filename);
            printf("Program exited normally\n");
        }
        if (strcmp(cmd, "info register\n") == 0) {
            info_register();
        }
        if (strcmp(cmd, "step\n") == 0) {
            execute(1);
        }
        if (strstr(cmd, "break") != NULL) {
            sscanf(cmd, "break %d\n", &nb_line);
            if(nb_line < prev_break) {
                nb_line += prev_break;
            }
            prev_break = nb_line;
            printf("Breakpoint set at line %d\n", nb_line);
        }
    }
}

int 
main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fichier_instructions>\n [opt]", argv[0]);
        return EXIT_FAILURE;
    }
    if (argv[2] != NULL) {
        if (strcmp(argv[2], "-d") == 0) {
            debugger(argv[1]);
            exit(EXIT_SUCCESS);
        }
    }
    else {
        switch(fork()){
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);
            case 0:
                load_instructions(argv[1]);
                execute(-1);
                exit(EXIT_SUCCESS);
            default:
                wait(NULL);
                break;
        }
    }
}