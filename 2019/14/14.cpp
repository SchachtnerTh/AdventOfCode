#include <iostream>
#include <vector>
#include<string.h>
#include "component.h"
#include "reaction.h"
using namespace std;

vector<reaction *> *reactions;

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

unsigned long berechneReaktionen()
{
	int ersetzungen;
	bool lastrun = false;
	// suche die Reaktion, bei der das Produkt "FUEL" ist
	reaction *rootreaction = findReactionFromProductMaterial("FUEL");
//	rootreaction->printReaction();
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
//						cout << "JETZT WIRD ALLES ERSETZT!" << endl;
						// Im lastrun-Modus werden die Sekundärreaktionen auch ausgeführt, wenn dabei Produkte übrig bleiben.
						// Die Anzahl der durch die Sekundärreaktion erzeugten Produkte wird von der Menge der Edukte der Root-Reaktion abgezogen. Hier können auch negative Werte entstehen.
						educt->reduceAmount(sekundaerreaktion->getProduct()->getAmount());

						// Jetzt gehe durch alle Edukte der Sekundärreaktion und suche, ob sie auch in der Edukte-Liste der Root-Reaktion schon vorkommen
						for (component *secundaeredukt : *sekundaerreaktion->getEducts())
						{
							bool found=false;
							for (component *primaeredukt : *rootreaction->getEducts())
							{
								if (strcmp(primaeredukt->getMaterial(), secundaeredukt->getMaterial()) == 0)
								{
									// Wenn ja, dann erhöhe die Anzahl der bereits bestehenden Edukte
									found = true;
									primaeredukt->increaseAmount(secundaeredukt->getAmount());
								}
							}
							if (!found)
							{
								// Wenn nein, füge ein neues Edukt zur Liste hinzu
								component *newEduct = new component(secundaeredukt->getAmount(), secundaeredukt->getMaterial());
								rootreaction->getEducts()->push_back(newEduct);
							}
						}						
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
						// Gehe wieder durch alle Edukte der Sekundärreaktion...
						bool found=false;
						for (component *primaeredukt : *rootreaction->getEducts())
						{
							// ... und suche, ob die Produkte auch in der Root-Reaktion schon enthalten sind.
							if (strcmp(primaeredukt->getMaterial(), secundaeredukt->getMaterial()) == 0)
							{
								// Wenn ja, dann zähle die in der Sekundärreaktion benötigten Mengen zu den Edukten der Root-Reaktion hinzu.
								// Konnte die Sekundärreaktion mehrfach ablaufen, zähle ein Vielfaches dieser Menge dazu.
								found = true;
								primaeredukt->increaseAmount(count * secundaeredukt->getAmount());
							}
						}
						if (!found)
						{
							// Wenn nein, füge ein neues Edukt hinzu und setze die Menge so, dass mehrfache Reaktionen berücksichtigt werden.
							component *newEduct = new component(count * secundaeredukt->getAmount(), secundaeredukt->getMaterial());
							rootreaction->getEducts()->push_back(newEduct);
						}
					}
//					cout << "Zwischenergebnis" << endl;
//					rootreaction->printReaction();
//					cout << "++++++++++++++++" << endl;
				}
			}
		}
		while (ersetzungen > 0); // Gehe immer wieder durch die Liste der Edukte der Root-Reaktion, bis keine Ersetzungen durch Sekundärreaktionen mehr möglich sind.
		if (!lastrun) {
			// Wenn die Ersetzung noch nicht im "lastrun"-Modus gelaufen ist, dann aktiviere ihn jetzt. Ersetzungen werden jetzt auch gemacht, wenn Edukte übrig bleiben sollten
			// Auch hier können mehrfach Ersetzungen passieren
			lastrun = true;
			cout << "Verteilung der Edukte, bevor welche übrig bleiben:" << endl; // Vorher nochmal die Edukte auflisten
			rootreaction->printReaction();
		} else
			lastrun = false; // Wenn der Lastrun-Modus schon aktiviert war, dann hier wieder beenden, dass die Schleife beendet wird.
	}
	while (lastrun);  // Alle Ersetzungen sind passiert (ohne und mit "lastrun")
//	cout << "Ersetzungen: " << ersetzungen << endl;
//	rootreaction->printReaction();

	// Suche das Edukt "ORE" und liefere die Anzahl zurück. Das ist die Anzahl an ORE, die für ein FUEL benötigt wird.
	// Alle anderen Edukte-Mengen sollten hier 0 oder negativ sein.
	for (component *educt : *rootreaction->getEducts())  
	{
		if (strcmp(educt->getMaterial(), "ORE") == 0)
		{
			return educt->getAmount();
		}
	}
	
	// Wenn wir hierher kommen, ist was schief gelaufen.
	// Ich will da jetzt gar nicht dran denken, wie das passieren kann...
	return -1;
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
	
	cout << "Anzahl an benötigten ORE: " << berechneReaktionen() << endl;
	
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
