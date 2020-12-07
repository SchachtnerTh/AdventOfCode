#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEBUG 0

int *program=NULL;
int iIntCount = 0;
int *work_program=NULL;

int *p_ptr;	// program pointer

void reset_program() {
	for (int i = 0; i < iIntCount; i++) {
		work_program[i] = program[i];
	}
}

void fill_program(char *prg) {
	char *line = NULL;
	size_t linelen;
        linelen = 0;
	FILE *f = fopen(prg, "r");
        while (getdelim(&line, &linelen, ',', f) != -1) {
                int iIntVal;
                iIntVal = atoi(line);
                iIntCount++;
                program = realloc(program, iIntCount * sizeof(unsigned int));
                program[iIntCount - 1] = iIntVal;
        }
	fclose(f);
        free(line);
	work_program = malloc(iIntCount * sizeof(unsigned int));
	reset_program();
}

void input_and_store_integer(int *ptr) {
	int input; // = 0;
	printf("Input an Integer: ");
	scanf("%d", &input);
	*ptr = input;
	return;
}

void output_integer_from_address(int *ptr) {
	printf("Output: %d\n", *ptr);
	return;
}

const char IMMEDIATE = '1';
const char POSITION = '0';

int getParam(int operator, int position) {
	char *tmpStr;
	tmpStr = malloc(12 * sizeof(char));
	snprintf(tmpStr, 12, "%010d", operator);
	int retval;
	int sl = strlen(tmpStr);
	if (tmpStr[sl - 3 - position] == IMMEDIATE)
	{
		retval = *(p_ptr + 1 + position);
	} else {
		retval = *(work_program + *(p_ptr + 1 + position));
	}
	free(tmpStr);
	return retval;
}

int do_operation() {
	int full_operator = *p_ptr;
	int operation;
	operation = (*p_ptr) % 100;	// last two digits tell us the type of operation
	int param1, param2;


	switch(operation) {
		case 1: // Addition
			if (DEBUG) printf("ADD ");
			param1 = getParam(*p_ptr, 0);
			param2 = getParam(*p_ptr, 1);
			if (DEBUG) printf ("%d and %d\n", param1, param2);
			*(work_program + *(p_ptr + 3)) = param1 + param2;
			p_ptr += 4;
			break;
		case 2: // Multiplikation
			if (DEBUG) printf("MUL\n");
			param1 = getParam(*p_ptr, 0);
			param2 = getParam(*p_ptr, 1);
			if (DEBUG) printf ("%d and %d\n", param1, param2);
			*(work_program + *(p_ptr + 3)) = param1 * param2;
			p_ptr += 4;
			break;
		case 3:
			if (DEBUG) printf("INP\n");
			input_and_store_integer(work_program + *(p_ptr + 1)); 
			p_ptr += 2;
			break;
		case 4:
			if (DEBUG) printf("OUT\n");
			param1 = getParam(*p_ptr, 0);
			printf("Output: %d\n", param1);
			p_ptr += 2;
			break;
		case 5:
			param1 = getParam(*p_ptr, 0);
			param2 = getParam(*p_ptr, 1);
			if (param1 != 0) {
				p_ptr = work_program + param2;
			} else {
				p_ptr += 3;
			}
			break;
		case 6:
			param1 = getParam(*p_ptr, 0);
			param2 = getParam(*p_ptr, 1);
			if (param1 == 0) {
				p_ptr = work_program + param2;
			} else {
				p_ptr += 3;
			}
			break;
		case 7:
			param1 = getParam(*p_ptr, 0);
			param2 = getParam(*p_ptr, 1);
			if (param1 < param2) {
				*(work_program + *(p_ptr + 3)) = 1;
			} else {
				*(work_program + *(p_ptr + 3)) = 0;
			}
			p_ptr += 4;
			break;
		case 8:
			param1 = getParam(*p_ptr, 0);
			param2 = getParam(*p_ptr, 1);
			if (param1 == param2) {
				*(work_program + *(p_ptr + 3)) = 1;
			} else {
				*(work_program + *(p_ptr + 3)) = 0;
			}
			p_ptr += 4;
			break;



		case 99: return 0; // Programm beenden
		default: return -1; // Fehler
	}
	return 1;
}

void print_program(char type) {
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

void execute_program(char print_style) {
	int iterations=0;
	p_ptr = work_program;
	while (1) {
		print_program(print_style);
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

void execute_program_params(int noun, int verb, char print_style) {
	work_program[1] = noun;
	work_program[2] = verb;
	execute_program(print_style);
}

int main(int argc, char **argv) {
	fill_program(argv[1]);
	execute_program(0);
	free(work_program);
	free(program);
}
