#include <stdio.h>
#include "intcomp.h"

#define SIZE 128

short panel[SIZE][SIZE];
short moved[SIZE][SIZE];
short direction;

const short UP=0;
const short RIGHT=1;
const short DOWN=2;
const short LEFT=3;

int posX = 0;
int posY = 0;

void move() {
	switch (direction) {
		case 0:	posY++;	break;
		case 1: posX++; break;
		case 2: posY--; break;
		case 3: posX--; break;
	}
}

short get_panel(int x, int y) {
	return panel[x + SIZE/2][y + SIZE/2];
}

void set_panel(int x, int y, short value) {
	panel[x + SIZE/2][y + SIZE/2] = value;
}


void change_direction(int dir) {
	if (dir == 1) 
		direction = (direction + 1) % 4;
	else
		direction = (direction - 1 + 4) % 4;
	
	printf ("%d ", direction);
}

void show_panel() {
	for (int y = SIZE-1; y >= 0; y--) {
		for (int x = 0; x < SIZE; x++){
			if (panel[x][y] == 1) printf("X");
			if (panel[x][y] == 0) printf(" ");
		}
		printf("\n");
	}	
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Bitte Programmdatei zum Laden angeben!\n");
		return -1;
	}
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++){
			panel[x][y] = 0;
			moved[x][y] = 0;
		}
	}
	direction = 0;
	int ret = 0;
	intcomp *comp;
	comp = new intcomp(argv[1]);
	printf("Starting test program\n");
	set_panel(0,0,1);
	do {
		int inp = get_panel(posX, posY);
		int o1, o2;
		o1 = comp->get_output();
		o2 = comp->get_output2();
		comp->get_input(get_panel(posX, posY));
		ret = comp->execute_program(0);
		set_panel(posX, posY, comp->get_output());
		moved[posX + SIZE/2][posY + SIZE/2] = 1;
		change_direction(comp->get_output2());
		move();
	} while (ret !=0);
	printf("\n");
	int count=0;
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++){
			if (moved[x][y] == 1) count++;
		}
	}
	printf("Panels painted: %d\n", count);
	show_panel();
}