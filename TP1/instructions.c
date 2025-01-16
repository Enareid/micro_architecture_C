#include "instructions.h"

const instruction_t instructions[18] = {
    {"NOP", 0b00000000, 8, 0, 0, 0}, /* Ne fait rien */
    {"JMP", 0b01110000, 8, 1, 16, 0}, /* Effectue un branchement a l'adresse codée sur 16 bits */
    {"JZ", 0b01110001, 8, 1, 16, 0}, /* Effectue un saut a l'adresse 16 bit si l'opération précédente à donné un résultat nul */
    {"JC", 0b01110010, 8, 1, 16, 0}, /* Effectue un saut à l'adresse 16 bit si l'opération précédente à engendré une retenue */
    {"JMP", 0b01110011, 8, 0, 0, 0}, /* Effectue un branchement à l'adresse RX0 (R0 + R1) */
    {"ST", 0b011110, 6, 1, 2, 0}, /* Stocke la valeur du registre R0 sur le l'adresse inscrit dans le registre RXn */
    {"LD", 0b011111, 6, 1, 2, 0}, /* Charge dans le registre R0 la valeur stockée en mémoire à l'adresse inscrit dans le registre RXn */
    {"ST", 0b01000, 5, 2, 3, 16}, /* Stocke la valeur du registre Rn en mémoire à l'adresse sur 16 bits */
    {"LD", 0b01001, 5, 2, 3, 16}, /* Charge dans le registre Rn la valeur stockée en mémoire à l'adresse sur 16 bits */
    {"MV", 0b01010, 5, 2, 3, 8}, /* Charge dans le registre Rn la valeur de l'argument codée sur 8 bits (soir une valeur immédiate, soir un registre) */
    {"DEC", 0b01011, 5, 1, 3, 0}, /* Soustrait 1 à la valeur de Rn et stocke le résultat dans Rn */
    {"INC", 0b01100, 5, 1, 3, 0}, /* Ajoute 1 à la valeur de Rn et stocke la résultat dans Rn */
    {"NOT", 0b01101, 5, 1, 3, 0}, /* Inverse bit à bit le registre Rn et stocke le résultat */
    {"ADD", 0b100, 3, 2, 2, 3}, /* Additionne la valeur du registre Rn (premier opérande) avec la valeur du registre Rm (second opérande) et stocke le résultat dans Rn */
    {"SUB", 0b101, 3, 2, 2, 3}, /* Soustrait la valeur du registre Rm (deuxième opérande) à la valeur du registre Rn (premièer opérande) et stocke le résultat dans Rn*/
    {"AND", 0b110, 3, 2, 2, 3}, /* Fait la conjonction bit à bit des deux registres et range le résultat dans le premier op (Rn codée sur 2 bits) */
    {"SWP", 0b111, 3, 2, 2, 3}, /* Echange la valeur du registre Rn (premier opérande) au registre Rm (deuxième opérande) */
    {"MV", 0b00, 2, 2, 3, 3} /* Charge dans le registre Rn (premier opérande) la valeur du registre Rm (second opérande) */
};