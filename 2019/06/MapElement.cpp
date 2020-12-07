#include "MapElement.h"
#include <cstddef>
#include <string.h>

#define DEBUG 0

#ifdef DEBUG
#include<stdio.h>
#endif

MapElement::MapElement(MapElement *newAttractor, char *newName) {
	size_t nameLen;

	if (DEBUG) printf ("newAttractor: %p\n", newAttractor);

	if (newAttractor == NULL) {
		if (DEBUG) printf ("isNull");
		level = 0;
	} else {
		if (DEBUG) printf ("isNotNull");
		level = newAttractor->getLevel() + 1;
	}

	nameLen = strlen(newName);
	name = new char[nameLen];
	strcpy(name, newName);

	attractor = newAttractor;
}

MapElement::~MapElement() {
	delete(name);
}

char *MapElement::getName() { return name; }
int MapElement::getLevel() { return level; }
void MapElement::setLevel(int newLevel) { level = newLevel; }
short MapElement::isIt(char *searchName) { return (!strcmp(name,searchName) ? 1 : 0); }
