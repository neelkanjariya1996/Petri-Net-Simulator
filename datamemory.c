#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
main () {

         int R[8] = {0};
         read_datamemory_file(R, 8);
         update_datamemory_file(R, 8);

         return 0;
}
