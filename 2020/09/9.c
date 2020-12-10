#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 1000
#define PREAMBLE 25

long zahlen[LENGTH];
long ziel_zahl;

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Bitte Dateinamen als Argument angeben!\n");
		return -1;
	}
	FILE *f;
	
	f = fopen(argv[1], "r");
	
	int i=0;

	while (!feof(f)) {
		fscanf(f, "%ld", &zahlen[i++]);
	}
	fclose(f);
	
	// for (int i = 0; i < LENGTH; printf("%ld\t", zahlen[i++]));
	
	for (int zahl = PREAMBLE; zahl < LENGTH; zahl++) {
		int found = 0;
		for (int anfang = zahl - PREAMBLE; anfang < zahl - 1; anfang++) {
			for (int zweiteZahl = anfang + 1; zweiteZahl < zahl; zweiteZahl++) {
				if (zahlen[anfang] + zahlen[zweiteZahl] == zahlen[zahl]) found = 1;
			}
		}
		if (found == 0) {
			printf ("Zahl Nr. %d (%ld) ist falsch.\n", zahl, zahlen[zahl]);
			ziel_zahl = zahlen[zahl];
			break;
		}
	}
	printf("Jetzt gehts weiter mit der Zahl %ld.\n", ziel_zahl);
	
	long summe;
	for (int anfang = 0; anfang < LENGTH - 1; anfang++) {
		summe = zahlen[anfang];
		long smallest = summe;
		long largest = summe;
		for (int cumulate = anfang + 1; cumulate < LENGTH; cumulate++) {
			summe += zahlen[cumulate];
			if (zahlen[cumulate] < smallest) smallest = zahlen[cumulate];
			if (zahlen[cumulate] > largest) largest = zahlen[cumulate];
			if (summe == ziel_zahl) {
				printf("Ziel erreicht: Anfang: %d, Ende: %d, Summe: %ld, Ziel: %ld, niedrigste Zahl: %ld, höchste Zahl: %ld, Summe beider Zahlen: %ld\n", anfang, cumulate, summe, ziel_zahl, smallest, largest, smallest + largest);
				return -1;
			}
			if (summe > ziel_zahl) break;
		}
	}
}