#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "cpu.h"
#include "cpu_state.h"
#include "instruction_utils.h"
#include "loader.h"
#include "pipeline_utils.h"
#include "memory.h"


int main() {
    memoryUnit = malloc(2048 * sizeof(uint32_t));
    memoryUnit[1024] = 200;
    for(int i=0;i<32;i++){
        RegisterDestination[i] = -1;
    }
    readInstructions();
    for (int i = 0; i <= sizeof(memoryUnit); i++) {
        printf("instruction%d is %d\n", i,memoryUnit[i]);
    }
    int clockCycle = 1;
    int decodeCount = 0;
    int executeCount = 0;
    int decodeIndex = -1;
    int executeIndex = -1;
    bool flushed = false;

    int stallCounter = 0;
    bool stallFlag = false;
    bool run = true; // Just for the extra print of clock cycle

    bool runningInstruction = false;
    printf("\n\n\n\n\n");

    // Stalls are done here
    while((((memoryUnit[PC]!=0 && PC<1024)) || runningInstruction) && run){
        printf("Clock Cycle: %d \n\n",clockCycle);
        runningInstruction = false;
    
        // FETCH
        if((clockCycle%2==1 && stallCounter%2==0) || (clockCycle%2==0 && stallCounter%2==1)&& !stallFlag){
            // every 2 clock cycles we fetch
            fetch(clockCycle);
        }
        for(int i=0;i<4;i++){
            if(instructionActive[i]==false){
                // printf("boolean: %d\n",instructionsStage[i]==1 && (decodeIndex==i||decodeIndex==-1) && !stallFlag);
                char string[50];
                instructionToString(instructions[i], string, sizeof(string));
                if(instructionsStage[i]==4 && !stallFlag){     //check if we finished the execute stage  --> go to WB
                    flushed = writeback(i);
                }
                if(instructionsStage[i]==3 && ((clockCycle%2==0 && stallCounter%2==0 ) || (clockCycle%2==1 && stallCounter%2==1) || (instructionsStage[i]==3 && stallFlag))){  //check if we finished the execute stage + no fetch operation is being executed
                    printf("Instruction:  %s index = %d   |      Stage: Memory \n\n",string,instructionDataArray[i].instructionAddress+1);
                    memory(i);
                    runningInstruction = true;
                }
                if(instructionsStage[i]==2&&(executeIndex==i||executeIndex==-1 && !stallFlag)){  //check if we finished the decode stage --> go to execute
                    printf("Instruction:  %s index = %d  |      Stage: Execute \n\n",string,instructionDataArray[i].instructionAddress+1);
                    executeCount++;
                    executeIndex = i;
                    runningInstruction = true;
                }
                if(instructionsStage[i]==1 && (decodeIndex==i||decodeIndex==-1) && !stallFlag){  //check if we finished the fetch stage
                    if(decodeCount==0){
                        printf("Instruction:  %s index = %d  |      Stage: Decode \n\n",string,instructionDataArray[i].instructionAddress+1);
                    }
                    decodeCount++;  //to check that you completed the 2 clock cycles
                    decodeIndex = i; // to prevent simultaneous decode of instructions
                    runningInstruction = true;
                }
                if(executeCount==2 && !stallFlag){
                    execute(executeIndex);
                    executeCount=0;
                    executeIndex=-1;
                    runningInstruction = true;
                }
                if(flushed){
                    // When a 
                    if(memoryUnit[PC]==0){
                    // prevent extra print of clock cycle
                        run = false;
                    }
                    decodeCount=0;
                    decodeIndex=-1;
                    executeCount=0;
                    executeIndex=-1;
                    flushed = false;
                }
            }
        }
        
        if(decodeCount==2){  //to reset the decode count
            char string[50];
            instructionToString(instructions[decodeIndex], string, sizeof(string));
            bool decodeFinished = decode(decodeIndex);
            if(decodeFinished){
                decodeCount=0;
                decodeIndex=-1;
                stallFlag = false;
                printf("Instruction:  %s  |      Stage: Decode \n\n",string);                      
            }else{
                stallFlag = true;
                stallCounter++;
                printf("Decode %s Stalled \n",string);
            }
            runningInstruction = true;       
        }
        instructionActive[0] = false;
        instructionActive[1] = false;
        instructionActive[2] = false;
        instructionActive[3] = false;
        
        printf("\n");
        clockCycle++;
    }
    printf("\n\nRegisters: \n");
    printf("PC = %i \n",PC);
    for(int i=0;i<sizeof(R)/sizeof(uint32_t);i++){
        printf("R%i = %i \n",i ,R[i]);
    }
    printf("\n\nMemory: \n");
    for(int i=0;i<2048;i++){
        if(!(memoryUnit[i]==0)){
            printf("Memory[%d] = %d \n",i,memoryUnit[i]);
        }
    }     
    free(memoryUnit);
    return 0;
}