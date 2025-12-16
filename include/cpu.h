#ifndef CPU_H
#define CPU_H

#include "instruction.h"
#include <stdint.h>
#include <stdbool.h>

void fetch(uint32_t* memoryUnit, InstructionData* instructions, bool* instructionActive, uint32_t* PC, int* instructionsStage, int clockCycle);
bool decode(InstructionData* instructions, int* instructionsStage, int instructionIndex, int* R, int* RegisterDestination);
void execute(InstructionData* instructions, int instructionIndex);
void memoryStage(InstructionData* instructions, uint32_t* memoryUnit, int instructionIndex);
bool writeback(InstructionData* instructions, int* R, int* instructionsStage, int* instructionActive, int instructionIndex);

#endif
