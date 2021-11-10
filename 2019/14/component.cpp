#include "component.h"
#include <string.h>
#include <iostream>

using namespace std;

component::component(int iAmount, const char* sMaterial)
{
	// cout << "in constructor component." << endl;
  count = iAmount;
  material = new char[strlen(sMaterial) + 1];
  strcpy (material, sMaterial);
}

char* component::getMaterial() { return material; }
int component::getAmount() { return count; }

void component::printComponent()
{
	cout << count << " x " << material << endl;
}

void component::reduceAmount(int reduction)
{
	count -= reduction;
}

void component::increaseAmount(int increase)
{
	count += increase;
}