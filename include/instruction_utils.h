#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdint.h>
#include <stdbool.h>

char* getStringOpcode(int opcode, char* returnValue);
char* instructionToString(int instruction, char* buffer, size_t buffer_size);
Opcode getOpcode(const char *opcode_str);
uint32_t concatenate_bits(uint32_t PC, uint32_t imm);


#endif
