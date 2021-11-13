#include "component.h"
#include <string.h>
#include <iostream>

using namespace std;

component::component(long iAmount, const char* sMaterial)
{
	// cout << "in constructor component." << endl;
  count = iAmount;
  material = new char[strlen(sMaterial) + 1];
  strcpy (material, sMaterial);
}

char* component::getMaterial() { return material; }
long component::getAmount() { return count; }

void component::printComponent()
{
	cout << count << " x " << material << endl;
}

void component::reduceAmount(long reduction)
{
	count -= reduction;
}

void component::increaseAmount(long increase)
{
	count += increase;
}

void component::setAmount(long newAmount)
{
	count = newAmount;
}

component::~component()
{
	delete material;
}