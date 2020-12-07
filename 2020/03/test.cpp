#include <stdio.h>
#include "map.h"

terrain *t;

int trees_in_slope(int right, int down) {
	int x = 0;
	int y = 0;
	int trees = 0;
	int maxY = t->getHeight();
	for (y = 0; y < maxY; y+=down) {
		//printf ("Call isTrees(%d,%d)\t", x, y);
		if (t->isTree(x, y)) {
			trees++;
			//printf ("T");
		}
		//printf("\n");
		x+=right;
	}
	return trees;
}



int main (int argc, char **argv) {
	if (argc < 2) {
		printf ("Bitte Map als Argument mit angeben.\n");
		return -1;
	}
	t = new terrain(argv[1]);
	t->test();
	int product=1;
	int trees = 0;	

	int right=1, down=1;
	trees = trees_in_slope(right, down);
	product *= trees;
	printf ("Anzahl an Bäumen: %d,%d: %d\n", right, down, trees);

	right = 3; down = 1;
	trees = trees_in_slope(right, down);
	product *= trees;
	printf ("Anzahl an Bäumen: %d,%d: %d\n", right, down, trees_in_slope(right, down));

	right = 5; down = 1;
	trees = trees_in_slope(right, down);
	product *= trees;
	printf ("Anzahl an Bäumen: %d,%d: %d\n", right, down, trees_in_slope(right, down));

	right = 7; down = 1;
	trees = trees_in_slope(right, down);
	product *= trees;
	printf ("Anzahl an Bäumen: %d,%d: %d\n", right, down, trees_in_slope(right, down));

	right = 1; down = 2;
	trees = trees_in_slope(right, down);
	product *= trees;
	printf ("Anzahl an Bäumen: %d,%d: %d\n", right, down, trees_in_slope(right, down));
	
	printf ("Gesamptprodukt: %d\n", product);

	delete (t);
}