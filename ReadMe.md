**Faculty of Media Engineering and Technology  ![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.001.png)Computer Systems Architecture – CSEN601**  

***Project ![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.002.png)General Description ![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.003.png)***

***Project Overview*** 

“Processor design is the design engineering task of creating a processor, a key component of computer hardware. The design process involves choosing an instruction set and a certain execution paradigm, and results in a microarchitecture. The mode of operation of any processor is the execution of lists of instructions. Instructions typically include those to compute or manipulate data values using registers, change or retrieve values in read/write memory, perform relational tests between data values and to control program flow.” 

In this project, you will simulate a fictional processor design and architecture using C. You are asked to choose one of four processor packages described in the upcoming sections. 

***Detailed Description*** 

**Packages Description** 

Package 1: Spicy Von Neumann Fillet with extra shifts *Memory Architecture* 

1) **Architecture**: Von Neumann 

` `Von Neumann Architecture is a digital computer architecture whose design is based on the concept of stored program computers where program data and instruction data are stored in the same memory. 

2) **Memory Size**: 2048 \* 32 ![ref1]

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.005.png)

- The main memory addresses are from 0 to (2^11) - 1 (0 to 2047). 
- Each memory block (row) contains 1 word which is 32 bits (4 bytes). 
- The main memory is word addressable. 
- Addresses from 0 to 1023 contain the program instructions. 
- Addresses from 1024 to 2048 contain the data. 
3) **Registers**: 33 
- Size: 32 bits 
- 31 General-Purpose Registers (GPRS) 
  - Names: R1 to R31 
- 1 Zero Register 
  - Name: R0 
  - Hard-wired value “0” (cannot be overwritten by any instruction). 
- 1 Program Counter 
- Name: PC 
- A program counter is a register in a computer processor that contains the address (location) of the instruction being executed at the current time. 
- As each instruction gets fetched, the program counter is incremented to point to the next instruction to be executed. 

*Instruction Set Architecture* 

1) Instruction Size: 32 bits 
1) Instruction Types: 3 ![ref1]

![ref2]

![ref3]

![ref4]

3) Instruction Count: 12 
- The opcodes are from 0 to 11 according to the instructions order in the following table: 

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.009.png)

- SLL and SRL: R3 will be 0 in the instruction format. 

“||” symbol indicates concatenation (0100 || 1100 = 01001100) 

*Data Path* 

1) Stages: 5 
- All instructions regardless of their type must pass through all 5 stages even if they do not need to access a particular stage. 
- **Instruction Fetch (IF):** Fetches the next instruction from the main memory using the address in the PC (Program Counter), and increments the PC. 
- **Instruction Decode (ID):** Decodes the instruction and reads any operands required from the register file. 
- **Execute (EX):** Executes the instruction. In fact, all ALU operations are done in this stage. 
- **Memory (MEM):** Performs any memory access required by the current instruction. For loads, it would load an operand from the main memory, while for stores, it would store an operand into the main memory. 
- **Write Back (WB):** For instructions that have a result (a destination register), the Write Back writes this result back to the register file. ![ref1]
2) Pipeline: 4 instructions (maximum) running in parallel 
- **Instruction Fetch (IF)** and **Memory (MEM)** can not be done in parallel since they access the same physical memory. 
- At a given clock cycle, you can either have the **IF**, **ID**, **EX**, **WB** stages active, or the **ID**, **EX**, **MEM**, **WB** stages active. 
- Number of clock cycles: 7 + ((n − 1) ∗ 2), where n = number of instructions 
- Imagine a program with 7 instructions: 
  - 7 + (6 ∗ 2) = 19 clock cycles 
- You are required to understand the pattern in the example and implement it. ![ref1]

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.010.jpeg)

- The pattern is as follows: 
- You fetch an instruction every 2 clock cycles starting from clock cycle 1. 
- An instruction stays in the Decode (ID) stage for 2 clock cycles. 
- An instruction stays in the Execute (EX) stage for 2 clock cycles. 
- An instruction stays in the Memory (MEM) stage for 1 clock cycle. 
- An instruction stays in the Write Back (WB) stage for 1 clock cycle. 
- You can not have the Instruction Fetch (IF) and Memory (MEM) stages working in parallel. Only one of them is active at a given clock cycle. 

Package 2: Double McHarvard with cheese circular shifts *Memory Architecture* 

1) Architecture: Harvard 
- Harvard Architecture is the digital computer architecture whose design is based on the concept where there are separate storage and separate buses (signal path) for instruction and 

  data. It was basically developed to overcome the bottleneck of Von Neumann Architecture. 

2) Instruction Memory Size: 1024 \* 16 

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.011.png)

- The instruction memory addresses are from 0 to 2^10 − 1 (0 to 1023). 
- Each memory block (row) contains 1 word which is 16 bits (2 bytes). 
- The instruction memory is word addressable. 
- The program instructions are stored in the instruction memory ![ref1]
3) Data Memory Size: 2048 \* 8 

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.012.png)

- The data memory addresses are from 0 to 2^11 − 1 (0 to 2047). 
- Each memory block (row) contains 1 word which is 8 bits (1 byte). 
- The data memory is word/byte addressable (1 word = 1 byte). 
- The data is stored in the data memory. 
4) Registers: 66 
- Size: 8 bits 
- 64 General-Purpose Registers (GPRS) 
  - Names: R0 to R63 
- 1 Status Register 

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.013.png)

- Name: SREG 
- A status register, flag register, or condition code register (CCR) is a collection of status flag bits for a processor. 
- The status register has 5 flags updated after the execution of specific instructions: 
- Carry Flag (C): Indicates when an arithmetic carry or borrow has been generated out 

of the most significant bit position. 

- Check on 9th bit (bit 8) of UNSIGNED[VALUE1] OP UNSIGNED[VALUE2] ==1 or not. 
- Two’s Complement Overflow Flag (V): Indicates when the result of a signed number operation is too large, causing the high-order bit to overflow into the sign bit. ![ref1]
- If 2 numbers are added, and they both have the same sign (both positive or both 

negative), then overflow occurs (V = 1) if and only if the result has the opposite sign. Overflow never occurs when adding operands with different signs. 

- If 2 numbers are subtracted, and their signs are different, then overflow occurs (V=1) if 

and only if the result has the same sign as the subtrahend. 

- Negative Flag (N): Indicates a negative result in an arithmetic or logic operation. 
  - N = 1 if result is negative. 
  - N = 0 if result is positive or zero. 
- Sign Flag (S): Indicates the expected sign of the result (not the actual sign). 
  - S = N ⊕ V (XORing the negative and overflow flags will calculate the sign flag). 
- Zero Flag (Z): Indicates that the result of an arithmetic or logical operation was zero. 
  - Z = 1 if result is 0. 
  - Z = 0 if result is not 0. 
- Since all registers are 8 bits, and we are only using 5 bits in the Status Register for 

the flags, you are required to keep Bits7:5 cleared “0” at all times in the register. 

- 1 Program Counter 
- Name: PC 
- Type: Special-purpose register with a size of 16 bits (not 8 bits). 
- A program counter is a register in a computer processor that contains the address(location) of the instruction being executed at the current time. 
- As each instruction gets fetched, the program counter is incremented to point to the next instruction to be executed. 

*Instruction Set Architecture* 

1) Instruction Size: 16 bits 
1) Instruction Types: 2 

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.014.png)

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.015.png)

3) Instruction Count: 12 
- The opcodes are from 0 to 11 according to the instructions order in the following 

table: 

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.016.png)

“||” symbol indicates concatenation (0100 || 1100 = 01001100). 

4) The Status Register (SREG) flags are affected by the following instructions: 
- The Carry flag (C) is updated every ADD instruction.
- The Overflow flag (V) is updated every ADD and SUB instruction.
- The Negative flag (N) is updated every ADD, SUB, MUL, AND, OR, SLC, and SRC instruction.
- The Sign flag (S) is updated every ADD and SUB instruction.
- The Zero flag (Z) is updated every ADD, SUB, MUL, AND, OR, SLC, and SRC instruction.
- A flag value can only be updated by the instructions related to it.

*Data Path* 

1) Stages: 3 
- All instructions regardless of their type must pass through all 3 stages. 
- **Instruction Fetch (IF):** Fetches the next instruction from the main memory using the address in the PC (Program Counter), and increments the PC. 
- **Instruction Decode (ID):** Decodes the instruction and reads any operands required from the register file. 
- **Execute (EX):** Executes the instruction. In fact, all ALU operations are done in this stage. 

Moreover, it performs any memory access required by the current instruction. For loads, it would load an operand from the main memory, while for stores, it would store an ![ref1] operand into the main memory. Finally, for instructions that have a result (a destination register), it writes this result back to the register file. 

2) **Number of clock cycles:** 3 + ((n − 1) ∗ 1), where n = number of instructions 
- Imagine a program with 7 instructions: 
  - 3 + (6 ∗ 1) = 9 clock cycles 
- You are required to understand the pattern in the example and implement it. 

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.017.png)

Package 3: Fillet-O-Neumann with moves on the side *Memory Architecture* 

1) Architecture: Von Neumann 
- Von Neumann Architecture is a digital computer architecture whose design is based on the concept of stored program computers where program data and instruction data are stored in the same memory. 
2) Memory Size: 2048 \* 32 ![ref1]

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.018.png)

- The main memory addresses are from 0 to 2^11 − 1 (0 to 2047). 
- Each memory block (row) contains 1 word which is 32 bits (4 bytes). 
- The main memory is word addressable. 
- Addresses from 0 to 1023 contain the program instructions. 
- Addresses from 1024 to 2048 contain the data. 
3) Registers: 33 
- Size: 32 bits 
- 31 General-Purpose Registers (GPRS) 
  - Names: R1 to R31 
- 1 Zero Register 
  - Name: R0 
  - Hard-wired value “0” (cannot be overwritten by any instruction). 
- 1 Program Counter 
- Name: PC 
- A program counter is a register in a computer processor that contains the address(location) of the instruction being executed at the current time. 
- As each instruction gets fetched, the program counter is incremented to point to the next instruction to be executed. 

*Instruction Set Architecture* 

1) Instruction Size: 32 bits 
1) Instruction Types: 3 

![ref2]

![ref3]

![ref4]

3) Instruction Count: 12 
- The opcodes are from 0 to 11 according to the instructions order in the following table: ![ref1]

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.019.png)

- MOVI: R2 will be 0 in the instruction format. 

∗∗ LSL and LSR: R3 will be 0 in the instruction format. 

“||” symbol indicates concatenation (0100 || 1100 = 01001100). 

*Data Path* 

1) Stages: 5 
- All instructions regardless of their type must pass through all 5 stages even if they do not need to access a particular stage. 
- **Instruction Fetch (IF):** Fetches the next instruction from the main memory using the 

  address in the PC (Program Counter), and increments the PC. 

- **Instruction Decode (ID):** Decodes the instruction and reads any operands required from 

the register file. 

- **Execute (EX):** Executes the instruction. In fact, all ALU operations are done in this stage. 
- **Memory (MEM):** Performs any memory access required by the current instruction. For 

loads, it would load an operand from the main memory, while for stores, it would store an operand into the main memory. 

- **Write Back (WB):** For instructions that have a result (a destination register), the Write 

Back writes this result back to the register file. 

2) Pipeline: 4 instructions (maximum) running in parallel 
- **Instruction Fetch (IF)** and **Memory (MEM)** can not be done in parallel since they access the same physical memory.
- At a given clock cycle, you can either have the **IF**, **ID**, **EX**, **WB** stages active, or the **ID**, **EX**, **MEM**, **WB** stages active.![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.020.png)
- Number of clock cycles: 7 + ((n − 1) ∗ 2), where n = number of instructions
- Imagine a program with 7 instructions: 7 + (6 ∗ 2) = 19 clock cycles
- You are required to understand the pattern in the example and implement it.

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.021.jpeg)

- The pattern is as follows: 
- You fetch an instruction every 2 clock cycles starting from clock cycle 1. 
- An instruction stays in the Decode (ID) stage for 2 clock cycles. 
- An instruction stays in the Execute (EX) stage for 2 clock cycles. 
- An instruction stays in the Memory (MEM) stage for 1 clock cycle. 
- An instruction stays in the Write Back (WB) stage for 1 clock cycle. 
- You can not have the Instruction Fetch (IF) and Memory (MEM) stages working in parallel. Only one of them is active at a given clock cycle. ![ref1]

Package 4: Double Big Harvard combo large arithmetic shifts *Memory Architecture* 

1) Architecture: Harvard 
   1. Harvard Architecture is the digital computer architecture whose design is based on the concept where there are separate storage and separate buses (signal path) for instruction and data. It was basically developed to overcome the bottleneck of Von Neumann Architecture. 
1) Instruction Memory Size: 1024 \* 16 

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.022.png)

- The instruction memory addresses are from 0 to 2^10 − 1 (0 to 1023). 
- Each memory block (row) contains 1 word which is 16 bits (2 bytes). 
- The instruction memory is word addressable. 
- The program instructions are stored in the instruction memory 
3) Data Memory Size: 2048 \* 8 

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.023.png)

- The data memory addresses are from 0 to 2^11 − 1 (0 to 2047). 
- Each memory block (row) contains 1 word which is 8 bits (1 byte). 
- The data memory is word/byte addressable (1 word = 1 byte). 
- The data is stored in the data memory. ![ref1]
4) Registers: 66 
- Size: 8 bits 
- 64 General-Purpose Registers (GPRS) 
  - Names: R0 to R63 
- 1 Status Register 

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.024.png)

- Name: SREG 
- A status register, flag register, or condition code register (CCR) is a collection of status flag bits for a processor. 
- The status register has 5 flags updated after the execution of specific instructions: 
- Carry Flag (C): Indicates when an arithmetic carry or borrow has been generated out of the most significant bit position. 
- Check on 9th bit (bit 8) of UNSIGNED[VALUE1] OP UNSIGNED[VALUE2] == 

1 or not. 

- Two’s Complement Overflow Flag (V): Indicates when the result of a signed number operation is too large, causing the high-order bit to overflow into the sign bit. 
- If 2 numbers are added, and they both have the same sign (both positive or both 

negative), then overflow occurs (V = 1) if and only if the result has the opposite 

sign. Overflow never occurs when adding operands with different signs. 

- If 2 numbers are subtracted, and their signs are different, then overflow occurs (V 

= 1) if and only if the result has the same sign as the subtrahend. 

- Negative Flag (N): Indicates a negative result in an arithmetic or logic operation. 
  - N = 1 if result is negative. 
  - N = 0 if result is positive or zero. 
- Sign Flag (S): Indicates the expected sign of the result (not the actual sign). 
  - S = N ⊕ V (XORing the negative and overflow flags will calculate the sign flag). 
- Zero Flag (Z): Indicates that the result of an arithmetic or logical operation was zero. 
  - Z = 1 if result is 0. 
  - Z = 0 if result is not 0. 
- Since all registers are 8 bits, and we are only using 5 bits in the Status Register for the flags, you are required to keep Bits7:5 cleared “0” at all times in the register. ![ref1]
- 1 Program Counter 
- Name: PC 
- Type: Special-purpose register with a size of 16 bits (not 8 bits). 
- A program counter is a register in a computer processor that contains the address(location) of the instruction being executed at the current time. 
- As each instruction gets fetched, the program counter is incremented to point to the next instruction to be executed. 

*Instruction Set Architecture* 

1) Instruction Size: 16 bits 
1) Instruction Types: 2 

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.025.png)

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.026.png)

3) Instruction Count: 12 
- The opcodes are from 0 to 11 according to the instructions order in the following table: 

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.027.png)

“||” symbol indicates concatenation (0100 || 1100 = 01001100). 

4) The Status Register (SREG) flags are affected by the following instructions:
- The Carry flag (C) is updated every ADD instruction.![ref1]
- The Overflow flag (V) is updated every ADD and SUB instruction.
- The Negative flag (N) is updated every ADD, SUB, MUL, ANDI, EOR, SAL, and SAR instruction.
- The Sign flag (S) is updated every ADD and SUB instruction.
- The Zero flag (Z) is updated every ADD, SUB, MUL, ANDI, EOR, SAL, and SAR instruction.
- A flag value can only be updated by the instructions related to it. 

*Data Path* 

1) Stages: 3 
   1. All instructions regardless of their type must pass through all 3 stages. 
   1. **Instruction Fetch (IF):** Fetches the next instruction from the main memory using the address in the PC (Program Counter), and increments the PC. 
   1. **Instruction Decode (ID):** Decodes the instruction and reads any operands required from the register file. 
   1. **Execute (EX):** Executes the instruction. In fact, all ALU operations are done in this stage. Moreover, it performs any memory access required by the current instruction. For loads, it would load an operand from the main memory, while for stores, it would store an operand into the main memory. Finally, for instructions that have a result (a destination register), it writes this result back to the register file. 
1) **Pipeline: 3** instructions (maximum) running in parallel 
- Number of clock cycles: 3 + ((n − 1) ∗ 1), where n = number of instructions 
- Imagine a program with 7 instructions: 
  - 3 + (6 ∗ 1) = 9 clock cycles 
- You are required to understand the pattern in the example and implement it. ![ref1]

![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.028.png)

***Deliverables*** 

The following guidelines must be followed in all packages: 

**Program Flow** 

1) You must write your program in **assembly language** in a text file. 
1) Your must read the instructions from the text file, and parse them according to their types/formats (opcode and other relevant fields). 
1) You must store the parsed version of the instructions in the memory (instruction segment of main memory or instruction memory according to your package). 
1) You should start the execution of your pipelined implementation by fetching the first instruction from the memory (instruction segment of main memory or instruction memory) at Clock Cycle 1. 
1) You should continue the execution based on the example provided in the Datapath section of each package reflecting the different stages working in parallel. 
1) The Clock Cycles can be simulated as a variable that is incremented after finishing the required stages at a given time. 

   Examples: 

Fetch(); ![](Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.029.png)

Decode(); 

Execute; 

// memory(); 

// writeback(); 

Cycle++ 

**Printings** 

The following items must be printed in the console after each Clock Cycle: 

1) The Clock Cycle number. 
1) The Pipeline stages: 
- Which instruction is being executed at each stage? 
- What are the input parameters/values for each stage? 
1) The updates occurring to the registers in case a register value was changed. 
1) The updates occurring in the memory (data segment of main memory or data memory according to your package) in case a value was stored or updated in the memory. ![ref1]
3) The content of all registers after the last clock cycle. 
3) The full content of the memory (main memory or instruction and data memories according to your package) after the last clock cycle. 

***Package Selection*** 

- You are requested to submit your selection of one of the previously described packages through the link: [https://docs.google.com/forms/d/e/1FAIpQLSdIA9pE1yQLsBU7aLz1l- PYCFFP4Rnb9x8UkURh9XqHf3v85Q/viewform?usp=sf_link ](https://docs.google.com/forms/d/e/1FAIpQLSdIA9pE1yQLsBU7aLz1l-PYCFFP4Rnb9x8UkURh9XqHf3v85Q/viewform?usp=sf_link)  
- **Package Selection Deadline:** **Saturday 06 April 2024 at 11:59 pm** 

  *Note: Kindly note that the final assignment will be based on the first come first serve basis to ensure equal distribution of all packages among the teams* 

- You can check your assigned package through the link: [https://docs.google.com/spreadsheets/d/1YYNIWAF_e041cuAKfjcy7hnPAgW90Bqdipq_ zeUq7RM/edit?usp=sharing ](https://docs.google.com/spreadsheets/d/1YYNIWAF_e041cuAKfjcy7hnPAgW90Bqdipq_zeUq7RM/edit?usp=sharing) 

***Project Instructions*** 

Please read the following instructions carefully: 

1) Any case of plagiarism will result in a zero. 
1) Any case of cheating will result in a zero. 
1) A cheating detection tool will be used to compare the submitted projects against all online and offline implementations similar to the project idea. 
   1. The projects that have more than 50% similarity percentage will receive a zero. 
1) It is your responsibility to ensure that you have: 
- Submitted before the deadline. 
- Submitted the correct file(s). 
- Submitted the correct file(s) names. 

***Submission Guidelines*** 

- The submission deadline for submission is **Thursday 16 May 2024 at 11:59 PM** 
- You are requested to submit the following documents: The below deliverables are the ones that will be described in the deliverables section, and below is just examples of the deliverables and the naming convention (video and report is a MUST, we can add extra deliverables which are codes etc) ![ref1]
1. A 1-min video to demonstrate the working code (please narrate and comment on the results)**  
- **name the Video (Project\_Team\_m\_Video.mp4)** 
2. The required project description report (kindly include in the cover page the team number, team name, package number and name, and team members’ names, IDs, and tutorials). 
- **name the report (Project\_Team\_m\_Report.pdf)** 
3. The developed C code of the experiment, the CMakeLists.txt, and any additional library used in a single zip folder 
- **name the Code (Project \_Team\_m\_Code.zip)** 
- Please upload your milestone deliverables to your drive as a .zip file with the following naming format: 

(Ex.: CSEN601\_S24\_Proj\_Package\_**n**\_Team\_**m**.zip) 

*where **m** is your team number and **n** is your package number.* 

- Submit **ONLY** the sharing link through the below form and ***Make sure that you give permission to access*** 
  - [https://docs.google.com/forms/d/e/1FAIpQLSf8i13CHO35cdfx-W6C- JG5l2Q450BAvaus2hPrHPZS3vYk5g/viewform?usp=sf_link ](https://docs.google.com/forms/d/e/1FAIpQLSf8i13CHO35cdfx-W6C-JG5l2Q450BAvaus2hPrHPZS3vYk5g/viewform?usp=sf_link) 

***Evaluation Process*** 

- The evaluation process of the process will be conducted during the first 2-3 days of the revision week. This timing is tentative, exact timings will be announced before the evaluations. 
- The evaluation timetable will be posted on the CMS during the last teaching week. 

***Project Grading*** 

The project will be graded upon multiple criteria for each of the submitted deliverables. These criteria including *(below is just some grading items and more are considered):* 

- The overall functionality of the project. 
- Each technical aspect of the project will be graded as well. 
- The quality of the submission (for example: well-commented and generic code, comprehensive and well-written reports, clear and comprehensive videos, and others). 
- Submission on time with no delays (late submissions will be subject to deduction). ![ref1]
- The evaluation attendance is obligatory for all members and graded upon only the showing up. 
- There is a collective team grade, yet during the evaluation and based on your discussion and answers, individual grades will be added as well. 
- Note extra bonus marks will be added in case of successfully merging the computer systems course project and the operating systems course project (maximum bonus is 1.75% to be added to the total 100% course grade) ![ref1]
***CSEN 601 – Spring 24***  19/19 

[ref1]: Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.004.png
[ref2]: Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.006.png
[ref3]: Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.007.png
[ref4]: Aspose.Words.af7bb3c6-0057-461e-a1c8-6f4e3ff06082.008.png
