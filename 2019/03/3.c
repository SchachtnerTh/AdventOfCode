#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char *schnur1=NULL;
char *schnur2=NULL;
size_t len1=0;
size_t len2=0;
signed int iMaxX=0, iMinX=0, iMaxY=0, iMinY=0;
unsigned int iWidth, iHeight;
int iStartX;
int iStartY;

struct move {
	char cDirection;
	unsigned int iLength;
};

struct move *moves1=NULL;
struct move *moves2=NULL;

struct wireInfo {
	char c;
	int wire1Steps;
	int wire2Steps;
};

struct wireInfo **matrix;

void readInput() {
	ssize_t iReadChars;
	getline(&schnur1, &len1, stdin);
	printf ("Lesen der ersten Zeile: %ld Zeichen.\n", len1);
	getline(&schnur2, &len2, stdin);
	printf ("Lesen der zweiten Zeile: %ld Zeichen.\n", len2);
}

void process(char *schnur, struct move **moveset, size_t *len) {
	signed int iPosX=0, iPosY=0;
	int iNumberOfMoves=0;
	char *tmp;
	struct move *currentMove;
	tmp = strtok(schnur, ",");
	while(tmp) {
		iNumberOfMoves++;
		*moveset = realloc(*moveset, iNumberOfMoves * sizeof(struct move));
		printf ("Nr. %d: %s\n", iNumberOfMoves, tmp);
		currentMove = *moveset + iNumberOfMoves - 1;
		currentMove->cDirection = tmp[0];
		currentMove->iLength = atoi(tmp + 1);
		tmp = strtok(NULL, ",");
	}
	*len = iNumberOfMoves;
	for (int i = 0; i < iNumberOfMoves; i++) {
		printf("Zug %d: %c - %d\n", i + 1, (*moveset + i)->cDirection, (*moveset + i)->iLength);
		switch((*moveset + i)->cDirection) {
			case 'U': iPosY -= (*moveset + i)->iLength; break;
			case 'D': iPosY += (*moveset + i)->iLength; break;
			case 'L': iPosX -= (*moveset + i)->iLength; break;
			case 'R': iPosX += (*moveset + i)->iLength; break;
		}
		if (iPosY < iMinY) iMinY = iPosY;
		if (iPosY > iMaxY) iMaxY = iPosY;
		if (iPosX < iMinX) iMinX = iPosX;
		if (iPosX > iMaxX) iMaxX = iPosX;
	}
}

struct wireInfo getAt(int x, int y) {
	return matrix[x + iStartX][y + iStartY];
}

void setAt(int x, int y, char single, char cross, int counter) {
	if (getAt(x,y).c == '\0' || getAt(x,y).c == single) {
		matrix[x + iStartX][y + iStartY].c = single;
		if (single == 'A' && (matrix[x + iStartX][y + iStartY].wire1Steps > counter || matrix[x + iStartX][y + iStartY].wire1Steps == 0)) matrix[x + iStartX][y + iStartY].wire1Steps = counter;	
		if (single == 'B' && (matrix[x + iStartX][y + iStartY].wire2Steps > counter || matrix[x + iStartX][y + iStartY].wire2Steps == 0)) matrix[x + iStartX][y + iStartY].wire2Steps = counter;
	} else {
		matrix[x + iStartX][y + iStartY].c = cross;
		if (single == 'A' && matrix[x + iStartX][y + iStartY].wire1Steps == 0) matrix[x + iStartX][y + iStartY].wire1Steps = counter;
		if (single == 'B' && matrix[x + iStartX][y + iStartY].wire2Steps == 0) matrix[x + iStartX][y + iStartY].wire2Steps = counter;
	}
}

void checkWire(struct move **moveset, size_t len, char cLineName) {
	int x = 0;
	int y = 0;
	int stepCounter=0;
	for (int i = 0; i < len; i++) {
		for (int l = 0; l < (*moveset + i)->iLength; l++) {
			stepCounter++;
			switch((*moveset + i)->cDirection) {
				case 'U': y--; break;
				case 'D': y++; break;
				case 'L': x--; break;
				case 'R': x++; break;
			}
			setAt(x, y, cLineName, 'X', stepCounter);
		}
	}
}

int main(int argc, char **argv) {
	readInput();
	process (schnur1, &moves1, &len1);
	process (schnur2, &moves2, &len2);
	iWidth = abs(iMinX) + abs(iMaxX) + 1;
	iHeight = abs(iMinY) + abs(iMaxY) + 1;
	printf("XMin = %d, XMax = %d, YMin = %d, YMax = %d\n", iMinX, iMaxX, iMinY, iMaxY);
	printf("width = %d, height = %d\n", abs(iMinX) + iMaxX + 1, abs(iMinY) + iMaxY + 1);
	printf("Länge 1: %ld, Länge 2: %ld\n", len1, len2);
	iStartX = abs(iMinX);
	iStartY = abs(iMinY);
	matrix = malloc(iWidth * sizeof(*matrix));
	for (int c=0; c < iWidth; c++) {
		//matrix[c] = malloc(iHeight * sizeof(matrix[0]));
		matrix[c] = malloc(iHeight * sizeof(struct wireInfo));
		for (int r = 0; r < iHeight; r++) {
//			printf (".");
			matrix[c][r].c=0;
			matrix[c][r].wire1Steps = 0;
			matrix[c][r].wire2Steps = 0;
		}
	}
	printf(",");
	printf ("M: %d\n", matrix[0][0].c);
	printf("First Wire\n");
	checkWire (&moves1, len1, 'A');
	printf("Second Wire\n");
	checkWire (&moves2, len2, 'B');
	printf("Wires Done\n");
	int mindist=0;
	int combisteps=0;
	for (int x=iMinX; x <= iMaxX; x++) {
		for (int y=iMinY; y <= iMaxY; y++) {
			if (getAt(x, y).c == 'X') {
				printf("%c\t", getAt(x,y).c);
				int steps = getAt(x, y).wire1Steps + getAt(x, y).wire2Steps;
				printf("steps1=%d, steps2=%d\n", getAt(x, y).wire1Steps, getAt(x, y).wire2Steps);
				if (combisteps == 0 || combisteps > steps) {
					//printf("steps1=%d, steps2=%d\n", getAt(x, y).wire1Steps, getAt(x, y).wire2Steps);
					combisteps = steps;
				}
			}
		}
	}
	printf("Lösung: %d, %d\n", mindist, combisteps);
	for (int c=0; c < iWidth; c++) {
		free(matrix[c]);
	}
	free(matrix);
	free(moves2);
	free(moves1);
	free(schnur2);
	free(schnur1);
}
