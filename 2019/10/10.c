#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 33

char map[SIZE][SIZE], visible[SIZE][SIZE];
int ergebnis[SIZE][SIZE];
float winkel[SIZE][SIZE];

const int VISIBLE=1;
const int INVISIBLE=2;
const int EMPTY=0;

int gcd(int a, int b)
{
    int temp;
    while (b != 0)
    {
        temp = a % b;

        a = b;
        b = temp;
    }
    return a;
}

void calculate(int y, int x) {
	int vektorX, vektorY;
	for (int tx=0; tx < SIZE; tx++) {
		for (int ty=0; ty < SIZE; ty++) {
			visible[ty][tx] = EMPTY;
		}
	}
	// erst vorwärts
	for (int dy = y; dy < SIZE; dy++) {
		for (int dx = 0; dx < SIZE; dx++) {
			if (dy == y && dx <= x) continue; // erst nach dem aktuellen Asteroiden anfangen
			if (map[dy][dx] == '#' && visible[dy][dx] == EMPTY) { // es ist ein Asteroid da und er wird auch nicht blockiert
				visible[dy][dx] = VISIBLE; // markiere als sichtbar
				vektorX = dx - x;
				vektorY = dy - y;
				if (vektorX == 0) {
					if (vektorY < 0) vektorY = -1;
					if (vektorY > 0) vektorY = 1;
				}
				if (vektorY == 0) {
					if (vektorX < 0) vektorX = -1;
					if (vektorX > 0) vektorX = 1;
				}
				// ansonsten kürzen, wenn möglich
				int krz = gcd(abs(vektorX), abs(vektorY));
				if (krz > 1) {
					vektorX /= krz;
					vektorY /= krz;
				}
				int nextX = dx + vektorX;
				int nextY = dy + vektorY;
				while (nextX < SIZE && nextY < SIZE && nextX >= 0 && nextY >= 0) {
					visible[nextY][nextX] = INVISIBLE;
					nextX += vektorX;
					nextY += vektorY;
				}
			}
		}
	}
	
	int p = 0;
	if (x == 9 && y == 5) p = 1; else p = 0;
	
	for (int dy = y; dy >= 0; dy--) {
		for (int dx = SIZE-1; dx >= 0; dx--) {
			//printf(",");
			if (dy == y && dx >= x) continue; //erst nach dem aktuellen Asteroiden anfangen
			if (map[dy][dx] == '#' && visible[dy][dx] == EMPTY) {
				visible[dy][dx] = VISIBLE; // markiere als sichtbar
				if (p == 1) printf ("%d,%d sichtbar\n", dx, dy);
				// alle dahinter müssen als nicht sichtbar markiert werden!
				vektorX = dx - x;
				vektorY = dy - y;
				if (p == 1) printf ("Vektor = %d %d", vektorX, vektorY );
				if (vektorX == 0) {
					if (vektorY < 0) vektorY = -1;
					if (vektorY > 0) vektorY = 1;
				}
				if (vektorY == 0) {
					if (vektorX < 0) vektorX = -1;
					if (vektorX > 0) vektorX = 1;
				}
				// ansonsten kürzen, wenn möglich
				int krz = gcd(abs(vektorX), abs(vektorY));
				if (krz > 1) {
					vektorX /= krz;
					vektorY /= krz;
				}
				if (p == 1) printf ("Vektor = %d %d", vektorX, vektorY );

				int nextX = dx + vektorX;
				int nextY = dy + vektorY;
				while (nextX < SIZE && nextY < SIZE && nextX >= 0 && nextY >= 0) {
					visible[nextY][nextX] = INVISIBLE;
					if (p == 1) printf ("Marking (%d|%d) as invisible\n", nextX, nextY);
					nextX += vektorX;
					nextY += vektorY;
				}				
			}
		}
	}
if (x==9 && y == 5) {
	printf ("(%d|%d)\n", x, y);
	for (int ay = 0; ay < SIZE; ay++) {
		for (int ax = 0; ax < SIZE; ax++) {
			printf ("%d", visible[ay][ax]);
		}
		printf("\n");
	}
}
	
	int visibleCount=0;
	for (int tx=0; tx < SIZE; tx++) {
		for (int ty=0; ty < SIZE; ty++) {
			if (visible[ty][tx] == VISIBLE) visibleCount++;
		}
	}
	ergebnis[y][x] = visibleCount;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Bitte Programmdatei zum Laden angeben!\n");
		return -1;
	}
	for (int x = 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			map[y][x] = 0;
			visible[y][x] = 0;
			ergebnis[y][x] = 0;
		}
	}
	FILE *f = fopen(argv[1], "r");
	for (int y = 0; y < SIZE; y++) {
		fscanf(f, "%s", map[y]);
	}
	
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			printf ("%c", map[y][x]);
		}
		printf("\n");
	}
	
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (map[y][x] == '#') 
				calculate(y,x);
		}
		printf("\n");
	}
	
		for (int ay = 0; ay < SIZE; ay++) {
		for (int ax = 0; ax < SIZE; ax++) {
			printf ("%03d ", ergebnis[ay][ax]);
		}
		printf("\n");
	}

	
	int highestErgebnis=0, highestX=0, highestY = 0;
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (ergebnis[y][x] > highestErgebnis)  {
				
				highestErgebnis = ergebnis[y][x];
				printf ("highest: %d\n", highestErgebnis);
				highestX = x;
				highestY = y;
			}
		}
	}
	printf("Highest value: %d at (%d|%d)\n", highestErgebnis, highestX, highestY);
	
	int xs = 23;
	int ys = 29;
	
	int count = 0;
	
	while (1) {
		calculate(ys, xs);
		for (int y = 0; y < SIZE; y++) {
			for (int x = 0; x < SIZE; x++) {
				winkel[y][x] = 7;
			}
		}
		for (int y = 0; y < SIZE; y++) {
			for (int x = 0; x < SIZE; x++) {
				if (visible[y][x] == VISIBLE) {
					 float tmp = atan((float)(x - xs) / (float)(ys-y));
					 printf ("x=%d, xs=%d, y=%d, ys=%d, (x-xs)=%d, (ys-y)=%d, Winkel %02.8f\n", x, xs, y, ys, x-xs, ys-y, tmp);
					 if ((x-xs) > 0 && (ys-y) > 0) winkel[y][x] = tmp;
					 if ((x-xs) > 0 && (ys-y) < 0) winkel[y][x] = tmp + M_PI;
					 if ((x-xs) < 0 && (ys-y) < 0) winkel[y][x] = tmp + M_PI;
					 if ((x-xs) < 0 && (ys-y) > 0) winkel[y][x] = tmp + 2 * M_PI;
					 if ((x-xs) == 0 && (ys-y > 0)) winkel[y][x] = 0;
					 if ((x-xs) == 0 && (ys-y < 0)) winkel[y][x] = M_PI;
					 if ((ys-y) == 0 && (x-xs > 0)) winkel[y][x] = M_PI / 2;
					 if ((ys-y) == 0 && (x-xs < 0)) winkel[y][x] = 3 * (M_PI / 2);
					 
				}
			}
		}
		
		for (int ay = 0; ay < SIZE; ay++) {
		for (int ax = 0; ax < SIZE; ax++) {
			printf ("%03.2f ", winkel[ay][ax]);
		}
		printf("\n");
	}
		
		
		int found = 0;
		float lowest = 7;
		int lowestX=SIZE, lowestY= SIZE;
		
		do {
			found = 0;
			for (int y = 0; y < SIZE; y++) {
				for (int x = 0; x < SIZE; x++) {
					float w = winkel[y][x];
					if (w != 7) {
						found = 1;
						if (w < lowest) {
							lowest = w;
							lowestX = x;
							lowestY = y;
						}
					}
				}
			}
			if (lowest != 7) {
				count ++;
				printf("%d. Asteroid. Winkel: %f. Koordinaten (%d|%d)\n", count, lowest, lowestX, lowestY);
				lowest = 7;
				map[lowestY][lowestX] = '.';
				winkel[lowestY][lowestX] = 7;
				lowestX = SIZE;
				lowestY = SIZE;

			}
		} while (found == 1);
	}
}