#include <iostream>
#include <vector>
#include<string.h>
#include "component.h"
#include "reaction.h"
#include "mathlib.h"
using namespace std;

vector<reaction *> *reactions;
unsigned long ores;
unsigned long fuels;

reaction *findReactionFromProductMaterial(const char *productMaterial)
{
	for (reaction *r : *reactions)
	{
		if (strcmp(r->getProduct()->getMaterial(), productMaterial) == 0)
		{
			return r;
		}
	}
	return NULL;
}

unsigned long berechneReaktionen(unsigned long fuelCount, bool allow_leftovers = true) // leftovers_allowed: wenn true, dann dürfen auch Produkte übrig bleiben
{
	int ersetzungen;
	bool lastrun = false;
	// suche die Reaktion, bei der das Produkt "FUEL" ist
	reaction *rootreaction = findReactionFromProductMaterial("FUEL");
	reaction *backup_root = NULL;
	//rootreaction->erweitere(fuelCount);
	unsigned long produced_fuel = 0L;
	unsigned long needed_ore = 0L;
	list <component *> *leftovers = new list<component *>();
	do
	{
		//cout << "vor den leftovers" << endl;
		//rootreaction->printReaction();
		if (backup_root != NULL)
		{
			for (vector<reaction *>::iterator it = reactions->begin(); it != reactions->end(); ++it)
			{
				if (strcmp((*it)->getProduct()->getMaterial(), "FUEL") == 0) {
					reactions->erase(it);
					break;
				}
			}
			reaction *r = new reaction(1, backup_root);
			reactions->push_back(r);
			delete rootreaction;
			rootreaction = findReactionFromProductMaterial("FUEL");
		}
		if (leftovers->size() != 0)
		{
			for (component *old_leftover : *leftovers)
			{
				rootreaction->increaseMaterialAmount(old_leftover);
			}
		}
		//cout << "nach den leftovers" << endl;
		//rootreaction->printReaction();
		do // Durchlaufe diese while-Schleife, solange die Variable "lastrun" auf true gesetzt ist
		{
			do // Durchlaufe diese while-Schleife, solange noch Edukte der Root-Reaktion ("FUEL") durch andere Reaktionen ersetzt werden können
			{
				ersetzungen = 0; // Zähle die Anzahl der Ersetzungen, fange bei 0 an.
				for (component *educt : *rootreaction->getEducts()) // gehe durch alle Edukte der Root-Reaktion
				{
	//				cout << "Edukt: " << educt->getMaterial() << ", Menge: " << educt->getAmount() << endl;
					if (strcmp(educt->getMaterial(), "ORE") == 0) continue; // ORE kann nicht durch andere Reaktionen erzeugt werden, deswegen gleich weiter zum nächsten Edukt
					if (educt->getAmount() <= 0) continue; // Wenn ein Edukt der Menge 0 (oder ggf. sogar mit negativen Mengen) benötigt wird, ebenfalls weiter zum nächsten.
					
					// Das aktuell Edukt wird mindestens einmal benötigt. Suche jetzt die Reaktion, die dieses Edukt erzeugt (wo es also PRODUKT ist) (--> Sekundärreaktion)
					reaction *sekundaerreaktion = findReactionFromProductMaterial(educt->getMaterial());
	//				cout << "Sekundärreaktion: " << endl;
	//				sekundaerreaktion->printReaction();
					if (sekundaerreaktion->getProduct()->getAmount() > educt->getAmount()) 
						// Wenn mehr vom Produkt der Sekundärreaktion benötigt wird, als bei einer Reaktion entsteht, so kann die Reaktion einmal komplett ausgeführt werden.
						// Die durch die Sekundärreaktion entstandene Menge and Produkten kann von der Menge der Edukte der Root-Reaktion abgezogen werden. Die Edukte der Sekundärreaktion
						// müssen dann zur Liste der Edukte der Root-Reaktion hinzugefügt werden. (Das kann auch öfters passieren, wenn die Sekundärreaktion öfters ausgeführt werden kann, um den
						// Bedarf in der Root-Reaktion zu decken.)
					{
						if (!lastrun)
						{ 
							// Wenn wir nicht im "lastrun"-Modus laufen, kann keine Ersetzung durchgeführt werden.
							//  Es würden sonst mehr Elemente durch die Sekundärreaktion erzeugt werden als gebraucht würden und das wird erst ganz am Schluss gemacht.
	//						cout << "(Noch) Keine Ersetzung möglich!" << endl;
						} else {
							//cout << "JETZT WIRD ALLES ERSETZT!" << endl;
							// Im lastrun-Modus werden die Sekundärreaktionen auch ausgeführt, wenn dabei Produkte übrig bleiben.
							// Die Anzahl der durch die Sekundärreaktion erzeugten Produkte wird von der Menge der Edukte der Root-Reaktion abgezogen. Hier können auch negative Werte entstehen.
							educt->reduceAmount(sekundaerreaktion->getProduct()->getAmount());

							//rootreaction->printReaction();
							// Jetzt gehe durch alle Edukte der Sekundärreaktion und suche, ob sie auch in der Edukte-Liste der Root-Reaktion schon vorkommen
							for (component *secundaeredukt : *sekundaerreaktion->getEducts())
							{
								rootreaction->increaseMaterialAmount(secundaeredukt);
							}						
							//rootreaction->printReaction();
						}
					} else {
						// Wenn die Sekundärreaktion durchgeführt werden kann und die komplette Menge des Produkts in der Root-Reaktion auch benötigt wird.
						int count=0; // Es kann sein, dass die Sekundärreaktion sogar mehrmals ablaufen kann, um den Bedarf in der Root-Reaktion zu decken. Das soll hier gezählt werden.
						while (sekundaerreaktion->getProduct()->getAmount() <= educt->getAmount())
						{
							count++; // zählt mit, wie oft die Reaktion substituiert werden kann
							educt->reduceAmount(sekundaerreaktion->getProduct()->getAmount());
						}
						ersetzungen++; // Counter hochzählen. Wird benötigt, um zu erkennen, dass noch eine Ersetzung durchgeführt werden konnte. Wenn der Counter mal 0 ist, dann kann keine
						// Sekundärreaktion mehr ausgeführt werden, die komplett in der Root-Reaktion verwendet werden kann. Es würde also ein Teil des Produkts der Sekundärreaktion übrig bleiben.
						for (component *secundaeredukt : *sekundaerreaktion->getEducts())
						{
							rootreaction->increaseMaterialAmount(secundaeredukt, count);
						}
	//					cout << "Zwischenergebnis" << endl;
	//					rootreaction->printReaction();
	//					cout << "++++++++++++++++" << endl;
					}
				}
			}
			while (ersetzungen > 0); // Gehe immer wieder durch die Liste der Edukte der Root-Reaktion, bis keine Ersetzungen durch Sekundärreaktionen mehr möglich sind.
			if (!lastrun) {
				if (allow_leftovers)
				{
					// Wenn die Ersetzung noch nicht im "lastrun"-Modus gelaufen ist, dann aktiviere ihn jetzt. Ersetzungen werden jetzt auch gemacht, wenn Edukte übrig bleiben sollten
					// Auch hier können mehrfach Ersetzungen passieren
					lastrun = true;
					//cout << "Verteilung der Edukte, bevor welche übrig bleiben:" << endl; // Vorher nochmal die Edukte auflisten
					//rootreaction->printReaction();
					// Kopiere die Root-Reaktion weg, um sie für spätere Reaktionen wieder verwenden zu können
					if (!backup_root)
					{
						backup_root = new reaction(1, rootreaction);
						//cout << " * Diese Reaktion wurde weggesichert: " << endl;
						//backup_root->printReaction();
						//cout << " *************************** " << endl;
					}
				}
				else
				{
					// Leftovers werden nicht erlaubt
					// Dann unfertig zurück
					return -1;
				}
			} else
				lastrun = false; // Wenn der Lastrun-Modus schon aktiviert war, dann hier wieder beenden, dass die Schleife beendet wird.
		}
		while (lastrun);  // Alle Ersetzungen sind passiert (ohne und mit "lastrun")
		//cout << "Ersetzungen: " << ersetzungen << endl;

		// Suche das Edukt "ORE" und liefere die Anzahl zurück. Das ist die Anzahl an ORE, die für ein FUEL benötigt wird.
		// Alle anderen Edukte-Mengen sollten hier 0 oder negativ sein.
		for (component *educt : *rootreaction->getEducts())  
		{
			if (strcmp(educt->getMaterial(), "ORE") == 0)
			{
				needed_ore += educt->getAmount();
			}
		}
		
		produced_fuel += rootreaction->getProduct()->getAmount();
		
		if ((produced_fuel % 100000) == 0) cout << "Verbrauchte ORE: " << needed_ore << " ORE, produzierte FUELs: " << produced_fuel << " FUEL." << endl;
		ores = needed_ore;
		fuels = produced_fuel;
		for (component *left : *leftovers)
		{
			delete left;
		}
		leftovers->clear();
		for (component *left_over_component : *rootreaction->getEducts())
		{
			if (left_over_component->getAmount() < 0)
			{
				component *c = new component(left_over_component->getAmount(), left_over_component->getMaterial());
				leftovers->push_back(c);
			}
		}
		
	}
	while (produced_fuel < fuelCount);

	cout << "Sollmenge von " << fuelCount << " FUEL erreicht. Aktuell: " << produced_fuel << " FUEL. Benötigt: " << needed_ore << " ORE." << endl;

	// Die originale Root-Reaktion wiederherstellen, dass die Funktion wieder aufgerufen werden kann.
	if (backup_root != NULL)
	{
		for (vector<reaction *>::iterator it = reactions->begin(); it != reactions->end(); ++it)
		{
			if (strcmp((*it)->getProduct()->getMaterial(), "FUEL") == 0) {
				reactions->erase(it);
				break;
			}
		}
		reaction *r = new reaction(1, backup_root);
		reactions->push_back(r);
		delete rootreaction;
		rootreaction = findReactionFromProductMaterial("FUEL");
	}



	return needed_ore;
}

int main (int argc, char **argv)
{
	// Reaktionen der Nanofactory in Vektor abspeichern
    reactions = new vector<reaction *>();
    char *str1, *str2;
	
	// Einfach mal 1000 Bytes reservieren (soll irgendwann mal dynamisch passieren...)
    str1 = new char[1000];
    str2 = new char[1000];
	
	// Ist ein Dateiname angegeben?
    if (argc != 2) {
      cout << "Kein Dateiname angegeben!" << endl;
	  //  Nein, dann Ende!
      return -1;
    }

	// Einlesen der Daten und Befüllen einer Datenstruktur "reactions"
    FILE *f;
    f = fopen(argv[1], "r");

    while (!feof(f)) {
		// Aus Datei lesen (Edukt(e) => Produkt)
		// Edukt(e) werden in str1 abgespeichert
		// Produkt wird in str2 abgespeichert
      fscanf (f, "%[0-9A-Z, ] => %[0-9A-Z ]\n", str1, str2);
      //cout << str1 << " *** " << str2 << endl;
	  // Es wird eine nue Instanz von "reaction" deklariert und instatiiert.
      reaction *r;
	  // cout << "R3";
      r = new reaction();
	  // cout << "R2";
	  // Die Instanz wird in den Vektor gehängt
	  reactions->push_back(r);
	  // cout << "R1";
	  // cout << "Reaction added." << endl;
	  
	  // Aus str2 werden jetzt die Menge und das Material des Produkts extrahiert
	  // und in der Reaktion abgespeichert
	  int amount;
	  char *material;
	  sscanf(str2, "%d %ms", &amount, &material);
      r->addProduct(amount, material);
	  
	  // Aus str1 werden jetzt die einzelnen Edukte separiert und dann jeweils nach Menge und Material getrennt in die Edukte-Liste der Reaktion geschrieben
	  char *tmp = new char[strlen(str1) + 1];
	  if (tmp = strtok(str1, ",")) {
		  int educt_amount;
		  char *educt_material;
		  // cout << tmp << endl;
		  sscanf(tmp, "%d %ms", &educt_amount, &educt_material);
		  // cout << "Amount: " << educt_amount << ", Material2: " << educt_material << endl;
		  r->addEduct(educt_amount, educt_material);
		  while (tmp = strtok(NULL, ",")) {
			  int educt_amount2;
			  char *educt_material2;
			  sscanf(tmp, "%d %ms", &educt_amount2, &educt_material2);
			  r->addEduct(educt_amount2, educt_material2);			  
		  }
	  }
	  
	  
	  //r->printReaction();
	  // Eine komplette Reaktion ist jetzt eingelesen und im Vektor abgespeichert
    }
	
	// Alle Reaktionen sind im Vektor abgespeichert
	
	unsigned long oreForOneFuel = berechneReaktionen(1);
	cout << "Anzahl an benötigten ORE für 1 FUEL: " << oreForOneFuel << endl;
	
	//berechneReaktionen(75120192);
	
/*
	unsigned long capacityOre = 1000000000000;
	unsigned long fuelForCapacityOre = capacityOre / oreForOneFuel;
	cout << "Aus " << capacityOre << " ORE könnten demnach " << fuelForCapacityOre << " FUELs produziert werden." << endl;
	cout << "Mit Algorithmus berechnen, wie viele ORE die " << fuelForCapacityOre << " FUELs wirklich benötigen: ";
	unsigned long realOreforCapacityFuels = berechneReaktionen(fuelForCapacityOre);
	cout << realOreforCapacityFuels << " ORE" << endl;
	double efficientOresPerFuel, efficientFuelsPerOre;
	efficientOresPerFuel = (double)realOreforCapacityFuels / (double)fuelForCapacityOre;
	efficientFuelsPerOre = 1 / efficientOresPerFuel;
	cout << "In großen Mengen also " << efficientOresPerFuel << " ORE pro FUEL oder " << efficientFuelsPerOre << " FUEL pro ORE." << endl;
	cout << "Mit dieser Rechnung können aus " << capacityOre << " ORE insgesamt " << (int)(efficientFuelsPerOre * capacityOre) << " FUELs erzeugt werden." << endl;
	//cout << "Anzahl an benötigten ORE für 955854 FUEL: " << berechneReaktionen(955854) << endl;
	//https://www.reddit.com/r/adventofcode/comments/eafj32/2019_day_14_solutions/femh2j0/d
	
	return 0;
*/	
	cout << endl << endl << "Teilaufgabe 2" << endl;

	unsigned long gesamtkgv=1;
	unsigned long zwischenkgv=0;
	reaction *r = findReactionFromProductMaterial("FUEL");
	reaction *backup_root = new reaction(1, r); // die brauchen wir, um die originale Root-Reaktion später wiederherstellen zu können
	vector<unsigned long> kgvlist;

	do
	{
		zwischenkgv = 0;
		r->erweitere(gesamtkgv);
		kgvlist.clear();
		cout << "Es bleiben übrig: " << (signed long) berechneReaktionen(1, false) << endl;;
		
		r->printReaction();
		r->bereinigeEdukte();
		//r->printReaction();
		for (component *educt : *r->getEducts())
		{
			if (strcmp(educt->getMaterial(), "ORE") == 0) continue;
			reaction *r2 = findReactionFromProductMaterial(educt->getMaterial());
			unsigned long eductAmount = educt->getAmount();
			unsigned long productAmount = r2->getProduct()->getAmount();
			unsigned long kgv = mathlib::kgV(eductAmount, productAmount);
			if ((productAmount % eductAmount) == 0) kgv=productAmount/eductAmount;
			cout << eductAmount << " x " << educt->getMaterial() << " (Reaction generates " << productAmount << "), kgV: " << kgv << endl;
			kgvlist.push_back(kgv);
		}
		
		for (unsigned long kgv : kgvlist)
		{
			cout << "kgV: " << kgv << endl;
		}
		
		
		for (unsigned long i=1; i < kgvlist.size(); i++)
		{
			if (zwischenkgv == 0) zwischenkgv=kgvlist[0];
			zwischenkgv = mathlib::kgV(zwischenkgv, kgvlist[i]);
		}
		
		if (zwischenkgv != 0)
		{
			gesamtkgv *= zwischenkgv;
		}
		cout << "Gesamt-kgV: " << gesamtkgv << endl;
	}
	while (zwischenkgv != 0 && gesamtkgv < 10000000000);
	
	unsigned long needed_ore = berechneReaktionen(1);
	unsigned long produced_fuel = r->getProduct()->getAmount();
	
	cout << "Zurück. ORE: " << ores << ", FUEL: " << fuels << "." << endl;
	
	unsigned long numberReactions = 1000000000000 / ores;
	if (numberReactions == 0) numberReactions = 1;
	unsigned long fuelAfterReactions = numberReactions * fuels;
	unsigned long usedOresAfterReactions = numberReactions * ores;
	unsigned long remainigOresAfterReactions = 1000000000000 - usedOresAfterReactions;
	double fuelPerOre = (double)fuelAfterReactions / (double)usedOresAfterReactions;
	
	cout << "Reaktion kann " << numberReactions << " mal ablaufen." << endl;
	cout << "Dabei werden " << fuelAfterReactions << " FUELs erzeugt und " << usedOresAfterReactions << " ORE benötigt." << endl;
	cout << "Kosten: " << fuelPerOre << endl;
	cout << "Mit 1.000.000.000.000 ORE " << " können " << (int)(fuelPerOre * 1000000000000) << " FUELs produziert werden." << endl;
	
			//rootreaction->erweitere(360);
//			rootreaction->printReaction();
			//berechneReaktionen();
			//rootreaction->printReaction2();
//			return 0;
	
	// Alle Daten sind eingelesen
	//vereinfache_Reaktion("A", "ORE");
	//component *c = new component (1, "C");
	//vereinfache_Reaktion(c, "ORE");
	
	/* reaction *root = findReactionFromProductMaterial("FUEL");
	unsigned long multiplier = 460662;
	unsigned long ores;
	
	do
	{
		multiplier++;
		//if (multiplier % 10 == 0)
			cout << multiplier << " FUEL(s)" << endl;
		for (vector<reaction *>::iterator it = reactions->begin(); it != reactions->end(); ++it)
		{
			if (strcmp((*it)->getProduct()->getMaterial(), "FUEL") == 0) {
				reactions->erase(it);
				break;
			}
		}

		reaction *newroot = new reaction(multiplier, root);
		reactions->push_back(newroot);

		ores = berechneReaktionen();
		cout << ores << " OREs" << endl;
	}
	while (ores < 1000000000000);
	*/
}
