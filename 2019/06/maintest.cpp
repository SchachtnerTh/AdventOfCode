#include "MapElement.h"
#include "RawElement.h"
#include <stdio.h>
#include <string.h>
#include <vector>

std::vector<RawElement *> liste;
int fullLevel=0;

void read_program(char *progFile) {
	char *line = NULL;
	size_t linelen;
	linelen = 0;
	FILE *f = fopen(progFile, "r");
	while (getline(&line, &linelen, f)!=-1) {
			char* pos = strstr(line, ")");
			char* strAttractor;
			char* strRotor;
			size_t diff = (size_t)(pos-line);
			strAttractor = new char[diff+1];
			strncpy(strAttractor, line, diff);
			strAttractor[diff]=0;
			int sLen;
			sLen = strlen(pos + 1) - 1;
			strRotor = new char[sLen + 1];
			strncpy(strRotor, pos + 1, sLen);
			strRotor[sLen]=0;
			RawElement *re = new RawElement(strAttractor, strRotor);
			liste.push_back(re);
			delete strAttractor;
			delete strRotor;
	}
	fclose(f);
}

void insertMapTile(MapElement *attractor) {
	int count=0;
	for (RawElement *e : liste) {
		if (!e->isUsed()) {
			if (!strcmp(e->getAttractor(), attractor->getName())) {
				MapElement *newElement = new MapElement(attractor, e->getRotor());
				fullLevel += newElement->getLevel();
				insertMapTile(newElement);
				e->setUsed();
			}
		}
	}
}

int countTransfers(RawElement *start, RawElement *end, int transfers) {
	if (!strcmp(end->getAttractor(),start->getRotor())) { printf("Anzahl Transfers: %d\n", transfers); return 1; }
	for (RawElement *e : liste) {
		if (!e->isUsed()) {
			if (!strcmp(start->getRotor(), e->getAttractor())) {
				e->setUsed();
				countTransfers(e, end, transfers+1);
			}
			if (!strcmp(start->getAttractor(), e->getRotor())) {
				e->setUsed();
				countTransfers(e, end, transfers+1);
			}
		}
	}
}

int main(int argc, char **argv) {
	read_program(argv[1]);
	MapElement *root = new MapElement(NULL, "COM");

// welche Attraktoren sind nicht auch Rotoren, sind also selbst COM?
	char *attr;
	attr = new char[4];

	for (RawElement *e : liste ) {
		int found = 0;
		strcpy(attr, e->getAttractor());
		for (RawElement *f : liste) {
			if (!strcmp(attr, f->getRotor())) found++;
		}
		if (!found) {
			printf("Top level element: %s)%s\n", e->getAttractor(), e->getRotor());
		}
	}

	insertMapTile(root);

	printf("\n");
	printf("FullLevel: %d\n", fullLevel);
	RawElement *rawAttrStart = NULL, *rawAttrEnd = NULL;
	for (RawElement *e : liste) {
		e->setUnused();
		if (e->isRotor("YOU")) { rawAttrStart = e; }
		if (e->isRotor("SAN")) { rawAttrEnd = e; }
	}
	printf ("Start: %p, End: %p\n", rawAttrStart, rawAttrEnd);
	countTransfers(rawAttrStart, rawAttrEnd, 0);

}
