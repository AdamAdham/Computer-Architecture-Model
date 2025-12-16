#ifndef CPU_STATE_H
#define CPU_STATE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* ================= CPU GLOBAL STATE ================= */

// Main memory
extern uint32_t *memoryUnit;

// Program Counter
extern uint32_t PC;

// Register file
extern uint32_t R[32];

// Pipeline instruction slots
extern uint32_t instructions[4];
extern uint16_t instructionsStage[4];
extern bool instructionActive[4];

// Register hazard tracking
extern int RegisterDestination[32];

/* ================= INSTRUCTION DATA ================= */

struct instructionData {
    int opcode;

    int R1;
    int R2;
    int R3;

    int R1Address;
    int R2Address;
    int R3Address;

    int shamt;
    int funct;

    signed int imm;
    int address;

    int loadStoreAddress;
    int instructionAddress;

    int aluResult;
    int memoryValue;

    bool branch;
    int dependantIndex;
    int clockCycleEntered;
    int PCAtBranch;
};

typedef enum {
    ADD,
    SUB,
    SLL,
    SRL,
    MULI,
    ADDI,
    BNE,
    ANDI,
    ORI,
    LW,
    SW,
    J
} Opcode;

extern struct instructionData instructionDataArray[4];



#endif // CPU_STATE_H
