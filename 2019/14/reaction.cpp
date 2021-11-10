#include "reaction.h"
#include <list>
#include <iostream>

reaction::reaction()
{
	// cout << "In Constructor reaction" << endl;
  educts = new list<component *>();
  // cout << "Constructor reaction done." << endl;
}

reaction::reaction(int multiplier, reaction *source)
{
	educts = new list<component *>();
	for (component *srceducts : *source->getEducts())
	{
		component *c = new component(multiplier * srceducts->getAmount(), srceducts->getMaterial());
		educts->push_back(c);
	}
	product = new component(multiplier * source->getProduct()->getAmount(), source->getProduct()->getMaterial());
}

void reaction::addProduct(int amount, const char* material)
{
	// cout << "[" << product << "] [" << amount << "] [" << material << "]" << endl;
  product = new component(amount, material);
  // product->printComponent();
}
  
void reaction::addEduct(int amount, const char* material)
{
  component *newEduct;
  // cout << "Amount: " << amount << ", Material: " << material << endl;
  newEduct = new component(amount, material);
  //newEduct->printComponent();
  educts->push_back(newEduct);
  //cout << "Ende von addEduct" << endl;
}

void reaction::printReaction()
{
	cout << "Reaktion:" << endl;
	cout << "---------" << endl;
	cout << "Produkt: ";
	product->printComponent();
	cout << "Edukte:";
	cout << endl;
	for (component *c : *educts)
	{
		c->printComponent();
		//cout << endl;
	}
	cout << "--------------------------" << endl << endl;
}

list <component *> * reaction::getEducts()
{
	return educts;
}

component* reaction::getProduct()
{
	return product;
}

reaction::~reaction()
{
}

