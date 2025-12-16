#include "loader.h"
#include <string.h>
#include <stdio.h>


int getSizeOfTextFile() {
    FILE *file;
    char filename[] = "instrTest.txt";
    int line_count = 0;
    char ch;

    file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            line_count++;
        }
    }

    fclose(file);
    return line_count;
}



void readInstructions() {
    FILE *file;
    char filename[] = "instrTest.txt";
    char line[1000]; // Adjust the size according to your needs
    char *token;
    char *ptr;
    int reg_num;

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int counter = 0;
    while (fgets(line, sizeof(line), file)) {
        token = strtok(line, " ");
        Opcode opcodeO = getOpcode(token);
        uint32_t instruction;
        if (token != NULL) {
            bool isR = false;
            bool isI = false;
            bool isJ = false;
            int opcode;
            switch(opcodeO) {
                case ADD: isR = true; opcode = 0b0000; break;
                case SUB: isR = true; opcode = 0b0001; break;
                case SLL: isR = true; opcode = 0b1000; break;
                case SRL: isR = true; opcode = 0b1001; break;
                case MULI: isI = true; opcode = 0b0010; break;
                case ADDI: isI = true; opcode = 0b0011; break;
                case BNE: isI = true; opcode = 0b0100; break;
                case ANDI: isI = true; opcode = 0b0101; break;
                case ORI: isI = true; opcode = 0b0110; break;
                case LW: isI = true; opcode = 0b1010; break;
                case SW: isI = true; opcode = 0b1011; break;
                case J: isJ = true; opcode = 0b0111; break;
            }
            instruction = (opcode << 28);
            if(isR) {
                token = strtok(NULL, " - ");
                reg_num = strtol(token + 1, &ptr, 10);
                printf("Binary value of R%d: %d\n", reg_num, reg_num);
                instruction += (reg_num << 23);

                token = strtok(NULL, " - ");
                reg_num = strtol(token + 1, &ptr, 10);
                printf("Binary value of R%d: %d\n", reg_num, reg_num);
                instruction += (reg_num << 18);

                token = strtok(NULL, " - ");
                if (strncmp(token, "R", 1) == 0) {
                    reg_num = strtol(token + 1, &ptr, 10);
                    printf("Binary value of R%d: %d\n", reg_num, reg_num);
                    instruction += (reg_num << 13);
                } else {
                    reg_num = strtol(token, &ptr, 10);
                    printf("value of shamt is %d: %d\n", reg_num, reg_num);
                    instruction += reg_num;
                }
            } else if(isI) {
                token = strtok(NULL, " - ");
                reg_num = strtol(token + 1, &ptr, 10);
                printf("Binary value of R%d: %d\n", reg_num, reg_num);
                instruction += (reg_num << 23);

                token = strtok(NULL, " - ");
                reg_num = strtol(token + 1, &ptr, 10);
                printf("Binary value of R%d: %d\n", reg_num, reg_num);
                instruction += (reg_num << 18);
                token = strtok(NULL, " ");
                reg_num = strtol(token, &ptr, 10);
                signed int imm = atoi(token);
                printf("imm value in read: %d\n\n\n",imm);
                printf("instruction before +imm: %d\n",instruction);
                if(imm<0){
                    imm = imm ^ 0b111111111111111111;
                    imm = -(imm + 1);
                    printf("imm: 2's comp:%d\n",imm);
                    instruction+=imm;
                }else{
                    instruction+=imm;
                }
                printf("instruction after +imm: %d\n",instruction);
            } else if(isJ) {
                token = strtok(NULL, " - ");
                reg_num = strtol(token, &ptr, 10);
                printf("value of address is %d: %d\n", reg_num, reg_num);
                instruction += reg_num;
            } else {
                printf("problemo");
            }
        }
        printf("%d was added \n\n",instruction);
        *(memoryUnit+counter) = instruction;
        if(counter == 1023) {
            break;
        }
        counter++;
    }   
    fclose(file);
}