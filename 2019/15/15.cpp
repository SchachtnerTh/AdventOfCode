#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <limits.h>

#include "intcomp.h"


using namespace std;

#define NORTH 1
#define SOUTH 2
#define WEST  3
#define EAST  4

#define OXYGEN 'O'
#define VACUUM '.'
#define WALL '#'


long x = 0;
long y = 0;
intcomp *c;
int step;



enum dir { DIR_N = NORTH, DIR_S = SOUTH, DIR_W = WEST, DIR_E = EAST };

class location {
	public:
		char type;
		long cost;
		long x;
		long y;
		location(long x, long y, char type, int cost);
};

location::location(long x, long y, char type, int cost) : x (x), y (y), type (type), cost(cost) {
	cost = 1; // erst mal nur, um zu bezeichnen, dass schon jemand da war;
}

class locationmap {
	public:
		list<location> *locationlist;
		locationmap();
		bool add(long x, long y, char type, bool updateSteps=true);
		long find(long x, long y);
		long find_min_x();
		long find_max_x();
		long find_min_y();
		long find_max_y();
		long getCost(long x, long y);
		void setCost(long x, long y, int cost);
		void setType(long x, long y, int type);
		int getType(long x, long y);
		int count_vacuum_positions();
		~locationmap();
};

locationmap::~locationmap() {
	delete locationlist;
}

locationmap::locationmap() {
	locationlist = new list<location>();
}

long locationmap::find(long x, long y) {
	for (list<location>::iterator it = locationlist->begin(); it != locationlist->end(); ++it){
		if (it->x == x && it->y == y) {
			return it->type;
		}
	}
	return -1; // not found
}

long locationmap::getCost(long x, long y) {
	for (list<location>::iterator it = locationlist->begin(); it != locationlist->end(); ++it){
		if (it->x == x && it->y == y) {
			return it->cost;
		}
	}
	return -1; // not found
}

void locationmap::setType(long x, long y, int type) {
	for (list<location>::iterator it = locationlist->begin(); it != locationlist->end(); ++it) {
		if (it->x == x && it->y == y) {
			it->type = type;
			return;
		}
	}
}

int locationmap::getType(long x, long y) {
	for (list<location>::iterator it = locationlist->begin(); it != locationlist->end(); ++it) {
		if (it->x == x && it->y == y) {
			return it->type;
		}
	}
	return -1;
}

void locationmap::setCost(long x, long y, int cost) {
	for (list<location>::iterator it = locationlist->begin(); it != locationlist->end(); ++it){
		if (it->x == x && it->y == y) {
			it->cost = cost;
		}
	}
}

long locationmap::find_min_x() {
	int minx=INT_MAX;
	for (list<location>::iterator it = locationlist->begin(); it != locationlist->end(); ++it){
		if (minx == INT_MAX) {
			minx = it->x;
		} else {
			if (it->x < minx) minx=it->x;
		}
	}
	return minx;
}

long locationmap::find_max_x() {
	int maxx=INT_MAX;
	for (list<location>::iterator it = locationlist->begin(); it != locationlist->end(); ++it){
		if (maxx == INT_MAX) {
			maxx = it->x;
		} else {
			if (it->x > maxx) maxx=it->x;
		}
	}
	return maxx;
}

long locationmap::find_min_y() {
	int miny=INT_MAX;
	for (list<location>::iterator it = locationlist->begin(); it != locationlist->end(); ++it){
		if (miny == INT_MAX) {
			miny = it->y;
		} else {
			if (it->y < miny) miny=it->y;
		}
	}
	return miny;
}

long locationmap::find_max_y() {
	int maxy=INT_MAX;
	for (list<location>::iterator it = locationlist->begin(); it != locationlist->end(); ++it){
		if (maxy == INT_MAX) {
			maxy = it->y;
		} else {
			if (it->y > maxy) maxy=it->y;
		}
	}
	return maxy;
}

bool locationmap::add(long x, long y, char type, bool updateSteps) {
	if (find(x, y) == -1) {
		location *l;
		if (updateSteps) {
			if (type == VACUUM) {
				l = new location(x, y, type, step);
			} else {
				l = new location(x, y, type, -1);
			}
		}
		
		locationlist->push_back(*l);
		return false;
	} else {
		//cout << "An Stelle (" << x << "," << y << ") waren wir bereits!" << endl;
		if (updateSteps) {
			if (getCost(x,y) > step) {
				//cout << "Kosten alt: " << getCost(x,y) << ", neu: " << step << endl;
				setCost(x,y,step);
				//cout << "Kosten für Feld aktualisiert" << endl;
				return false;
			}
		}
		return true;
	}
}

locationmap *oxygen;

int locationmap::count_vacuum_positions() {
	int vacpos=0;
	// Hier werden alle Zellen gezählt, in denen noch kein Sauerstoff angelangt ist ('.')
	// Außerdem wird hier auch gleich noch die Liste gefüllt mit allen sauerstoffgefüllten Zellen.
	for (list<location>::iterator it = locationlist->begin(); it != locationlist->end(); ++it){
		if (it->type == VACUUM) vacpos++;
		if (it->type == OXYGEN) oxygen->add(it->x, it->y, OXYGEN);
	}
	return vacpos;
}

locationmap *lm;


int gehe(int richtung) {
	bool schonmalda=false;
	c->get_input((long)richtung);
	switch (richtung) {
		case WEST : x--; break;
		case EAST : x++; break;
		case NORTH : y++; break;
		case SOUTH : y--; break;
	}

	c->execute_program(0);
	
	int status = c->get_output();
	
	switch (status) {
		case 0 : 
			schonmalda=lm->add(x, y, WALL); 
			switch (richtung)
			{
				case NORTH : y--; break; // Bewegung wieder rückgängig machen
				case EAST  : x--; break; // Bewegung wieder rückgängig machen
				case SOUTH : y++; break; // Bewegung wieder rückgängig machen
				case WEST : x++; break; // Bewegung wieder rückgängig machen
			}
			break;
		case 1 : 
			schonmalda=lm->add(x, y, VACUUM); 
			break;
		case 2 : 
			schonmalda=lm->add(x, y, OXYGEN); 
			break;
	}
	//cout << "Location: (" << x << "," << y << "), Status: " << status << endl;
	if (schonmalda)
		return -1;
	else
		return status;
}

bool oxygen_found=false;

void explore(int from=0, bool return_on_oxygen_found=true); // forward declaration needed for recursion

void explore_dir(int from, bool return_on_oxygen_found, int direction, int counterdir) {
	int status;
	if (from != direction) {
		status = gehe(direction);
		if (status != 0) {
			if (status != -1) {
				step++;
				if (status == 2 && return_on_oxygen_found) { cout << "Kürzeste Distanz: " << step << " Schritte." << endl; oxygen_found = true; return; }
				explore(counterdir, return_on_oxygen_found);
				gehe(counterdir);
				step--;
			}
		}
	}
}

void explore(int from, bool return_on_oxygen_found) {
	explore_dir(from, return_on_oxygen_found, NORTH, SOUTH);
	if (oxygen_found && return_on_oxygen_found) return;
	explore_dir(from, return_on_oxygen_found, EAST, WEST);
	if (oxygen_found && return_on_oxygen_found) return;
	explore_dir(from, return_on_oxygen_found, SOUTH, NORTH);
	if (oxygen_found && return_on_oxygen_found) return;
	explore_dir(from, return_on_oxygen_found, WEST, EAST);
	if (oxygen_found && return_on_oxygen_found) return;
}

void checkOx(long x, long y) {
	if (lm->getType(x,y) == VACUUM) {
		lm->setType(x,y, OXYGEN);
	}
}


int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Bitte Dateinamen als Argument angeben!\n");
		return -1;
	}
	//intcomp *c;
	c = new intcomp(argv[1]);

	int counter = 0;
	

	
	lm = new locationmap();
	long status;

	step = 0;
	explore();
	c->reset_program();
	delete lm;
	lm = new locationmap();
	counter=0;
	step=0;
	
	explore(0, false);
	
	oxygen = new locationmap();
	int vacount;
	cout << "Berechne Zeit bis zum vollständigen Fluten mit Sauerstoff... " << endl;
	while (vacount = lm->count_vacuum_positions()){
		counter++;
		// es sind noch Vakuumbereiche vorhanden
		// Die Bereiche, in denen schon Sauerstoff ist, wurden in der Schleifenbedingung auch gleich mitgezählt
		for (list<location>::iterator it = oxygen->locationlist->begin(); it!=oxygen->locationlist->end(); ++it) {
			int x = it->x;
			int y = it->y;
			//cout << "(" << x << "," << y << ")" << endl;
			//cout << "(" << x << "," << y << ")" << endl;
			// check (x+1,y)
			checkOx(x+1,y);
			// check (x-1,y)
			checkOx(x-1,y);
			// check (x,y+1)
			checkOx(x,y+1);
			// check (x,y-1)
			checkOx(x,y-1);
			
		}
		//cout << "OX: " << oxygen->locationlist->size() << ", VAC: " << vacount << endl;;
	}
	cout << "Anzahl Minuten: " << counter << endl;
	
	/*
	
	cout << "Minimum X: " << lm->find_min_x() << endl;
	cout << "Maximum X: " << lm->find_max_x() << endl;
	cout << "Minimum Y: " << lm->find_min_y() << endl;
	cout << "Maximum Y: " << lm->find_max_y() << endl;
	
	for (int yy = lm->find_min_y(); yy < lm->find_max_y(); yy++) {
		for (int xx = lm->find_min_x(); xx < lm->find_max_x(); xx++) {
			char c = (char)lm->find(xx,yy);
			if (c == -1) c=' ';
			if (c == '.') c=' ';
			printf("%c", c);
		}
		printf("\n");
	}
	*/
	//printf ("Return code: %d\n", ret);
	delete lm;
}
