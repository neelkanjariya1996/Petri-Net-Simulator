/*On my honor, I have neither given nor received unauthorized aid on this assignment*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INSTRUCTIONS 	16 
#define MAX_REGISTERS 		8
#define MAX_DATAMEMORY 		8

typedef struct inm_t_ {
	int opcode;
	int dest_reg;
	int src1;
	int src2;
} inm_t;

typedef struct inm_q_t_ {
	int head;
	int tail;
	int size;
	inm_t inm[MAX_INSTRUCTIONS];
} inm_q_t;

typedef struct inb_t_ {
	int opcode;
	int dest_reg;
	int src1;
	int src2;
} inb_t;

typedef struct inb_q_t_ {
	int head;
	int tail;
	int size;
	inb_t inb[MAX_INSTRUCTIONS];
} inb_q_t;

typedef struct lib_t_ {
	int opcode;
	int dest_reg;
	int src1;
	int src2;
} lib_t;

typedef struct lib_q_t_ {
	int head;
	int tail;
	int size;
	lib_t lib[MAX_INSTRUCTIONS];
} lib_q_t;

typedef struct aib_t_ {
	int opcode;
	int dest_reg;
	int src1;
	int src2;
} aib_t;

typedef struct aib_q_t_ {
	int head;
	int tail;
	int size;
	aib_t aib[MAX_INSTRUCTIONS];
} aib_q_t;

typedef struct adb_t_ {
	int dest_reg;
	int mem_loc;
} adb_t;

typedef struct adb_q_t_ {
	int head;
	int tail;
	int size;
	adb_t adb[MAX_INSTRUCTIONS];
} adb_q_t;

typedef struct reb_t_ {
	int dest_reg;
	int reg_val;
} reb_t;

typedef struct reb_q_t_ {
	int head;
	int tail;
	int size;
	reb_t reb[MAX_INSTRUCTIONS];
} reb_q_t;

typedef struct dam_t_ {
	int mem_val;
} dam_t;

typedef struct rgf_t_ {
	int reg_val;
} rgf_t;

inm_q_t inm_q;
inb_q_t inb_q;
aib_q_t aib_q;
lib_q_t lib_q;
adb_q_t adb_q;
reb_q_t reb_q;
rgf_t rgf[MAX_REGISTERS];
dam_t dam[MAX_DATAMEMORY];

int mem_ind = 0;
int mem_val = 0;
int reg_ind = 0;
int reg_val = 0;
int opcode = 0;
int destination_register = 0;
int first_source = 0;
int second_source = 0;

FILE *simulation;

#define inm_head 	inm_q.head
#define inm_tail	inm_q.tail
#define inm_size	inm_q.size
#define inm 		inm_q.inm

#define inb_head 	inb_q.head
#define inb_tail	inb_q.tail
#define inb_size	inb_q.size
#define inb 		inb_q.inb

#define lib_head 	lib_q.head
#define lib_tail	lib_q.tail
#define lib_size	lib_q.size
#define lib 		lib_q.lib

#define aib_head 	aib_q.head
#define aib_tail	aib_q.tail
#define aib_size	aib_q.size
#define aib 		aib_q.aib

#define adb_head 	adb_q.head
#define adb_tail	adb_q.tail
#define adb_size	adb_q.size
#define adb 		adb_q.adb

#define reb_head 	reb_q.head
#define reb_tail	reb_q.tail
#define reb_size	reb_q.size
#define reb 		reb_q.reb

void
print_inm () {

	int i = 0;

	printf("INM:");
	for (i = inm_head; i < (inm_head + inm_size); i++) {
		
		if (inm[i].opcode == 1) {
			printf("<ADD,");
		} else if (inm[i].opcode == 2) {
			printf("<SUB,");
		} else if (inm[i].opcode == 3) {
			printf("<AND,");
		} else if (inm[i].opcode == 4) {
			printf("<OR,");
		} else if (inm[i].opcode == 5) {
			printf("<LD,");
		}

		printf("R%d,", inm[i].dest_reg);
		printf("R%d,", inm[i].src1);
		if (i < ((inm_head + inm_size) - 1)) {
			printf("R%d>,", inm[i].src2);
		} else {
			printf("R%d>", inm[i].src2);
		}
	}

	printf("\n");

}

void
print_inb () {

	printf("INB:");
	for (int i = inb_head; i < (inb_head + inb_size); i++) {
		
		if (inb[i].opcode == 1) {
			printf("<ADD,");
		} else if (inb[i].opcode == 2) {
			printf("<SUB,");
		} else if (inb[i].opcode == 3) {
			printf("<AND,");
		} else if (inb[i].opcode == 4) {
			printf("<OR,");
		} else if (inb[i].opcode == 5) {
			printf("<LD,");
		}

		printf("R%d,", inb[i].dest_reg);
		printf("%d,", inb[i].src1);
		if (i < ((inb_head + inb_size) - 1)) {
			printf("%d>,", inb[i].src2);
		} else {
			printf("%d>", inb[i].src2);
		}
	}

	printf("\n");

}

void
print_aib() {

	printf("AIB:");
	for (int i = aib_head; i < (aib_head + aib_size); i++) {

		if (aib[i].opcode == 1) {
			printf("<ADD,");
		} else if (aib[i].opcode == 2) {
			printf("<SUB,");
		} else if (aib[i].opcode == 3) {
			printf("<AND,");
		} else if (aib[i].opcode == 4) {
			printf("<OR,");
		} else if (aib[i].opcode == 5) {
			printf("<LD,");
		}

		printf("R%d,", aib[i].dest_reg);
		printf("%d,", aib[i].src1);
		if (i < ((aib_head + aib_size) - 1)) {
			printf("%d>,", aib[i].src2);
		} else {
			printf("%d>", aib[i].src2);
		}
	}

	printf("\n");
		
}

void
print_lib () {
	
	printf("LIB:");
	for (int i = lib_head; i < (lib_head + lib_size); i++) {

		if(lib[i].opcode == 5) {
			printf("<LD,");
			printf("R%d,", lib[i].dest_reg);
			printf("%d,", lib[i].src1);
			if (i < ((lib_head + lib_size) - 1)) {
				printf("%d>,", lib[i].src2);
			} else {
				printf("%d>", lib[i].src2);
			}
		} else
			continue;
	}

	printf("\n");

}

void
print_adb () {
	
	printf("ADB:");
	for (int i = adb_head; i < (adb_head + adb_size); i++) {
		printf("<R%d,", adb[i].dest_reg);
		printf("%d>", adb[i].mem_loc);
	}

	printf("\n");

}

void
print_reb () {

	printf("REB:");
	for (int i = reb_head; i < (reb_head + reb_size); i++) {
		printf("<R%d,", reb[i].dest_reg);
		if (i < (reb_head + reb_size - 1)) {
			printf("%d>,", reb[i].reg_val);
		} else {
			printf("%d>", reb[i].reg_val);
		}
	}

	printf("\n");

}

void
print_rgf () {

        int i = 0;

        printf("RGF:");
        for (i = 0; i < MAX_REGISTERS - 1; i++) {
                printf("<R%d,%d>,", i, rgf[i].reg_val);
        }
        printf("<R7,%d>", rgf[7].reg_val);
        
	printf("\n");

}

void
print_dam () {

        int i = 0;

        printf("DAM:");
        for (i = 0; i < MAX_DATAMEMORY - 1; i++) {
                printf("<%d,%d>,", i, dam[i].mem_val);
        }
        printf("<7,%d>", dam[i].mem_val);
        
	printf("\n");

}

int
read_dam() {

        FILE *read_dam;
        char str[6];
        char *pch;
        int ret = 0;
        int i = 0;

        read_dam = fopen("datamemory.txt", "r");
        if (read_dam == NULL) {
                fprintf(stderr, "Error reading file \n");
                return -1;
        } else {
		fseek (read_dam, 0, SEEK_END);
		unsigned long size = (unsigned long)ftell(read_dam);
		if (size > 0) {
			rewind(read_dam);
		 
			while (ret = fscanf(read_dam, "%s", str)) {

				if (ret == EOF) {
					break;
				}

				pch = strtok(str, "<,>\n");
				mem_ind = atoi(pch);
				if (mem_ind < 0 || mem_ind > 7) {
					printf("Memory location can only be in between 0 to 7\n");
					return -1;
				} 
				for (i = 0; i < MAX_DATAMEMORY; i++) {
					if (mem_ind == i) {
						if (pch != NULL) {
							pch = strtok (NULL, "<,>\n");
							mem_val = atoi(pch);
							if (mem_val < 0 || mem_val > 63) {
								printf("The contents of data memory can be between 0 to 63\n");
								return -1;
							}
							dam[i].mem_val = mem_val;
						}
					}
				}
			}
		}
	}

	fclose(read_dam);

	return 0;
}

int
read_reg() {

        FILE *read_reg;
        char str[8];
        char *pch;
        int ret = 0;
        int i = 0;

        read_reg = fopen("registers.txt", "r");
        if (read_reg == NULL) {
                fprintf(stderr, "Error reading file\n");
                return -1;
        } else {
		fseek (read_reg, 0, SEEK_END);
		unsigned long size = (unsigned long)ftell(read_reg);
		
		if (size > 0) {
			rewind(read_reg);

			while (ret = fscanf(read_reg, "%s", str)) {

				if (ret == EOF) {
					break;
				}

				pch = strtok(str, "<R,>\n");
				reg_ind = atoi(pch);
				if (reg_ind < 0 || reg_ind > 7) {
					printf("Register index can only be between 0 to 7\n");
					return -1;
				}
				for (i = 0; i < MAX_REGISTERS; i++) {
					if (reg_ind == i) {
						if (pch != NULL) {
							pch = strtok (NULL, "<R,>\n");
							reg_val = atoi(pch);
							if (reg_val < 0 || reg_val > 63) {
								printf("Register values can only be between 0 to 63\n");
								return -1;
							}
							rgf[i].reg_val = reg_val;
						}
					}
				}

			}
		}
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
                return -1;
        } else {
		fseek (read_inst, 0, SEEK_END);
		int size = ftell(read_inst);
		
		if (size == 0) {
			printf("Instruction file empty\n");
			return -1;
		}
	}
        fclose(read_inst);

        read_inst = fopen("instructions.txt", "r");
        for (c = getc(read_inst); c != EOF; c = getc(read_inst)) {
                if (c == '\n') {
                        num_of_inst = num_of_inst + 1;
                }
        }

        fclose(read_inst);

        return num_of_inst;

}

int
read_inst(int num_of_inst) {

        FILE *read_inst;
        char str[15];
        char *pch;
        int ret;
        int i = 0;

        read_inst = fopen("instructions.txt", "r");
        if (read_inst == NULL) {
                fprintf(stderr, "Error reading file\n");
                return -1;
        } else {
		fseek (read_inst, 0, SEEK_END);
		int size = ftell(read_inst);
		
		if (size == 0) {
			printf("Instruction file empty\n");
			return -1;
		}
	}
        fclose(read_inst);

        read_inst = fopen("instructions.txt", "r");
        i = 0;
        if (num_of_inst <= MAX_INSTRUCTIONS) {
                while (ret = fscanf(read_inst, "%s", str)) {

                        if (ret == EOF) {
                                break;
                        }
                        pch = strtok(str,"<,>\n");
                                
			if (!(strncmp(pch, "ADD", 3))) {
                                inm[i].opcode = 1;
                        } else if (!(strncmp(pch, "SUB", 3))) {
                                inm[i].opcode = 2;
                        } else if (!(strncmp(pch, "AND", 3))) {
                                inm[i].opcode = 3;
                        } else if (!(strncmp(pch, "OR", 2))) {
                                inm[i].opcode = 4;
                        } else if (!(strncmp(pch, "LD", 2))) {
                                inm[i].opcode = 5;
                        }  else {
			        opcode = 6;
			 	printf("Allowed instructions are ADD, SUB, AND, OR and LD\n");
				return -1;
			}		
				
                        pch = strtok (NULL, "<R,>\n");
                        if (pch != NULL) {
				destination_register = atoi(pch);
				if (destination_register < 0 || destination_register > 7) {
				printf("Destination register names should be between R0 to R7\n");
				return -1;
				}
                                inm[i].dest_reg = destination_register;
                        }

                        pch = strtok (NULL, "<R,>\n");
                        if (pch != NULL) {
				first_source = atoi(pch);
				if (first_source < 0 || first_source > 7) {
					printf("First source operand names should be between R0 to R7\n");
					return -1;
				}
                                inm[i].src1 = first_source;
                        }

                        pch = strtok (NULL, "<R,>\n");
                        if(pch != NULL) {
				second_source = atoi(pch);
				if (second_source < 0 || second_source > 7) {
					printf("Second source operand names should be between R0 to R7\n");
					return -1;
				}
                                inm[i].src2 = second_source;
				} else {
					printf("Invalid Instruction\n");
					return -1;
			}
                        i++;
                  }
        }

        fclose(read_inst);

	return 0;

}

void
decode () {
	
	int s1 = 0;
	int s2 = 0;
	
	s1 = inm[inm_head].src1;
	s2 = inm[inm_head].src2;
	
	inb[inb_tail].opcode = inm[inm_head].opcode;
	inb[inb_tail].dest_reg = inm[inm_head].dest_reg;
	inb[inb_tail].src1 = rgf[s1].reg_val;
	inb[inb_tail].src2 = rgf[s2].reg_val;
	
	inm_head++;
	inb_tail++;
	inm_size--;
	inb_size++;

}

void
issue2 () {
	
	if (inb[inb_head].opcode == 5) { 
		lib[lib_tail].opcode = inb[inb_head].opcode;
		lib[lib_tail].dest_reg = inb[inb_head].dest_reg;
		lib[lib_tail].src1 = inb[inb_head].src1;
		lib[lib_tail].src2 = inb[inb_head].src2;
	} 
	
	inb_head++;
	lib_tail++;
	inb_size--;
	lib_size++;

}

void
issue1 () {

	if (inb[inb_head].opcode == 1 || inb[inb_head].opcode == 2 || inb[inb_head].opcode == 3 || inb[inb_head].opcode == 4) { 
		aib[aib_tail].opcode = inb[inb_head].opcode;
		aib[aib_tail].dest_reg = inb[inb_head].dest_reg;
		aib[aib_tail].src1 = inb[inb_head].src1;
		aib[aib_tail].src2 = inb[inb_head].src2;
	}
	
	inb_head++;
	aib_tail++;
	inb_size--;
	aib_size++;

}

void
addr () {
	
	int mem_loc = 0;
		
	mem_loc = lib[lib_head].src1 + lib[lib_head].src2;

	if (lib[lib_head].opcode == 5) { 
		adb[adb_tail].dest_reg = lib[lib_head].dest_reg;
		adb[adb_tail].mem_loc = mem_loc;
	}

	lib_head++;
	adb_tail++;
	lib_size--;
	adb_size++;

}

void
load () {
	
	int mem_loc = 0;
		
	mem_loc = adb[adb_head].mem_loc;

	reb[reb_tail].dest_reg = adb[adb_head].dest_reg;
	reb[reb_tail].reg_val = dam[mem_loc].mem_val;

	adb_head++;
	reb_tail++;
	adb_size--;
	reb_size++;

}

void
alu () {

	int reg_val = 0;

	if (aib[aib_head].opcode == 1)
		reg_val = aib[aib_head].src1 + aib[aib_head].src2;
	else if (aib[aib_head].opcode == 2)
		reg_val = aib[aib_head].src1 - aib[aib_head].src2;
	else if (aib[aib_head].opcode == 3)
		reg_val = aib[aib_head].src1 & aib[aib_head].src2;
	else if (aib[aib_head].opcode == 4)
		reg_val = aib[aib_head].src1 | aib[aib_head].src2;

	reb[reb_tail].dest_reg = aib[aib_head].dest_reg;
	reb[reb_tail].reg_val = reg_val;
	
	aib_head++;
	reb_tail++;
	aib_size--;
	reb_size++;

}

void
write () {

	int reg_name = 0;
		
	reg_name = reb[reb_head].dest_reg;

	rgf[reg_name].reg_val = reb[reb_head].reg_val;

	reb_head++;
	reb_size--;

}

int
main () {

	simulation = fopen("simulation.txt", "w");
	int num_of_inst = 0;
	int step = 0; 
	int curr_inm_size = 0;
	int curr_inb_size = 0;
	int curr_aib_size = 0;
	int curr_lib_size = 0;
	int curr_adb_size = 0;
	int curr_reb_size = 0;
	int read_inst_out = 0;
	int num_of_inst_out = 0;
	int read_dam_out = 0;
	int update_dam_out = 0;
	int read_reg_out = 0;
	int update_reg_out = 0;

	memset(&inm_q, 0, sizeof(inm_q));
	memset(&inb_q, 0, sizeof(inb_q));
	memset(&aib_q, 0, sizeof(aib_q));
	memset(&lib_q, 0, sizeof(lib_q));
	memset(&adb_q, 0, sizeof(adb_q));
	memset(&reb_q, 0, sizeof(reb_q));
	memset(&rgf, 0, sizeof(rgf));
	memset(&dam, 0, sizeof(dam));

	num_of_inst = inst_count();
	num_of_inst_out = inst_count();	
	if (num_of_inst_out == -1) {
		return 0;
	}
	if(num_of_inst > MAX_INSTRUCTIONS) {
                 printf("MAXIMUM NUMBER OF INSTRUCTIONS ALLOWED IS 16\n");
                 return 0;
         }

	read_dam_out = read_dam ();
	if (read_dam_out == -1) {
		return 0;
	}
	if (mem_ind < 0 || mem_ind > 7) {
		return 0;
	}
	if (mem_val < 0 || mem_val > 63) {
		return 0;
	}
/*
	update_dam ();
	if (update_dam_out == -1) {
		return 0;
	}
*/
	read_reg_out = read_reg ();
	if (read_reg_out == -1) {
		return 0;
	}
	if (reg_ind < 0 || reg_ind > 7) {
		return 0;
	}
	if (reg_val < 0 || reg_val > 63) {
		return 0;
	}
/*
	update_reg ();
	if (update_reg_out == -1) {
		return 0;
	}
*/
	read_inst_out = read_inst (num_of_inst);
	if (read_inst_out == -1) {
		return 0;
	}
	if (opcode == 6) {
		return 0;
	}
	if (destination_register < 0 || destination_register > 7) {
		return 0;
	}
	if (first_source < 0 || first_source > 7) {
		return 0;
	}
	if (second_source < 0 || second_source > 7) {
		return 0;
	}
	
	inm_size = num_of_inst;

	while (inm_size != 0 || inb_size != 0 || lib_size != 0 || adb_size != 0 || aib_size != 0 || reb_size != 0) {

		curr_inm_size = inm_size;
		curr_inb_size = inb_size;
		curr_aib_size = aib_size;
		curr_lib_size = lib_size;
		curr_adb_size = adb_size;
		curr_reb_size = reb_size;
		
		printf("STEP %d\n", step);
		
		print_inm();
		print_inb();
		print_aib();
		print_lib();
		print_adb();
		print_reb();
		print_rgf();
		print_dam();


		if (curr_inm_size != 0) {
			decode();
		}

		if (curr_inb_size != 0) {
			if (inb[inb_head].opcode == 5) {
				issue2();
			}
			else {
				issue1();
			}
		}

		if (curr_lib_size != 0) {
			addr();
		}

		if (curr_adb_size != 0) {
			load();
		}

		if (curr_aib_size != 0) {
			alu();
		}

		if (curr_reb_size != 0) {
			write();
		} 
		
		step++;

		printf("\n");
	
	}
	
	printf("STEP %d:\n",step);
	print_inm();
	print_inb();
	print_aib();
	print_lib();
	print_adb();
	print_reb();
	print_rgf();
	print_dam();
	printf("\n");
		
	return 0;
}
