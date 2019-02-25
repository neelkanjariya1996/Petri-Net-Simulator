#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INSTRUCTIONS 16			//Maximum number of instructions that are allowed
#define MAX_DATAMEMORY 8			//MAximum number of memory locations allowed
#define MAX_REGISTERS 8				//Maximum number of registers

typedef struct inm_t_ {
	int opcode[MAX_INSTRUCTIONS];
	int dest_reg[MAX_REGISTERS];
	int src1[MAX_REGISTERS];
	int src2[MAX_REGISTERS];
} inm_t;

typedef struct inb_t_ {
	int opcode[MAX_INSTRUCTIONS];
	int dest_reg[MAX_REGISTERS];
	int src1[MAX_REGISTERS];
	int src2[MAX_REGISTERS];
} inb_t;

typedef struct lib_t_ {
	int opcode[MAX_INSTRUCTIONS];
	int dest_reg[MAX_REGISTERS];
	int src1[MAX_REGISTERS];
	int src2[MAX_REGISTERS];
} lib_t;

typedef struct aib_t_ {
	int opcode[MAX_INSTRUCTIONS];
	int dest_reg[MAX_REGISTERS];
	int src1[MAX_REGISTERS];
	int src2[MAX_REGISTERS];
} aib_t;

typedef struct adb_t_ {
	int dest_reg[MAX_REGISTERS];
	int mem_add;
} adb_t;

typedef struct reb_t_ {
	int dest_reg[MAX_REGISTERS];
	int val;
} reb_t;

void
print_rgf (int R[]) {
	
	int i = 0;

	printf("RGF:");
	for (i = 0; i < MAX_REGISTERS - 1; i++) {
		printf("<R%d,%d>,", i, R[i]);
	}
	printf("<R7,%d>", R[7]);
	printf("\n");

}

void
print_dam (int M[]) {
	
	int i = 0;

	printf("DAM:");
	for (i = 0; i < MAX_DATAMEMORY - 1; i++) {
		printf("<%d,%d>,", i, M[i]);
	}
	printf("<7,%d>", M[i]);
	printf("\n");

}

int
read_dam(int M[]) {

        FILE *read_dam;
        char str[6];
        char *pch;
        int mem_ind = 0;
        int mem_val = 0;
        int ret = 0;
        int i = 0;

        read_dam = fopen("datamemory.txt", "r");
        if (read_dam == NULL) {
                fprintf(stderr, "Error reading file\n");
                return 1;
        }

        while (ret = fscanf(read_dam, "%s", str)) {

                if (ret == EOF) {
                        break;
                }
                
		pch = strtok(str, "<,>\n");
                mem_ind = atoi(pch);
                for (i = 0; i < MAX_DATAMEMORY; i++) {
                        if (mem_ind == i) {
                                if (pch != NULL) {
                                        pch = strtok (NULL, "<,>\n");
                                        mem_val = atoi(pch);
                                        M[i] = mem_val;
                                }
                        }
                }

        }

        fclose(read_dam);

        return 0;
}

int
update_dam(int M[]) {

        FILE *read_dam;
        int i = 0;

        read_dam = fopen("datamemory.txt", "w");
        if (read_dam == NULL) {
                fprintf(stderr, "Error reading file\n");
                return 1;
        }

        for (i = 0; i < MAX_DATAMEMORY; i++) {
                fprintf(read_dam, "<%d,%d>\n", i, M[i]);
        }
	
        fclose(read_dam);

        return 0;
}

int 
read_reg(int R[]) {

	FILE *read_reg;
        char str[8];
        char *pch;
        int reg_ind = 0;
        int reg_val = 0;
        int ret = 0;
        int i = 0;

        read_reg = fopen("registers.txt", "r");
        if (read_reg == NULL) {
                fprintf(stderr, "Error reading file\n");
                return 1;
        }

        while (ret = fscanf(read_reg, "%s", str)) {

                if (ret == EOF) {
                        break;
                }

                pch = strtok(str, "<R,>\n");
                reg_ind = atoi(pch);
                for (i = 0; i < MAX_REGISTERS; i++) {
                        if (reg_ind == i) {
                                if (pch != NULL) {
                                        pch = strtok (NULL, "<R,>\n");
                                        reg_val = atoi(pch);
                                        R[i] = reg_val;
                                }
                        }
                }

        }

        fclose(read_reg);

	return 0;
}

int
update_reg(int R[]) {

	FILE *read_reg;
	int i = 0;
	
	read_reg = fopen("registers.txt", "w");
        if (read_reg == NULL) {
                fprintf(stderr, "Error reading file\n");
                return 1;
        }

        for (i = 0; i < MAX_REGISTERS; i++) {
                fprintf(read_reg, "<R%d,%d>\n", i, R[i]);
        }

        fclose(read_reg);

	return 0;
}

int
inst_count() {

	FILE *read_inst;
	char c;
	int num_of_inst = 0;

        read_inst = fopen("instructions.txt", "r");
        if (read_inst == NULL) {
                fprintf(stderr, "Error reading file\n");
                return 1;
        }

	for (c = getc(read_inst); c != EOF; c = getc(read_inst)) {
		if (c == '\n') {
			num_of_inst = num_of_inst + 1;
		}
	}
	printf("The number of instructions = %d\n", num_of_inst);

	fclose(read_inst);
	
	return num_of_inst;
}

int
read_inst(int opcode[], int dest_reg[], int src1[], int src2[], int num_of_inst) {

	FILE *read_inst;
        char str[15];
        char *pch;
        int ret;
        int i = 0;
	int destination_register = 0;
	int first_source = 0;
	int second_source = 0;

	read_inst = fopen("instructions.txt", "r");
        if (read_inst == NULL) {
                fprintf(stderr, "Error reading file\n");
                return 1;
        }

	i = 0;
	if (num_of_inst <= MAX_INSTRUCTIONS) {
		while (ret = fscanf(read_inst, "%s", str)) {

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
					destination_register = atoi(pch);
					dest_reg[i] = destination_register;
				}

				pch = strtok (NULL, "<R,>\n");
				if (pch != NULL) {
					first_source = atoi(pch);
					src1[i] = first_source;
				}

				pch = strtok (NULL, "<R,>\n");
				if(pch != NULL) {
					second_source = atoi(pch);
					src2[i] = second_source;
				}
			}
			i++;
		}
        }
        
	fclose(read_inst);

        return 0;
}

void
performing_inst (int R[], int M[], int opcode[], int dest_reg[], int src1[], int src2[], int num_of_inst) {

	int d = 0;
	int s1 = 0;
	int s2 = 0;
	int i = 0;
	int ld = 0;

	for (i = 0; i < num_of_inst; i++) {
		
		d = dest_reg[i];
		s1 = src1[i];
		s2 = src2[i];
		
		printf("INSTRUCTION: %d\n", i);
		if (opcode[i] == 1) {
			R[d] = R[s1] + R[s2];
			update_reg(R);
			print_rgf(R);
		} else if (opcode[i] == 2) {
			R[d] = R[s1] - R[s2];
			update_reg(R);
			print_rgf(R);
		} else if (opcode[i] == 3) {
			R[d] = R[s1] && R[s2];
			update_reg(R);
			print_rgf(R);
		} else if (opcode[i] == 4) {
			R[d] = R[s1] || R[s2];
			update_reg(R);
			print_rgf(R);
		} else if (opcode[i] == 5) {
			ld = R[s1] + R[s2];
			R[d] = M[ld];
			update_reg(R);
			print_rgf(R);
		}

	}

	printf("\n");

}

int
main () {

	 int R[MAX_REGISTERS] = {0};
	 int M[MAX_DATAMEMORY] = {0};
	 int opcode[MAX_INSTRUCTIONS] = {0};
	 int dest_reg[MAX_INSTRUCTIONS] = {0};
	 int src1[MAX_INSTRUCTIONS] = {0};
	 int src2[MAX_INSTRUCTIONS] = {0};
	 int num_of_inst = 0;
	 int active_token[6] = {0};	//[0] = inm, [1] = inb, [2] = aib, [3] = lib, [4] = adb, [5] = reb
	 
	 num_of_inst = inst_count();
	 if(num_of_inst > MAX_INSTRUCTIONS) {
		 printf("MAXIMUM NUMBER OF INSTRUCTIONS ALLOWED IS 16\n");
		 return 0;
	 }

	 active_token[0] = num_of_inst;
	 for (int i = 0; i < 6; i++) {
	 	printf("active_token[%d] = %d\n", i, active_token[i]);
	}


	 read_reg(R);
	 update_reg(R);
         read_dam(M);
         update_dam(M);
	 read_inst(opcode, dest_reg, src1, src2, num_of_inst);
	 performing_inst(R, M, opcode, dest_reg, src1, src2, num_of_inst);
	 print_rgf(R);
	 print_dam(M);

	 while (active_token[0] != 0 || active_token[1] != 0 || active_token[2] != 0 || active_token[3] != 0 || active_token[4] != 0 || active_token[5] != 0) {
		
	 
	 }

         return 0;
}
