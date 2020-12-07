#include <stdio.h>

char liste[1024];

int main(int argc, char **argv) {
	if (argc < 2) printf("Bitte Dateiname noch mit angeben.\n");
	FILE *f = fopen(argv[1], "r");
	char sitzplatz[11];
	int highest=0;
	for (int i = 0; i < 1024; liste[i++] = 0);
	while (!feof(f)) {
		fscanf(f, "%s\n", sitzplatz);
		printf("Platz: %s\n", sitzplatz);
		int reihe=0;
		int platz=0;
		for (int i = 0; i < 7; i++) {
			reihe <<= 1;
			reihe += (sitzplatz[i] == 'B' ? 1 : 0);
			if (i < 3) {
				platz <<= 1;
				platz += (sitzplatz[i+7] == 'R' ? 1 : 0);
			}
		}
		int code = reihe * 8 + platz;
		liste[code] = 1;
		printf ("Reihe: %d, Platz: %d, Code: %d\n", reihe, platz, code);
		if (code > highest) highest = code;
	}
	printf ("Höchster Code: %d\n", highest);
	for (int i = 0; i < 1024; i++) {
		if (!liste[i] && ((i & 1016) != 1016) && ((i & 1016) != 0)) {
			if ((i > 0) && (i < 1023) && liste [i-1] && liste[i+1]) printf("%d\t", i);
		}
	}
	fclose(f);
}
