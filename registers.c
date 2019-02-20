#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int 
read_register_file(int R[], int number_of_registers) {

	FILE *read_registers;
        char str[6];
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
main () {

	 int R[8] = {0};
	 read_register_file(R, 8);
	 update_register_file(R, 8);

	 return 0;

}
