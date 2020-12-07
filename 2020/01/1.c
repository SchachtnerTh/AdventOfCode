#include<stdio.h>
#include<stdlib.h>

int *program=NULL;
int iIntCount = 0;

void fill_program(char *prg) {
	char *line = NULL;
	size_t linelen;
        linelen = 0;
	FILE *f = fopen(prg, "r");
        while (getline(&line, &linelen, f) != -1) {
                int iIntVal;
                iIntVal = atoi(line);
                iIntCount++;
                program = realloc(program, iIntCount * sizeof(unsigned int));
                program[iIntCount - 1] = iIntVal;
        }
	fclose(f);
        free(line);
}

int main(int argc, char **argv) {
	fill_program(argv[1]);
	for (int i = 0; i < iIntCount; i++) {
		for (int j = i+1; j < iIntCount; j++) {
			if (*(program + i) + *(program + j) == 2020) printf ("Die gewünschte Zahl ist %d\n", *(program + i) * *(program + j));
		}
	}
	for (int i = 0; i < iIntCount; i++) {
		for (int j = i+1; j < iIntCount; j++) {
			for (int k = j + 1; k < iIntCount; k++) {
				if (*(program + i) + *(program + j) + *(program + k) == 2020) printf ("Die gewünschte Zahl ist %d\n", *(program + i) * *(program + j) * *(program + k));
			}
		}
	}
	free(program);
}
