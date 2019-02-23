#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INSTRUCTIONS 16 
#define MAX_REGISTERS 8
#define MAX_DATAMEMORY 8

typedef struct inm_t_ {
	int opcode;
	int dest_reg;
	int src1;
	int src2;
} inm_t;

typedef struct inb_t_ {
	int opcode;
	int dest_reg;
	int src1;
	int src2;
} inb_t;

typedef struct lib_t_ {
	int opcode;
	int dest_reg;
	int src1;
	int src2;
} lib_t;

typedef struct aib_t_ {
	int opcode;
	int dest_reg;
	int src1;
	int src2;
} aib_t;

typedef struct adb_t_ {
	int dest_reg;
	int val;
} adb_t;

typedef struct reb_t_ {
	int dest_reg;
	int val;
} reb_t;

typedef struct dam_t_ {
	int mem_val;
} dam_t;

typedef struct rgf_t_ {
	int reg_val;
} rgf_t;

void
print_rgf (rgf_t rgf[]) {

        int i = 0;

        printf("RGF:");
        for (i = 0; i < MAX_REGISTERS - 1; i++) {
                printf("<R%d,%d>,", i, rgf[i].reg_val);
        }
        printf("<R7,%d>", rgf[7].reg_val);
        printf("\n");

}

void
print_dam (dam_t dam[]) {

        int i = 0;

        printf("DAM:");
        for (i = 0; i < MAX_DATAMEMORY - 1; i++) {
                printf("<%d,%d>,", i, dam[i].mem_val);
        }
        printf("<7,%d>", dam[i].mem_val);
        printf("\n");

}

void
read_dam(dam_t dam[]) {

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
                return;
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
                                        dam[i].mem_val = mem_val;
                                }
                        }
                }
        }
        
	fclose(read_dam);
}

void
update_dam(dam_t dam[]) {

        FILE *read_dam;
        int i = 0;

        read_dam = fopen("datamemory.txt", "w");
        if (read_dam == NULL) {
                fprintf(stderr, "Error reading file\n");
                return; 
        }

        for (i = 0; i < MAX_DATAMEMORY; i++) {
                fprintf(read_dam, "<%d,%d>\n", i, dam[i].mem_val);
        }

        fclose(read_dam);

        //return 0;
}

void
read_reg(rgf_t rgf[]) {

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
                return;
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
                                        rgf[i].reg_val = reg_val;
                                }
                        }
                }

        }

        fclose(read_reg);
}

int
update_reg(rgf_t rgf[]) {

        FILE *read_reg;
        int i = 0;

        read_reg = fopen("registers.txt", "w");
        if (read_reg == NULL) {
                fprintf(stderr, "Error reading file\n");
                return 1;
        }

        for (i = 0; i < MAX_REGISTERS; i++) {
                fprintf(read_reg, "<R%d,%d>\n", i, rgf[i].reg_val);
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

void
read_inst(inm_t inm[], int num_of_inst) {

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
                return;
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
                                        inm[i].opcode = 1;
                                } else if (!(strcmp(pch, "SUB"))) {
                                        inm[i].opcode = 2;
                                } else if (!(strcmp(pch, "AND"))) {
                                        inm[i].opcode = 3;
                                } else if (!(strcmp(pch, "OR"))) {
                                        inm[i].opcode = 4;
                                } else if (!(strcmp(pch, "LD"))) {
                                        inm[i].opcode = 5;
                                }

                                pch = strtok (NULL, "<R,>\n");
                                if (pch != NULL) {
                                        destination_register = atoi(pch);
                                        inm[i].dest_reg = destination_register;
                                }
                                pch = strtok (NULL, "<R,>\n");
                                if (pch != NULL) {
                                        first_source = atoi(pch);
                                        inm[i].src1 = first_source;
                                }

                                pch = strtok (NULL, "<R,>\n");
                                if(pch != NULL) {
                                        second_source = atoi(pch);
                                        inm[i].src2 = second_source;
                                }
                        }
                        i++;
                }
        }

        fclose(read_inst);

}

void
performing_inst (inm_t inm[], dam_t dam[], rgf_t rgf[], int num_of_inst) {

        int d = 0;
        int s1 = 0;
        int s2 = 0;
        int i = 0;
        int ld = 0;

        for (i = 0; i < num_of_inst; i++) {

                d = inm[i].dest_reg;
                s1 = inm[i].src1;
                s2 = inm[i].src2;

                printf("INSTRUCTION: %d\n", i);
                if (inm[i].opcode == 1) {
                        rgf[d].reg_val = rgf[s1].reg_val + rgf[s2].reg_val;
                        update_reg(rgf);
                        print_rgf(rgf);
                } else if (inm[i].opcode == 2) {
                        rgf[d].reg_val = rgf[s1].reg_val - rgf[s2].reg_val;
                        update_reg(rgf);
                        print_rgf(rgf);
                } else if (inm[i].opcode == 3) {
                        rgf[d].reg_val = rgf[s1].reg_val && rgf[s2].reg_val;
                        update_reg(rgf);
                        print_rgf(rgf);
                } else if (inm[i].opcode == 4) {
                        rgf[d].reg_val = rgf[s1].reg_val || rgf[s2].reg_val;
                        update_reg(rgf);
                        print_rgf(rgf);
                } else if (inm[i].opcode == 5) {
                        ld = rgf[s1].reg_val + rgf[s2].reg_val;
                        rgf[d].reg_val = dam[ld].mem_val;
                        update_reg(rgf);
                        print_rgf(rgf);
                }

        }

        printf("\n");

}

void
decode (inm_t inm[], inb_t inb[], rgf_t rgf[]) {
	
	int read_count_inm = 0;
	int write_count_inb = 0;
	int s1 = 0;
	int s2 = 0;

	s1 = inm[read_count_inm].src1;
	s2 = inm[read_count_inm].src2;
	
	inb[write_count_inb].opcode = inm[read_count_inm].opcode;
	inb[write_count_inb].dest_reg = inm[read_count_inm].dest_reg;
	inb[write_count_inb].src1 = rgf[s1].reg_val;
	inb[write_count_inb].src2 = rgf[s2].reg_val;
	
	read_count_inm++;
	write_count_inb++;
}

void
issue1 (inb_t inb[], lib_t lib[]) {

	int read_count_inb = 0;
	int write_count_lib = 0;

	if (inb[read_count_inb].opcode == 5) { 
		lib[write_count_lib].opcode = inb[read_count_inb].opcode;
		lib[write_count_lib].dest_reg = inb[read_count_inb].dest_reg;
		lib[write_count_lib].src1 = inb[read_count_inb].src1;
		lib[write_count_lib].src2 = inb[read_count_inb].src2;
		read_count_inb++;
		write_count_lib++;
	} else {
		return;
	} 
}

void
issue2 (inb_t inb[], aib_t aib[]) {

	int read_count_inb = 0;
	int write_count_aib = 0;

	if (inb[read_count_inb].opcode == 1 || inb[read_count_inb].opcode == 2 || inb[read_count_inb].opcode == 3 || inb[read_count_inb].opcode == 4) { 
		aib[write_count_aib].opcode = inb[read_count_inb].opcode;
		aib[write_count_aib].dest_reg = inb[read_count_inb].dest_reg;
		aib[write_count_aib].src1 = inb[read_count_inb].src1;
		aib[write_count_aib].src2 = inb[read_count_inb].src2;
	
		read_count_inb++;
		write_count_aib++;
	} else {
		return;
	} 
}

int
main () {

	int num_of_inst = 0;
	num_of_inst = inst_count();
	if(num_of_inst > MAX_INSTRUCTIONS) {
                 printf("MAXIMUM NUMBER OF INSTRUCTIONS ALLOWED IS 16\n");
                 return 0;
         }

	inm_t inm[num_of_inst];
	inb_t inb[num_of_inst];
	aib_t aib[num_of_inst];
	lib_t lib[num_of_inst];
	adb_t adb[num_of_inst];
	reb_t reb[num_of_inst];
	rgf_t rgf[MAX_REGISTERS];
	dam_t dam[MAX_DATAMEMORY];

	read_dam (dam);
	update_dam (dam);
	read_reg (rgf);
	update_reg (rgf);
	read_inst (inm, num_of_inst);
	performing_inst (inm, dam, rgf, num_of_inst);
	decode(inm, inb, rgf);
	for (int i = 0; i < num_of_inst; i++) {
		printf("inst:%d\t opcode:%d\t dest_reg:%d\t src1:%d\t src2:%d\t\n", i, inb[i].opcode, inb[i].dest_reg, inb[i].src1, inb[i].src2);
	}
	issue1(inb, lib);
	for (int i = 0; i < num_of_inst; i++) {
		printf("inst:%d\t opcode:%d\t dest_reg:%d\t src1:%d\t src2:%d\t\n", i, lib[i].opcode, lib[i].dest_reg, lib[i].src1, lib[i].src2);
	}
	issue2(inb, aib);
	for (int i = 0; i < num_of_inst; i++) {
		printf("inst:%d\t opcode:%d\t dest_reg:%d\t src1:%d\t src2:%d\t\n", i, aib[i].opcode, aib[i].dest_reg, aib[i].src1, aib[i].src2);
	}
		
	return 0;
}
