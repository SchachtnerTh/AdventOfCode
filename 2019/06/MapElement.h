#ifndef MAPELEMENT_H
#define MAPELEMENT_H

class MapElement {
	private:
	MapElement *attractor;
	char *name;
	int level;

	public:
	char* getName();
	int getLevel();
	void setLevel(int newLevel);
	MapElement(MapElement *newAttractor, char *newName);
	short isIt(char *searchName);
	~MapElement();
};

#endif
