#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 1000
#define PREAMBLE 25

int *zahlen;
int anz_zahlen;
long ziel_zahl;

void print() {
	for (int i = 0; i < anz_zahlen; i++) {
		printf("Zahl %2d: %2d\n", i, *(zahlen + i));
	}
}

void swap (int *a, int *b) {
	int h;
	h = *a;
	*a = *b;
	*b = h;
}

void sort() {	// Bubble Sort
	int complete = 0;
	int h;
	while (complete == 0) {
		complete = 1;
		for (int i = 0; i < anz_zahlen - 1; i++) {
			if (zahlen[i] > zahlen[i + 1]) {
				complete = 0;
				swap(zahlen + i, zahlen + i + 1);
			}
		}
	}
}

void calculate_13_diffs() {
	int diff1 = 0;
	int diff3 = 0;
	
	for (int i = 0; i < anz_zahlen - 1; i++) {
		switch (zahlen[i + 1] - zahlen[i]) {
			case 1: diff1++; break;
			case 3: diff3++; break;
		}
	}
	printf("Die gesuchte Zahl ist %d\n", diff3 * diff1);
}

long combination = 0;

void find_ways(int start_index) {
	for (int i = start_index + 1; i < anz_zahlen; i++)
	{
		if (zahlen[i] - zahlen[start_index] <= 3) {
			//if (start_index != 0) printf(" -> ");
			//printf("%d", zahlen[i]);
			if (i == anz_zahlen - 1) {
				combination++;
				if ((combination % 1000000000) == 0) printf("combination: %ld\n", combination);
			//	printf("\n");
			}
			find_ways(i);
		}
		if (i == anz_zahlen - 1) {
			return;
		}
	}
	
}

long findways2() {
	short abstaende[anz_zahlen];
	short kombis[anz_zahlen];
	long alleKombis[anz_zahlen];
	for (int i = 0; i < anz_zahlen; i++) {
		alleKombis[i]=0;
		if (i == 0) 
			abstaende[i] = 0;
		else {
			abstaende[i] = zahlen[i] - zahlen[i-1];
		}
		
	}
	for (int i = 1; i < anz_zahlen; i++) {
		kombis[i] = 1;
		if (i + 1 < anz_zahlen) if (abstaende[i] + abstaende[i + 1] < 4) { kombis[i]++; }
		if (i + 2 < anz_zahlen) if (abstaende[i] + abstaende[i + 1] + abstaende[i + 2] < 4) { kombis[i]++; }
	}
	
	alleKombis[anz_zahlen - 1] = 1;
	for (int i = anz_zahlen - 2; i > 0; i--) {
		if (kombis[i] >= 1) alleKombis[i] = alleKombis[i + 1];
		if (kombis[i] >= 2 && ((i + 2) < anz_zahlen)) alleKombis[i] += alleKombis[i + 2];
		if ((kombis[i] == 3) && ((i + 3) < anz_zahlen)) alleKombis[i] += alleKombis[i + 3];
	}
	return alleKombis[1];
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Bitte Dateinamen als Argument angeben!\n");
		return -1;
	}
	zahlen = NULL;
	anz_zahlen = 0;
	FILE *f;
	
	f = fopen(argv[1], "r");

	while (!feof(f)) {
		int z = 0;
		fscanf(f, "%d", &z);
		if (z != 0) {
			anz_zahlen++;
			zahlen = (int *) realloc(zahlen, anz_zahlen * sizeof(int));
			zahlen[anz_zahlen - 1] = z;
		}
	}
	
	int max=0;
	for (int i = 0; i < anz_zahlen; i++) {
		if (zahlen[i] > max) max = zahlen[i];
	}
	anz_zahlen += 2;
	zahlen = (int *) realloc(zahlen, anz_zahlen * sizeof(int));
	zahlen[anz_zahlen - 2] = 0;
	zahlen[anz_zahlen - 1] = max + 3;
	
	fclose(f);
	
//	print();
	sort();
//	print();
	calculate_13_diffs();
//	find_ways(0); // Brute Force
	printf("Anzahl an möglichen Kombinationen: %ld\n", findways2());
}