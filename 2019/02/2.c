#include<stdio.h>
#include<stdlib.h>

unsigned int *program=NULL;
int iIntCount = 0;
unsigned int *work_program=NULL;

int *p_ptr;	// program pointer

void reset_program() {
	for (int i = 0; i < iIntCount; i++) {
		work_program[i] = program[i];
	}
}

void fill_program() {
	char *line = NULL;
	size_t linelen;
        linelen = 0;
        while (getdelim(&line, &linelen, ',', stdin) != -1) {
                int iIntVal;
                iIntVal = atoi(line);
                iIntCount++;
                program = realloc(program, iIntCount * sizeof(unsigned int));
                program[iIntCount - 1] = iIntVal;
        }
        free(line);

	work_program = malloc(iIntCount * sizeof(unsigned int));
	reset_program();
}

int do_operation() {
	switch(*p_ptr) {
		case 1: // Addition
			*(work_program + *(p_ptr + 3)) = *(work_program + *(p_ptr + 1)) + *(work_program + *(p_ptr + 2));
			break;
		case 2: // Multiplikation
			*(work_program + *(p_ptr + 3)) = *(work_program + *(p_ptr + 1)) * *(work_program + *(p_ptr + 2));
			break;
		case 99: return 0; // Programm beenden
		default: return -1; // Fehler
	}
	p_ptr += 4;	// zur nächsten Anweisung
}

void print_program(int type) {
	if (type == 1) {
		printf ("---------------------------------------------------------\n");
		for (int i=0; i < iIntCount; i++) {
			printf("%7d ", work_program[i]);
			if (i % 8 == 7) printf("\n");
		}
		printf ("\n");
		printf ("---------------------------------------------------------\n");
	}
	if (type == 2) {
		printf ("Ergebnis: %d\t", work_program[0]);
	}
}

void execute_program(int noun, int verb, int print_style) {
	int iterations=0;
	work_program[1] = noun;
	work_program[2] = verb;
	p_ptr = work_program;
	while (1) {
		int ret = do_operation();
		iterations++;
		if (ret == 0) {
			if (print_style != 0) printf ("Programm erfolgreich beendet.\t");
			break;
		}
		if (ret == -1) {
			printf ("Fehler bei der Programmausführung aufgetreten!\n");
			return;
		}
	}
	print_program(print_style);
	if (print_style != 0) printf("Durchgeführte Berechnungen: %d\n", iterations);
}

int main(int argc, char **argv) {
	fill_program();
	for (int noun = 0; noun <= 99; noun++) {
		for (int verb = 0; verb <= 99; verb++) {
			execute_program(noun, verb, 0);
			if (*work_program == 19690720) 
				printf ("100 * noun + verb = %d (%2d, %2d)\n", 100 * noun + verb, noun, verb);
			reset_program();
		}
	}
	free(work_program);
	free(program);
}
