#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

void fetch(int clockCycle) {
    // In description says that we fetch from memory
    if(PC<1024 && memoryUnit[PC]!=0){
        int i=0;
        while(instructionsStage[i]!=0 && i<4){
            i++;
        }
        if(i>=4) return;
        instructionDataArray[i].clockCycleEntered = clockCycle;
        instructions[i] = memoryUnit[PC];
        char string[50];
        instructionToString(instructions[i], string, sizeof(string));
        instructionDataArray[i].instructionAddress = PC;
        PC = PC + 1;
        instructionDataArray[i].PCAtBranch = PC;
        instructionsStage[i] = 1;
        instructionActive[i] = true;
        
        printf("Instruction:  %s     |      Stage: Fetch \n",string);
    }
}

bool decode(int32_t instructionIndex){
    // get instr and do the same as the task
        int instruction = instructions[instructionIndex];

        instructionDataArray[instructionIndex].opcode = (instruction & 0b11110000000000000000000000000000)>>28;  
        instructionDataArray[instructionIndex].R1Address = (instruction & 0b00001111100000000000000000000000)>>23;  
        instructionDataArray[instructionIndex].R1 = R[instructionDataArray[instructionIndex].R1Address];
        instructionDataArray[instructionIndex].R2Address =  (instruction & 0b00000000011111000000000000000000)>>18;   
        instructionDataArray[instructionIndex].R2 = R[instructionDataArray[instructionIndex].R2Address];
        instructionDataArray[instructionIndex].R3Address = (instruction & 0b00000000000000111110000000000000)>>13; 
        instructionDataArray[instructionIndex].R3 = R[instructionDataArray[instructionIndex].R3Address];
        instructionDataArray[instructionIndex].shamt = (instruction & 0b00000000000000000001111111111111);      
        instructionDataArray[instructionIndex].imm = (instruction & 0b00000000000000111111111111111111)>>0;     
        instructionDataArray[instructionIndex].address = (instruction & 0b00001111111111111111111111111111)>>0;
        instructionDataArray[instructionIndex].branch = false;

        // Most bonus logic

        char *generalRegisterOpcodes[] = {"ADD ", "SUB "};
        char string[50];
        instructionToString(instructions[instructionIndex], string, sizeof(string));
        if(!notR1Instruction(string) && RegisterDestination[instructionDataArray[instructionIndex].R1Address]==-1){
            RegisterDestination[instructionDataArray[instructionIndex].R1Address] = instructionIndex; 
        }

        if(!(string[0]=='J')){
            // Not a jump instruction because jumps dont use registers
            int dependantOnInstructionIndexR2 = RegisterDestination[instructionDataArray[instructionIndex].R2Address];  
            if(instructionDataArray[dependantOnInstructionIndexR2].opcode==10 && instructionsStage[dependantOnInstructionIndexR2]<=3){
                // dependent instruction is a LW instruction and is less than or equal memory stage 
                // So we return false to stall the stages
                return false;
            }
            if(dependantOnInstructionIndexR2!=-1 && dependantOnInstructionIndexR2!=instructionIndex){  
                char string2[50];
                instructionToString(instructions[instructionIndex], string2, sizeof(string2));
                if(instructionDataArray[dependantOnInstructionIndexR2].opcode==10){                    instructionDataArray[instructionIndex].R2 = instructionDataArray[dependantOnInstructionIndexR2].memoryValue;
                }else{
                    instructionDataArray[instructionIndex].R2 = instructionDataArray[dependantOnInstructionIndexR2].aluResult;         // Forwarding
                }    
            }
            if(isFirst4CharactersInArray(string, generalRegisterOpcodes, sizeof(generalRegisterOpcodes) / sizeof(generalRegisterOpcodes[0]))) {   
                // this is an ADD or SUB opcode
                // R3 is also needed  
                int dependantOnInstructionIndexR3 = RegisterDestination[instructionDataArray[instructionIndex].R3Address];  
                if(instructionDataArray[dependantOnInstructionIndexR2].opcode==10 && instructionsStage[dependantOnInstructionIndexR2]<=3){
                    // dependent instruction is a LW instruction and is less than or equal memory stage
                    // So we return false to stall the stages
                    return false;
                }
                if(dependantOnInstructionIndexR3!=-1 && dependantOnInstructionIndexR3!=instructionIndex){  
                    printf("aluResult %d\n\n",instructionDataArray[dependantOnInstructionIndexR3].aluResult);
                    if(instructionDataArray[dependantOnInstructionIndexR2].opcode==10){
                        printf("loadStoreAddress: %d\n",instructionDataArray[dependantOnInstructionIndexR3].loadStoreAddress);
                        instructionDataArray[instructionIndex].R3 = instructionDataArray[dependantOnInstructionIndexR3].memoryValue;
                    }else{
                        instructionDataArray[instructionIndex].R3 = instructionDataArray[dependantOnInstructionIndexR3].aluResult; // Forwarding 
                    }
                }
            }
        }

        instructionsStage[instructionIndex]+=1;
        return true;
}

void execute(int32_t instructionIndex){
    // add all params rs,R3,rt etc and acc to opcode we use the relevant arguement
    // immediate signed
    int opcode = instructionDataArray[instructionIndex].opcode; //.opcode is from the structure
    int R1 = instructionDataArray[instructionIndex].R1;
    int R1Address = instructionDataArray[instructionIndex].R1Address;
    int R2 = instructionDataArray[instructionIndex].R2;
    int R3 = instructionDataArray[instructionIndex].R3;
    int shamt = instructionDataArray[instructionIndex].shamt;
    signed int imm = instructionDataArray[instructionIndex].imm;

    // Handling Negative values
    bool negativeFlag = false;
    int MSB = imm & 0b100000000000000000;
    MSB = MSB >> 17;
    if(MSB==1){
        // Negative number
        negativeFlag = true;
        imm = imm ^ 0b111111111111111111;
        imm = imm + 1;
    }
    int res;
    int address = instructionDataArray[instructionIndex].address;
    switch (opcode)
    {
        case 0:
            // ADD
            instructionDataArray[instructionIndex].aluResult = R2 + R3;
            break;
        case 1:
            // SUB
            instructionDataArray[instructionIndex].aluResult = R2 - R3;
            break;
        case 2:
            // MULI
            if(negativeFlag){
                instructionDataArray[instructionIndex].aluResult = R2 * (-imm);   
            }else{
                instructionDataArray[instructionIndex].aluResult = R2 * imm; 
            }    
            break;

        case 3:
            // ADDI
            if(negativeFlag){
                instructionDataArray[instructionIndex].aluResult = R2 + (-imm);   
            }else{
                instructionDataArray[instructionIndex].aluResult = R2 + imm; 
            }     
            break;

        case 4:
            // BNE
            res = R1-R2;
            printf("PC was %i in Execute Stage \n",instructionDataArray[instructionIndex].PCAtBranch);
            if(res!=0){
                if(negativeFlag){
                    PC = instructionDataArray[instructionIndex].PCAtBranch + (-imm);  //pc + 1 is already done so we'll add the imm directly --> check the remarks document
                }else{
                    PC = instructionDataArray[instructionIndex].PCAtBranch + imm;
                }
                printf("PC was changed to %i in Execute Stage \n",PC);
                instructionDataArray[instructionIndex].branch = true;
            }else{
                printf("PC was unchanged \n");
            }          
            break;

        case 5:
            // ANDI
            if(negativeFlag){   
                instructionDataArray[instructionIndex].aluResult = R2 & (-imm);  
            }else{
                instructionDataArray[instructionIndex].aluResult = R2 & imm;  
            }      
            break;

        case 6:
            // ORI
            if(negativeFlag){
                instructionDataArray[instructionIndex].aluResult = R2 | (-imm);
            }else{
                instructionDataArray[instructionIndex].aluResult = R2 | imm;
            }
            break;

        case 7:
            // J
            instructionDataArray[instructionIndex].branch = true;
            printf("PC was %i in Execute Stage \n",instructionDataArray[instructionIndex].PCAtBranch);
            PC = concatenate_bits(instructionDataArray[instructionIndex].PCAtBranch,address);
            printf("PC was changed to %i in Execute Stage \n",PC);
            break;

        case 8:
            // SLL
            instructionDataArray[instructionIndex].aluResult = R2 << shamt;
            break;

        case 9:
            // SRL
            instructionDataArray[instructionIndex].aluResult = R[R1Address] = R2 >> shamt;  
            break;

        case 10:
            // LW            
            // R1 = memoryUnit[R2+imm];     --> this accesses the memory which is incorrect in execute stage
            //loadStoreAddress holds R2+imm (ALU operation)
            if(negativeFlag){
                instructionDataArray[instructionIndex].loadStoreAddress = R2 + (-imm);
            }else{
                instructionDataArray[instructionIndex].loadStoreAddress = R2 + imm;
            } 
            break;

        case 11:
            // SW
            if(negativeFlag){
                instructionDataArray[instructionIndex].loadStoreAddress = R2 + (-imm);
            }else{
                instructionDataArray[instructionIndex].loadStoreAddress = R2 + imm;
            }
            printf("SW instruction \n");
            break;

    default:
        printf("OPERATION NOT SUPPORTED \n");
        break;
    }
    instructionsStage[instructionIndex]+=1;
}

void memory(int32_t instructionIndex){
    int opcode = instructionDataArray[instructionIndex].opcode;
    int memoryLocation = instructionDataArray[instructionIndex].loadStoreAddress;
    int R1 = instructionDataArray[instructionIndex].R1;
    int R1Address = instructionDataArray[instructionIndex].R1Address;
    if(opcode==10){
        // LW
        if(memoryLocation<0){
            printf("Memory address location %d is invalid at Memory Stage\n",memoryLocation);
        }else{
            instructionDataArray[instructionIndex].memoryValue =  memoryUnit[memoryLocation];
        }
    }else if(opcode==11){
        // SW
        // since only memory is LW and SW
         printf("Memory address location %i was %i in Memory stage \n",memoryLocation,memoryUnit[memoryLocation]);
        if(memoryLocation<1023){
            printf("Memory address location %i was not changed (due to invalid memory address) \n",memoryLocation);
        }else{
            memoryUnit[memoryLocation] = R1;
            printf("Memory address location %i has changed to %i in Memory stage \n",memoryLocation,memoryUnit[memoryLocation]);
        }
    }
    instructionsStage[instructionIndex] += 1;
}

bool writeback(int32_t instructionIndex){
    char *generalRegisterOpcodes[] = {"ADD ", "SUB ", "MULI", "ADDI", "ANDI", "ORI ", "SLL ","SRL "};
    char string[50];
    instructionToString(instructions[instructionIndex], string, sizeof(string));
    printf("Instruction:  %s     |      Stage: Writeback \n",string);
    int R1Address = instructionDataArray[instructionIndex].R1Address;
    if(isFirst4CharactersInArray(string, generalRegisterOpcodes, sizeof(generalRegisterOpcodes) / sizeof(generalRegisterOpcodes[0]))) {     
        printf("R%i was %i in Write Back stage \n",R1Address,R[R1Address]);
        if(R1Address==0){
            printf("R0 has not been changed \n\n");
        }else{       
            R[R1Address] = instructionDataArray[instructionIndex].aluResult;
            printf("R%i has changed to %i in Write Back stage \n\n",R1Address,R[R1Address]);
        } 
        
    }else if(isLW(string)){
        int R1 = instructionDataArray[instructionIndex].R1;
        int memoryLocation = instructionDataArray[instructionIndex].loadStoreAddress;
        if(memoryLocation<0){
            printf("Memory address location %d is invalid at Write Back Stage\n",memoryLocation);
        }else{
            printf("R%i was %i in Write Back stage \n",R1Address,R1);
            R[R1Address] =  instructionDataArray[instructionIndex].memoryValue;
            printf("R%i has changed to %i in Write Back stage \n",R1Address,R[R1Address]);
        }
    }

    // Reset data for that instruction
    bool flushed = false;
    if(instructionDataArray[instructionIndex].branch){
        // If a J or BNE instruction
        // &&
        // branch will occur (BNE condition is true || J instruction)
        flushInstructions(instructionIndex);
        flushed = true;
    }
    instructions[instructionIndex]=-1;
    instructionActive[instructionIndex] = false;
    instructionDataArray[instructionIndex].opcode = 0;  
    instructionDataArray[instructionIndex].R1Address = 0;
    instructionDataArray[instructionIndex].R1 = 0;
    instructionDataArray[instructionIndex].R2Address = 0; 
    instructionDataArray[instructionIndex].R2 =
    instructionDataArray[instructionIndex].R3Address = 0;
    instructionDataArray[instructionIndex].R3 = 0;
    instructionDataArray[instructionIndex].shamt = 0;
    instructionDataArray[instructionIndex].imm = 0; 
    instructionDataArray[instructionIndex].address = 0;
    instructionDataArray[instructionIndex].branch = false;
    instructionsStage[instructionIndex]=0;
    return flushed;
    
}