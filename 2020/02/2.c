#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CHARS 1000	// Zwar nicht elegant, aber quick & dirty

int countChar(char c, char *str) {
	int pos = 0;
	int charcounter = 0;
	while (*(str + pos) != 0) {
		if (*(str + pos++) == c) charcounter++;
	}
	return charcounter;
}

int main (int argc, char **argv) {
	FILE *f;
	int min_num, max_num;
	int oks, ngs, oks2, ngs2;
	char c;
	char *pwd;
	
	oks = ngs = ngs2 = oks2 = 0;
	pwd = malloc(NUM_CHARS * sizeof(char));
	if (argc < 2) {
		printf("Usage: %s <input file>\n", argv[0]);
		return -1;
	}
	f = fopen(argv[1], "r");
	while (!feof(f)) {
		fscanf(f, "%d-%d %c: %s\n", &min_num, &max_num, &c, pwd);
		if (!strlen(pwd) == 0) {
			int chars = countChar(c, pwd);
			if (chars <= max_num && chars >= min_num) 
				oks++;
			else 
				ngs++;
			if (pwd[min_num - 1] == c && pwd[max_num - 1] != c) || (pwd[min_num - 1] != c && pwd[max_num - 1] == c)) 
				oks2 ++;
			else
				ngs2++;
		}
	}
	printf ("\n");
	printf ("Anzahl an korrekten Passwörtern: %d\nAnzahl an nicht korrekten Passwörtern: %d\n", oks,ngs);
	printf ("Anzahl an korrekten Passwörtern neuer Standard: %d\nAnzahl an nicht korrekten Passwörtern neue Password policy : %d\n", oks2,ngs2);
	fclose(f);
	free(pwd);
}