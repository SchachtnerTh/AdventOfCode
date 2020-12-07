#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstddef>

terrain::terrain (char* source) {
	terrainmap = NULL;
	FILE *f = fopen(source, "r");
	int lines=0;
	while (!feof(f)) {
		printf ("lines: %d\n" , lines);
		terrainmap = (char **)realloc(terrainmap, (lines + 1) * sizeof(char *));
		size_t thisLineWidth = 0;
		*(terrainmap + lines) = NULL;
		size_t w = getline (terrainmap + lines, &thisLineWidth, f);
		if ((*(terrainmap + lines))[w - 1] == '\n') {
			w--;
			(*(terrainmap + lines))[w - 1] == '\0';
		}
		if (width == 0) width = w;
		lines ++;
	}
	height = lines-1;
}

int terrain::getHeight() { return height; }

terrain::~terrain() {
	for (int i = height-1; i >= 0; i--) {
		free (*(terrainmap + i));
	}
	free (terrainmap);
}

void terrain::test() {
	for (int lines = 0; lines < height; lines++) {
		printf ("line %02d: ", lines);
		for (int cols = 0; cols < 2 * width; cols++) {
			printf("%c", terrainmap[lines][cols % width]);
//			printf("%c", terrainmap[0][0]);
		}
		printf("\n");
	}
}

bool terrain::isTree(int x, int y) {
	// if (*(*(terrainmap + (x % width)) + y) == 'T') return true;
	// if (*(*(terrainmap + (x % width)) + y) == '.') return false;
	//printf ("width: %d, x: %d, y: %d, height: %d\t", width, x, y, height);
	if (terrainmap[y][x % width] == '#') return true;
	if (terrainmap[y][x % width] == '.') return false;
	return false;
}