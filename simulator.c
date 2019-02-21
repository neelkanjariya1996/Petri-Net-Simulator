#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INSTRUCTIONS 16
#define MAX_DATAMEMORY 8
#define MAX_REGISTERS 8

int
read_datamemory_file(int M[], int number_of_memory_locations) {

        FILE *read_datamemory;
        char str[6];
        char *pch;
        int memory_index = 0;
        int memory_value = 0;
        int ret = 0;
        int i = 0;

        read_datamemory = fopen("datamemory.txt", "r");
        if (read_datamemory == NULL) {
                fprintf(stderr, "Error reading file\n");
                return 1;
        }

        while (ret = fscanf(read_datamemory, "%s", str)) {

                if (ret == EOF) {
                        break;
                }
                
		pch = strtok(str, "<,>\n");
                memory_index = atoi(pch);
                for (i = 0; i < number_of_memory_locations; i++) {
                        if (memory_index == i) {
                                if (pch != NULL) {
                                        pch = strtok (NULL, "<,>\n");
                                        memory_value = atoi(pch);
                                        M[i] = memory_value;
                                }
                        }
                }

        }

        fclose(read_datamemory);

        return 0;
}

int
update_datamemory_file(int M[], int number_of_memory_locations) {

        FILE *read_datamemory;
        int i = 0;

        read_datamemory = fopen("datamemory.txt", "w");
        if (read_datamemory == NULL) {
                fprintf(stderr, "Error reading file\n");
                return 1;
        }

        for (i = 0; i < number_of_memory_locations; i++) {
                fprintf(read_datamemory, "<%d,%d>\n", i, M[i]);
        }
	
        fclose(read_datamemory);

        return 0;
}

int 
read_register_file(int R[], int number_of_registers) {

	FILE *read_registers;
        char str[8];
        char *pch;
        int register_index = 0;
        int register_value = 0;
        int ret = 0;
        int i = 0;

        read_registers = fopen("registers.txt", "r");
        if (read_registers == NULL) {
                fprintf(stderr, "Error reading file\n");
                return 1;
        }

        while (ret = fscanf(read_registers, "%s", str)) {

                if (ret == EOF) {
                        break;
                }

                pch = strtok(str, "<R,>\n");
                register_index = atoi(pch);
                for (i = 0; i < number_of_registers; i++) {
                        if (register_index == i) {
                                if (pch != NULL) {
                                        pch = strtok (NULL, "<R,>\n");
                                        register_value = atoi(pch);
                                        R[i] = register_value;
                                }
                        }
                }

        }

        fclose(read_registers);

	return 0;
}

int
update_register_file(int R[], int number_of_registers) {

	FILE *read_registers;
	int i = 0;
	
	read_registers = fopen("registers.txt", "w");
        if (read_registers == NULL) {
                fprintf(stderr, "Error reading file\n");
                return 1;
        }

        for (i = 0; i < number_of_registers; i++) {
                fprintf(read_registers, "<R%d,%d>\n", i, R[i]);
        }

        fclose(read_registers);

	return 0;
}

int
instruction_count() {

	FILE *read_instructions;
	char c;
	int number_of_instructions = 0;

        read_instructions = fopen("instructions.txt", "r");
        if (read_instructions == NULL) {
                fprintf(stderr, "Error reading file\n");
                return 1;
        }

	for (c = getc(read_instructions); c != EOF; c = getc(read_instructions)) {
		if (c == '\n') {
			number_of_instructions = number_of_instructions + 1;
		}
	}
	printf("The number of instructions = %d\n", number_of_instructions);

	fclose(read_instructions);
	
	return number_of_instructions;
}

int
read_instructions(int opcode[], int destination_register[], int first_source_operand[], int second_source_operand[], int number_of_instructions) {

	FILE *read_instructions;
        char str[15];
        char *pch;
        int ret;
        int i = 0;
	int dest_reg = 0;
	int first_source = 0;
	int second_source = 0;

	read_instructions = fopen("instructions.txt", "r");
        if (read_instructions == NULL) {
                fprintf(stderr, "Error reading file\n");
                return 1;
        }

	if (number_of_instructions > MAX_INSTRUCTIONS) {
		printf("Maximum number of instruction allowed is 16\n");
	}
	
	i = 0;
	if (number_of_instructions <= MAX_INSTRUCTIONS) {
		while (ret = fscanf(read_instructions, "%s", str)) {

                	if (ret == EOF) {
                        	break;
                	}	
		
			pch = strtok(str,"<,>\n");
			while (pch != NULL) {
				if (!(strcmp(pch, "ADD"))) {
					opcode[i] = 1;
				} else if (!(strcmp(pch, "SUB"))) {
					opcode[i] = 2;
				} else if (!(strcmp(pch, "AND"))) {
					opcode[i] = 3;
				} else if (!(strcmp(pch, "OR"))) { 
					opcode[i] = 4;
				} else if (!(strcmp(pch, "LD"))) { 
					opcode[i] = 5;
				}
			
				pch = strtok (NULL, "<R,>\n");
				if (pch != NULL) {
					dest_reg = atoi(pch);
					destination_register[i] = dest_reg;
				}

				pch = strtok (NULL, "<R,>\n");
				if (pch != NULL) {
					first_source = atoi(pch);
					first_source_operand[i] = first_source;
				}

				pch = strtok (NULL, "<R,>\n");
				if(pch != NULL) {
					second_source = atoi(pch);
					second_source_operand[i] = second_source;
				}
			}
			i++;
		}
        }
/*	
	if (number_of_instructions <= MAX_INSTRUCTIONS) {
		for (i = 0; i < number_of_instructions; i++) {
			printf("Instruction = %d\t   Opcode = %d\t   Destination Register = %d\t", i, opcode[i], destination_register[i]); 
			printf("First Source operand = %d\t   Second Source operand = %d\n", first_source_operand[i], second_source_operand[i]);
		}

	}
*/	
        fclose(read_instructions);

        return 0;
}

void
print_registers(int R[]) {

	int i = 0;

	for (i = 0; i < MAX_REGISTERS; i++) {
		printf("<R%d,%d>", i, R[i]);
	}
	printf("\n");

}


void
print_datamemory(int M[]) {

	int i = 0;

	for (i = 0; i < MAX_DATAMEMORY; i++) {
		printf("<%d,%d>", i, M[i]);
	}
	printf("\n");

}

void
performing_instructions (int R[], int M[], int opcode[], int destination_register[], int first_source_operand[], int second_source_operand[], int number_of_instructions) {

	int d = 0;
	int s1 = 0;
	int s2 = 0;
	int i = 0;
	int ld = 0;

	for (i = 0; i < number_of_instructions; i++) {
		
		d = destination_register[i];
		s1 = first_source_operand[i];
		s2 = second_source_operand[i];
		
		printf("INSTRUCTION: %d\n", i);
		if (opcode[i] == 1) {
			R[d] = R[s1] + R[s2];
			update_register_file(R, MAX_REGISTERS);
			print_registers(R);
		} else if (opcode[i] == 2) {
			R[d] = R[s1] - R[s2];
			update_register_file(R, MAX_REGISTERS);
			print_registers(R);
		} else if (opcode[i] == 3) {
			R[d] = R[s1] && R[s2];
			update_register_file(R, MAX_REGISTERS);
			print_registers(R);
		} else if (opcode[i] == 4) {
			R[d] = R[s1] || R[s2];
			update_register_file(R, MAX_REGISTERS);
			print_registers(R);
		} else if (opcode[i] == 5) {
			ld = R[s1] + R[s2];
			R[d] = M[ld];
			update_register_file(R, MAX_REGISTERS);
			print_registers(R);
		}

	}

	printf("\n");

}

int
main () {

	 int R[MAX_REGISTERS] = {0};
	 int M[MAX_DATAMEMORY] = {0};
	 int opcode[MAX_INSTRUCTIONS] = {0};
	 int destination_register[MAX_INSTRUCTIONS] = {0};
	 int first_source_operand[MAX_INSTRUCTIONS] = {0};
	 int second_source_operand[MAX_INSTRUCTIONS] = {0};
	 int number_of_instructions = 0;
	 
	 number_of_instructions = instruction_count();
	 if(number_of_instructions > MAX_INSTRUCTIONS) {
		 printf("MAXIMUM NUMBER OF INSTRUCTIONS ALLOWED IS 16\n");
		 return 0;
	 }

	 //printf("HII\n");
	 read_register_file(R, MAX_REGISTERS);
	 //printf("reading register file\n");
	 update_register_file(R, MAX_REGISTERS);
	 //printf("updating register fie\n");
         read_datamemory_file(M, MAX_DATAMEMORY);
	 //printf("reading data memory\n");
         update_datamemory_file(M, MAX_DATAMEMORY);
	 //printf("updating data memory\n");
	 read_instructions(opcode, destination_register, first_source_operand, second_source_operand, number_of_instructions);
	 //printf("reading instructions\n");
	 performing_instructions (R, M, opcode, destination_register, first_source_operand, second_source_operand, number_of_instructions);
	 //printf("performing instructions\n");

         return 0;
}
