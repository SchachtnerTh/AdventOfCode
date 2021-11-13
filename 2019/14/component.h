#ifndef COMPONENT_H
#define COMPONENT_H

class component
{
  public:
     component(long iAmount, const char* sMaterial); 
	 void printComponent();
	 char* getMaterial();
	 long getAmount();
	 void reduceAmount(long reduction);
	 void increaseAmount(long increase);
	 void setAmount(long newAmount);
	 ~component();
  private:
     long count;
	 char *material;
};

#endif
