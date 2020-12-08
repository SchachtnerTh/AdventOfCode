#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG 0

struct op {
	char *code;
	int num;
};

struct op *program;
struct op *work_program;
int instructions_read=0;
long accu=0;

//struct op *program;

void copy_program()
{
	work_program = malloc(instructions_read * sizeof(struct op));
	for (int i = 0; i < instructions_read; i++) {
		work_program[i].code = malloc(20);
		strcpy(work_program[i].code, program[i].code);
		work_program[i].num = program[i].num;
	}
}

int run_program(struct op* prg) {
	int ip=0;
	int status=0;
	char *visited = malloc(instructions_read);
	for (int i = 0; i < instructions_read; visited[i++]=0);
	
	while (1) {
		int newip=0;
		// printf("ip: %d of %d\n", ip, instructions_read);
		if (visited[ip] >= 1) {
			status = -1;
			break; // loop detected
		}
		if (ip >= instructions_read - 1) {
			status = 0;
			break; // program terminated
		}
		if (!strcmp(prg[ip].code, "nop")) {
			if (DEBUG) printf("nop\n");
			visited[ip]++;
			newip = ip + 1;
		}
		if (!strcmp(prg[ip].code, "acc")) {
			if (DEBUG) printf("acc\n");
			visited[ip]++;
			accu += prg[ip].num;
			newip = ip + 1;
		}
		if (!strcmp(prg[ip].code, "jmp")) {
			if (DEBUG) printf("jmp\n");
			visited[ip]++;
			newip = ip + prg[ip].num;
		}
		ip = newip;

	}
	if (DEBUG) if (status == -1) printf ("program loops.\n");
	if (DEBUG) if (status == 0) printf ("program terminated.\n");
	if (DEBUG)printf ("Accumulator before loop or termination: %ld\n", accu);
	return status;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Bitte Dateinamen als Argument angeben!\n");
		return -1;
	}
	FILE *f;

	program = NULL;
	
	f = fopen(argv[1], "r");

	while (!feof(f)) {
		program = (struct op *)realloc(program, (instructions_read + 1) * sizeof(struct op));
		(program + instructions_read)->code = (char *)malloc(20 * sizeof(char));
		fscanf(f, "%s %d", (program + instructions_read)->code, &((program + instructions_read)->num));
		instructions_read++;
	}
	fclose(f);
	
	run_program(program);
	printf ("unmodified program: Accu: %ld\n", accu);
	
	int num_occurence_done=0;
	int numold=0;
	
	while (1) {
		copy_program();
		int counter = 0;
		for (int i = 0; i < instructions_read; i++)
		{
			if (!strcmp(work_program[i].code, "jmp")) {
				if (counter == num_occurence_done) {
					if (DEBUG) printf("(jmp->nop) numdone: %d, counter: %d, line: %d (%s %d)\n", num_occurence_done, counter, i+1, work_program[i].code, work_program[i].num);
					strcpy(work_program[i].code, "nop");
					num_occurence_done++;
					break;
				}
			} else if (!strcmp(work_program[i].code, "nop")) {
				if (counter == num_occurence_done) {
					if (DEBUG) printf("(nop->jmp) numdone: %d, counter: %d, line: %d (%s %d)\n", num_occurence_done, counter, i+1, work_program[i].code, work_program[i].num);
					strcpy(work_program[i].code, "jmp");
					num_occurence_done++;
					break;
				}
			}
			if (!strcmp(work_program[i].code, "jmp") || !strcmp(work_program[i].code, "nop")) counter++;
		}
		accu = 0;
		int ret = run_program(work_program);
		if (ret == 0) break;
		if (num_occurence_done == numold) { 
			printf ("alles ersetzt");
			break;
		}
		numold = num_occurence_done;
	}
	printf ("modified program: Accu: %ld\n", accu);
	
/*
	for (int i = 0; i < instructions_read - 1; i++) {
		printf ("Instruction %d: %s, %d\n", i, (program + i)->code, (program + i)->num);
	}
	*/
}