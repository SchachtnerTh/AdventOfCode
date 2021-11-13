#include "reaction.h"
#include <list>
#include <iostream>
#include <string.h>

reaction::reaction()
{
	// cout << "In Constructor reaction" << endl;
  educts = new list<component *>();
  // cout << "Constructor reaction done." << endl;
}

reaction::reaction(unsigned long multiplier, reaction *source)
{
	educts = new list<component *>();
	for (component *srceducts : *source->getEducts())
	{
		component *c = new component(multiplier * srceducts->getAmount(), srceducts->getMaterial());
		educts->push_back(c);
	}
	product = new component(multiplier * source->getProduct()->getAmount(), source->getProduct()->getMaterial());
}

void reaction::addProduct(unsigned long amount, const char* material)
{
	// cout << "[" << product << "] [" << amount << "] [" << material << "]" << endl;
  product = new component(amount, material);
  // product->printComponent();
}
  
void reaction::addEduct(unsigned long amount, const char* material)
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
	for (component *educt : *educts)
	{
		delete educt;
	}
	delete educts;
	delete product;
}

void reaction::bereinigeEdukte()
{
		for (list<component *>::iterator it = educts->begin(); it != educts->end(); )
		{
			if ((*it)->getAmount() == 0) {
				//cout << "Remove." << (*it)->getMaterial() << endl;
				it = educts->erase(it);
				//cout << "done." << *it << endl;
			} else {
				++it;
			}
		}
}

void reaction::erweitere(unsigned long factor)
{
	product->setAmount(product->getAmount() * factor);
	for (list<component *>::iterator it = educts->begin(); it != educts->end(); ++it)
	{
		(*it)->setAmount((*it)->getAmount() * factor);
	}
}

void reaction::increaseMaterialAmount(component *secundaeredukt, long count)
{
	bool found=false;
	for (component *primaeredukt : *educts)
	{
		if (strcmp(primaeredukt->getMaterial(), secundaeredukt->getMaterial()) == 0)
		{
			// Wenn ja, dann erhöhe die Anzahl der bereits bestehenden Edukte
			found = true;
			primaeredukt->increaseAmount(secundaeredukt->getAmount() * count);
		}
	}
	if (!found)
	{
		// Wenn nein, füge ein neues Edukt zur Liste hinzu
		component *newEduct = new component(secundaeredukt->getAmount() * count, secundaeredukt->getMaterial());
		educts->push_back(newEduct);
	}

}