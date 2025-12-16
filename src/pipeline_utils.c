#include "pipeline_utils.h"
#include <string.h>
#include <stdio.h>


void flushInstructions(int branchInstructionIndex){
    int branchClockCycleEntered = instructionDataArray[branchInstructionIndex].clockCycleEntered;
    for(int i=0;i<4;i++){
        char string[50];
        instructionToString(instructions[i], string, sizeof(string));
        int clockCycleEntered =  instructionDataArray[i].clockCycleEntered;        
        if(i!=branchInstructionIndex && clockCycleEntered>branchClockCycleEntered && clockCycleEntered!=branchClockCycleEntered+6){
            // 1st condition: Flush the instructions that is not the branch one
            // &&
            // 2nd condition: Flush the instructions that came after the branch not before
            char string[50];
            instructionToString(instructions[i], string, sizeof(string));
            printf("FLush:  %s\n",string);
            instructions[i] = -1;
            instructionsStage[i] = 0; 
            instructionActive[i] = false;
        }  
    }
    printf("\n");
}

bool isLW(char *str) {
    // Extract the first 4 characters of the string
    char first_2_chars[2];  // Make room for the null terminator
    strncpy(first_2_chars, str, 2);

    if(strcmp(first_2_chars,"LW")==0){
        return true;
    }    
    return false;  // No match found
}


bool isSW(char *str) {
    // Extract the first 4 characters of the string
    char first_2_chars[2];  // Make room for the null terminator
    strncpy(first_2_chars, str, 2);

    if(strcmp(first_2_chars,"SW")==0){
        return true;
    }    
    return false;  // No match found
}

bool isPCInstruction(char *str) {
    // Extract the first 4 characters of the string
    char first_3_chars[3];  // Make room for the null terminator
    strncpy(first_3_chars, str, 3);
    char firstChar = str[0];

    if(strcmp(first_3_chars,"BNE")==0 || firstChar == 'J'){
        return true;
    }    
    return false;  // No match found
}


bool notR1Instruction(char *str) {
    // Extract the first 4 characters of the string
    char first_3_chars[3];  // Make room for the null terminator
    strncpy(first_3_chars, str, 3);

    char first_2_chars[2];  // Make room for the null terminator
    strncpy(first_2_chars, str, 2);

    char firstChar = str[0];

    if(strcmp(first_3_chars,"BNE")==0 || firstChar == 'J' || strcmp(first_2_chars,"SW")==0){
        return true;
    }    
    return false;  // No match found
}


bool isFirst4CharactersInArray(char *str, char *array[], int array_size) {
    // Extract the first 4 characters of the string
    char first_4_chars[5];  // Make room for the null terminator
    strncpy(first_4_chars, str, 4);
    first_4_chars[4] = '\0';  // Null terminate the string

    // Iterate over the array of strings
    for (int i = 0; i < array_size; i++) {
        // Compare the first 4 characters with each string in the array
        if (strcmp(first_4_chars, array[i]) == 0) {
            return true;  // Match found
        }
    }

    return false;  // No match found
}