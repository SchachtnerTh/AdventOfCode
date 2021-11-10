#ifndef REACTION_H
#define REACTION_H

//#include<vector>
#include<list>
#include "component.h"

using namespace std;

class reaction
{
  public:
    reaction();
	reaction(int multiplier, reaction *source);
    void addProduct(int amount, const char* material);
    void addEduct(int amount, const char* material);
	list <component *> *getEducts();
	component *getProduct();
	void printReaction();
    ~reaction();
    list<component *> *educts;
    component *product;
};

#endif
