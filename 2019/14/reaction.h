#ifndef REACTION_H
#define REACTION_H

#include<list>
#include "component.h"

using namespace std;

class reaction
{
  public:
    reaction();
	reaction(unsigned long multiplier, reaction *source);
	
    void addProduct(unsigned long amount, const char* material);
    void addEduct(unsigned long amount, const char* material);
	list <component *> *getEducts();
	component *getProduct();
	void printReaction();
    ~reaction();
    list<component *> *educts;
    component *product;
	void bereinigeEdukte();
	void erweitere(unsigned long factor);
	void increaseMaterialAmount(component *secundaeredukt, long count = 1);
};

#endif
