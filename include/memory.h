#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdbool.h>

/* ==============================
   Memory Layout Configuration
   ============================== */

#define MEMORY_SIZE        2048      // Total words
#define INSTRUCTION_START  0
#define INSTRUCTION_END    1023
#define DATA_START         1024
#define DATA_END           2047

#define WORD_SIZE          4          // 4 bytes (32 bits)

typedef struct {
    uint32_t data[MEMORY_SIZE];
} Memory;

// Memory Initialization -----------------
void memory_init(Memory* mem);

// Instruction Memory Access -----------------

bool memory_read_instruction(
    Memory* mem,
    uint32_t address,
    uint32_t* instruction
);

bool memory_write_instruction(
    Memory* mem,
    uint32_t address,
    uint32_t instruction
);

// Data Memory Access -----------------

bool memory_read_data(
    Memory* mem,
    uint32_t address,
    uint32_t* value
);

bool memory_write_data(
    Memory* mem,
    uint32_t address,
    uint32_t value
);

// Validation Helpers -----------------

bool is_instruction_address(uint32_t address);

bool is_data_address(uint32_t address);

#endif
