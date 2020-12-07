#ifndef RAWELEMENT_H
#define RAWELEMENT_H

class RawElement {
	private:
	char *attractor;
	char *rotor;
	short used;

	public:
	RawElement(char *newAttractor, char *newRotor);
	~RawElement();
	void setUsed();
	void setUnused();
	short isUsed();
	short isAttractor(char *searchAttractor);
	short isRotor(char *searchRotor);
	char *getAttractor();
	char *getRotor();
};

#endif
