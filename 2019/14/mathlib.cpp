#include "mathlib.h"

unsigned long mathlib::ggT(unsigned long zahl1, unsigned long zahl2)
{
  if(zahl2 == 0)
  {
   return zahl1;
  }
  return ggT(zahl2, zahl1%zahl2);
}

unsigned long mathlib::kgV(unsigned long zahl1, unsigned long zahl2)
{
   return (zahl1*zahl2)/ggT(zahl1, zahl2);
}
