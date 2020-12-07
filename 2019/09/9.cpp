#include <stdio.h>
#include "intcomp.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Bitte Programmdatei zum Laden angeben!\n");
		return -1;
	}
	intcomp *comp;
	comp = new intcomp(argv[1]);
	printf("Starting test program\n");
	printf("\n");
	printf("Locating coordinates of Ceres distress signal.\n");
	comp->reset_program();
	comp->get_input(2);
	comp->execute_program(0);
	delete comp;
}