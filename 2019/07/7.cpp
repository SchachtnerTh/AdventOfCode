#include "intcomp.h"
#include <stdio.h>
#include <limits.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

bool first_loop = true;
bool continue_loop = true;
int retvals[5] = {0,0,0,0,0};
char phase[5] = {9,8,7,6,5};
intcomp *amp[5];
int maxthrust = 0;

vector<string> permutations;

void permute(string a, int l, int r)  
{  
    // Base case  
    if (l == r)  {
        //cout<<a<<endl;;
	permutations.push_back(a);
    }
    else
    {  
        // Permutations made  
        for (int i = l; i <= r; i++)  
        { 
            // Swapping done 
	    swap (a[l], a[i]);
  
            // Recursion called  
            permute(a, l+1, r);  
  
            //backtrack  
	    swap (a[l], a[i]);
        }  
    }  
}  

void calc_amp(int pos, char* phases) {
	if (first_loop) {
		if (DEBUG) printf("!!\n");
		amp[pos]->get_input(phases[pos] - '0');
		if (DEBUG) printf("** Input in Amp %d: %d\n", pos, phases[pos] - '0');
		amp[pos]->execute_program(0);
	}
	if (first_loop && pos == 0) {
		amp[pos]->get_input(0);
		if (DEBUG) printf("!!\n");
		if (DEBUG) printf("** Input in amp 0: 0\n");
	} else {
		int index;
		if (pos == 0) index = 4; else index = pos - 1;
		amp[pos]->get_input(retvals[index]);
		if (DEBUG) printf("** Input in Amp %d: %d, %d\n", pos, retvals[index], index);
	}
	if (amp[pos]->execute_program(0) != -2) {
		if (pos == 4) continue_loop = false;
		if (DEBUG) printf ("A is 0\n");
		if (pos == 4) {
			int th = amp[pos]->get_output();
			printf("Thrusters: %d\n", th);
			if (th > maxthrust) maxthrust = th;
		}
	}
	if (DEBUG) printf ("** Output amp %d: %d\n", pos, amp[pos]->get_output());
	retvals[pos] = amp[pos]->get_output();
	if (DEBUG) printf ("retvals: {%d,%d,%d,%d,%d}\n", retvals[0], retvals[1], retvals[2], retvals[3], retvals[4]);
	if (DEBUG) printf ("---------------\n");
}

int main (int argc, char **argv) {
	int inputZahl;

	string str = "56789";
	int n = str.size();
	permute(str, 0, n-1);
	int amplifier;
		
	for (string z : permutations) {
		printf("%s\t", &z[0]);
		amp[0] = new intcomp(argv[1]);
		amp[1] = new intcomp(argv[1]);
		amp[2] = new intcomp(argv[1]);
		amp[3] = new intcomp(argv[1]);
		amp[4] = new intcomp(argv[1]);
		amplifier=0;
	
		while (continue_loop) {
			calc_amp(amplifier, &z[0]);
			if (amplifier == 4) first_loop = false;
			amplifier = (amplifier + 1) % 5;
		}

		amplifier = 0;
		first_loop = true;
		continue_loop = true;
		retvals[0] = retvals[1] = retvals[2] = retvals[3] = retvals[4] = 0;
		for (int i = 0; i < 5; delete amp[i++]);
	}
	printf ("Max Thrust: %d\n", maxthrust);


}
