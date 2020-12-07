#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include "intcomp.h"

intcomp::intcomp(char *prg) {
	program=NULL;
	iIntCount=0;
	work_program=NULL;
	fill_program(prg);
	input = -1;
	output = INT_MAX;
	program_running = false;
}

intcomp::~intcomp() {
	delete work_program;
	delete program;
}

int intcomp::get_output() {
	return output;
}

void intcomp::reset_program() {
	for (int i = 0; i < iIntCount; i++) {
		work_program[i] = program[i];
	}
}

void intcomp::get_input(int inp) {
	input = inp;
}

void intcomp::fill_program(char *prg) {
	char *line = NULL;
	size_t linelen;
    linelen = 0;
	FILE *f = fopen(prg, "r");
    while (getdelim(&line, &linelen, ',', f) != -1) {
                int iIntVal;
                iIntVal = atoi(line);
                iIntCount++;
                program = (int *)realloc((void *)program, iIntCount * sizeof(unsigned int));
                program[iIntCount - 1] = iIntVal;
    }
	fclose(f);
        free(line);

	work_program = (int *)malloc(iIntCount * sizeof(unsigned int));
	reset_program();
}

int intcomp::input_and_store_integer(int *ptr) {
    if (input == -1) {
		if (DEBUG) printf ("Input leer\n");
		return 0;
	} else {
		if (DEBUG) printf ("Input NICHT leer: %d\n", input);
		*ptr = input;
		input = -1;
		return 1;
	}
}

void intcomp::output_integer_from_address(int *ptr) {
	output = *ptr;
	return;
}

int intcomp::getParam(int op, int position) {
	char *tmpStr;
	tmpStr = (char *)malloc(12 * sizeof(char));
	snprintf(tmpStr, 12, "%010d", op);
	int retval;
	int sl = strlen(tmpStr);
	if (tmpStr[sl - 3 - position] == intcomp::IMMEDIATE)
	{
		retval = *(p_ptr + 1 + position);
	} else {
		retval = *(work_program + (int)*(p_ptr + 1 + position));
	}
	free(tmpStr);
	return retval;
}

int intcomp::do_operation() {
	// Check operation parameter types
	int full_operator = *p_ptr;
	int operation;
	operation = (*p_ptr) % 100;	// last two digits tell us the type of operation
	int param1, param2;
	
	if (DEBUG) printf ("Operation: %d\n", operation);


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
			*(work_program + *(p_ptr + 3)) = param1 * param2;
			p_ptr += 4;
			break;
		case 3:  //input
			if (DEBUG) printf("INP\n");
			if (input_and_store_integer(work_program + *(p_ptr + 1))) {
				p_ptr += 2;
			} else
				return -2;
			break;
		case 4:
			if (DEBUG) printf("OUT\n");
			param1 = getParam(*p_ptr, 0);
			output_integer_from_address(work_program + *(p_ptr + 1));
			p_ptr += 2;
			break;
		case 5: // Jump-if-true
			if (DEBUG) printf("Pointer: %p, Wert dort: %d\n", p_ptr, *p_ptr);
			param1 = getParam(*p_ptr, 0);
			param2 = getParam(*p_ptr, 1);
			if (DEBUG) printf("Param1: %d, Param2: %d\n", param1, param2);
			if (param1 != 0) {
				if (DEBUG) printf ("Do the jump to location %d\n", param2);
				p_ptr = work_program + param2;
			} else {
				if (DEBUG) printf("Do not jump.\n");
				p_ptr += 3;
			}
			break;
		case 6: // Jump-if-false
			param1 = getParam(*p_ptr, 0);
			param2 = getParam(*p_ptr, 1);
			if (param1 == 0) {
				p_ptr = work_program + param2;
			} else {
				p_ptr += 3;
			}
			break;
		case 7: // less-then
			param1 = getParam(*p_ptr, 0);
			param2 = getParam(*p_ptr, 1);
			if (param1 < param2) {
				*(work_program + *(p_ptr + 3)) = 1;
			} else {
				*(work_program + *(p_ptr + 3)) = 0;
			}
			p_ptr += 4;
			break;
		case 8: // equals
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
		default: { printf ("%d\n", operation); return INT_MAX;} // Fehler
	}
	return 1;
}

void intcomp::print_program(char type) {
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

int intcomp::execute_program(int print_style) {
	static int iterations;
	if (!program_running) {
		program_running = true;
		iterations=0;
		p_ptr = work_program;
	}
	while (1) {
		print_program(print_style);
		int ret = do_operation();
		iterations++;
		if (ret == 0) {
			if (print_style != 0) printf ("Programm erfolgreich beendet.\t");
			program_running = false;
			break;
		}
		if (ret == INT_MAX) {
			printf ("Fehler bei der Programmausführung aufgetreten!\n");
			program_running = false;
			return INT_MAX;
		}
		if (ret == -2) {
			return -2; // Programm wartet auf Eingabe
		}
	}
	print_program(print_style);
	if (print_style != 0) printf("Durchgeführte Berechnungen: %d\n", iterations);
	return 0;
}

void intcomp::execute_program_params(int noun, int verb, char print_style) {
	work_program[1] = noun;
	work_program[2] = verb;
	execute_program(print_style);
}
