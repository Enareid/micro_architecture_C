#include "instructions.h"
#include "fonction.c"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

instruction_t instructions[17] = {
    {"NOP", 0b00000000, 8, 0, 1, {.fonction = NOP}}, /* Ne fait rien */
    {"JMP", 0b01110000, 8, 0, 1, {.fonction = JMP}}, /* Effectue un branchement a l'adresse codée sur 16 bits */
    {"JZ", 0b01110001, 8, 0, 1, {.fonction = JZ}}, /* Effectue un saut a l'adresse 16 bit si l'opération précédente à donné un résultat nul */
    {"JC", 0b01110010, 8, 0, 1, {.fonction = JC}}, /* Effectue un saut à l'adresse 16 bit si l'opération précédente à engendré une retenue */
    {"JMP", 0b01110011, 8, 1, 1, {.fonction1 = JMP2}}, /* Effectue un branchement à l'adresse RX0 (R0 + R1) */
    {"ST", 0b011110, 6, 1, 1, {.fonction1 = ST2}}, /* Stocke la valeur du reg R0 sur le l'adresse inscrit dans le reg RXn */
    {"LD", 0b011111, 6, 1, 1, {.fonction1 = LD2}}, /* Charge dans le reg R0 la valeur stockée en mémoire à l'adresse inscrit dans le reg RXn */
    {"ST", 0b01000, 5, 1, 1, {.fonction1 = ST}}, /* Stocke la valeur du reg Rn en mémoire à l'adresse sur 16 bits */
    {"LD", 0b01001, 5, 1, 1, {.fonction1 = LD}}, /* Charge dans le reg Rn la valeur stockée en mémoire à l'adresse sur 16 bits */
    {"MV", 0b01010, 5, 1, 1, {.fonction1 = MV}}, /* Charge dans le reg Rn la valeur de l'argument codée sur 8 bits (soir une valeur immédiate, soir un reg) */
    {"DEC", 0b01011, 5, 1, 1, {.fonction1 = DEC}}, /* Soustrait 1 à la valeur de Rn et stocke le résultat dans Rn */
    {"INC", 0b01100, 5, 1, 1, {.fonction1 = INC}}, /* Ajoute 1 à la valeur de Rn et stocke la résultat dans Rn */
    {"NOT", 0b01101, 5, 1, 1, {.fonction1 = NOT}}, /* Inverse bit à bit le reg Rn et stocke le résultat */
    {"ADD", 0b100, 3, 2, 1, {.fonction2 = ADD}}, /* Additionne la valeur du reg Rn (premier opérande) avec la valeur du reg Rm (second opérande) et stocke le résultat dans Rn */
    {"SUB", 0b101, 3, 2, 1, {.fonction2 = SUB}}, /* Soustrait la valeur du reg Rm (deuxième opérande) à la valeur du reg Rn (premièer opérande) et stocke le résultat dans Rn*/
    {"AND", 0b110, 3, 2, 1, {.fonction2 = AND}}, /* Fait la conjonction bit à bit des deux regs et range le résultat dans le premier op (Rn codée sur 2 bits) */
    {"SWP", 0b111, 3, 2, 1, {.fonction2 = SWP}}, /* Echange la valeur du reg Rn (premier opérande) au reg Rm (deuxième opérande) */
};


/* 4A 00 01 => 01001[LD] 010[R2] 0000000000000001[0001h] => LD R2, 0001h */