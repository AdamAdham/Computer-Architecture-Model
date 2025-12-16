#include "instruction_utils.h"
#include <string.h>
#include <stdio.h>

char* getStringOpcode(int opcode,char* returnValue) {
    switch(opcode) {
        case 0: strcpy(returnValue,"ADD"); break;
        case 1: strcpy(returnValue,"SUB"); break;
        case 2: strcpy(returnValue,"MULI"); break;
        case 3: strcpy(returnValue,"ADDI"); break;
        case 4: strcpy(returnValue,"BNE"); break;
        case 5: strcpy(returnValue,"ANDI"); break;
        case 6: strcpy(returnValue,"ORI"); break;
        case 7: strcpy(returnValue,"J"); break;
        case 8: strcpy(returnValue,"SLL"); break;
        case 9: strcpy(returnValue,"SRL"); break;
        case 10: strcpy(returnValue,"LW"); break;
        case 11: strcpy(returnValue,"SW"); break;

        default: return "UNKNOWN";
    }
}


char* instructionToString(int instruction, char* buffer, size_t buffer_size){
        int opcode = (instruction & 0b11110000000000000000000000000000)>>28; 
        char opcodeString[5];
        getStringOpcode(opcode,opcodeString);
        int R1Address = (instruction & 0b00001111100000000000000000000000)>>23;  
        int R2Address =  (instruction & 0b00000000011111000000000000000000)>>18;   
        int R3Address = (instruction & 0b00000000000000111110000000000000)>>13; 
        int shamt = (instruction & 0b00000000000000000001111111111111);      
        int imm = (instruction & 0b00000000000000111111111111111111)>>0; 
        int MSB = imm & 0b100000000000000000;
        MSB = MSB >> 17;
        if(MSB==1){
            // Negative number
            imm = imm ^ 0b111111111111111111;
            imm = imm + 1;
            imm = -imm;
        }  

        int address = (instruction & 0b00001111111111111111111111111111)>>0;
    switch(opcode) {
        case 0:
        case 1: snprintf(buffer, buffer_size,"%s R%d R%d R%d",opcodeString,R1Address,R2Address,R3Address); break;
        case 2: 
        case 3:
        case 4: 
        case 5: 
        case 6: 
        case 10: // Getting all that use R1 R2 imm
        case 11: snprintf(buffer, buffer_size,"%s R%d R%d %d",opcodeString,R1Address,R2Address,imm); break;
        case 7: snprintf(buffer, buffer_size,"%s %d",opcodeString,address); break;
        case 8: 
        case 9: snprintf(buffer, buffer_size,"%s R%d R%d %d",opcodeString,R1Address,R2Address,shamt); break;
        default: "";break;
    }
}

Opcode getOpcode(const char *opcode_str) {
    if (strcmp(opcode_str, "ADD") == 0) {
        return ADD;
    } else if (strcmp(opcode_str, "SUB") == 0) {
        return SUB;
    } else if (strcmp(opcode_str, "SLL") == 0) {
        return SLL;
    } else if (strcmp(opcode_str, "SRL") == 0) {
        return SRL;
    } else if (strcmp(opcode_str, "MULI") == 0) {
        return MULI;
    } else if (strcmp(opcode_str, "ADDI") == 0) {
        return ADDI;
    } else if (strcmp(opcode_str, "BNE") == 0) {
        return BNE;
    } else if (strcmp(opcode_str, "ANDI") == 0) {
        return ANDI;
    } else if (strcmp(opcode_str, "ORI") == 0) {
        return ORI;
    } else if (strcmp(opcode_str, "LW") == 0) {
        return LW;
    } else if (strcmp(opcode_str, "SW") == 0) {
        return SW;
    } else if (strcmp(opcode_str, "J") == 0) {
        return J;
    } else {
        return -1; // unknown opcode
    }
}

uint32_t concatenate_bits(uint32_t PC, uint32_t imm) {
    // Extract the desired bits from PC and imm
    uint32_t PC_bits = PC & 0xF0000000;  // PC[31:28]
    uint32_t imm_bits = imm & 0x0FFFFFFF;   // imm[27:0]

    // Concatenate the extracted bits
    uint32_t concatenated_value = PC_bits | imm_bits;

    return concatenated_value;
}