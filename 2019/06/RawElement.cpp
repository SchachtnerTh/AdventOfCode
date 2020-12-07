#include "RawElement.h"
#include <string.h>
#include <cstddef>

RawElement::RawElement(char *newAttractor, char* newRotor) {
	size_t sa, sr;
	sa = strlen(newAttractor);
	sr = strlen(newRotor);

	attractor = new char[sa];
	rotor = new char[sr];

	strcpy(attractor, newAttractor);
	strcpy(rotor, newRotor);
	used = 0;
}

RawElement::~RawElement() {
	delete attractor;
	delete rotor;
}

void RawElement::setUsed() { used=1; }
void RawElement::setUnused() { used=0; }
short RawElement::isUsed() { return used; }
short RawElement::isAttractor(char *searchAttractor) {
	return (!strcmp(searchAttractor,attractor) ? 1 : 0);
}
short RawElement::isRotor(char *searchRotor) {
	return (!strcmp(searchRotor,rotor) ? 1 : 0);
}
char *RawElement::getAttractor() { return attractor; }
char *RawElement::getRotor() { return rotor; }

