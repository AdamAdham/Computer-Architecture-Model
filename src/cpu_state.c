#include "cpu_state.h"
#include <string.h>
#include <stdio.h>

// CPU GLOBAL STATE ------------------

uint32_t *memoryUnit = NULL;
uint32_t PC = 0;
uint32_t R[32] = {0};

uint32_t instructions[4] = {0};
uint16_t instructionsStage[4] = {0};
bool instructionActive[4] = {false};

int RegisterDestination[32] = {0};

struct instructionData instructionDataArray[4] = {0};