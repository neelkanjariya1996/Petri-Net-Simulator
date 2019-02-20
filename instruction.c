#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INSTRUCTIONS 16

int
main() {

	FILE *read_instructions;
        char str[15];
        char *pch;
        int ret;
        int i = 0;
	char c;
	int number_of_instructions = 0;
	int opcode[MAX_INSTRUCTIONS] = {0};
	int destination_register[MAX_INSTRUCTIONS] = {0};
	int first_source_operand[MAX_INSTRUCTIONS] = {0};
	int second_source_operand[MAX_INSTRUCTIONS] = {0};
	int dest_reg = 0;
	int first_source = 0;
	int second_source = 0;

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

	fclose(read_instructions);
       	
	printf("The number of instructions = %d\n", number_of_instructions);
       		
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
	
	if (number_of_instructions <= MAX_INSTRUCTIONS) {
		for (i = 0; i < number_of_instructions; i++) {
			printf("Instruction = %d\t   Opcode = %d\t   Destination Register = %d\t", i, opcode[i], destination_register[i]); 
			printf("First Source operand = %d\t   Second Source operand = %d\n", first_source_operand[i], second_source_operand[i]);
		}

	}
	
        fclose(read_instructions);

        return 0;
}
