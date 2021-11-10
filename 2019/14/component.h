#ifndef COMPONENT_H
#define COMPONENT_H

class component
{
  public:
     component(int iAmount, const char* sMaterial); 
	 void printComponent();
	 char* getMaterial();
	 int getAmount();
	 void reduceAmount(int reduction);
	 void increaseAmount(int increase);
  private:
     int count;
	 char *material;
};

#endif
