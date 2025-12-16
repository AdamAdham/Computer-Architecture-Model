#ifndef PIPELINE_UTILS_H
#define PIPELINE_UTILS_H

#include <stdint.h>
#include <stdbool.h>

void flushInstructions(int branchInstructionIndex);

bool isLW(char *str);
bool isSW(char *str);
bool isPCInstruction(char *str);
bool notR1Instruction(char *str);
bool isFirst4CharactersInArray(char *str, char *array[], int array_size);

#endif