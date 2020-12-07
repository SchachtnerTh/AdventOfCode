#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passport.h"

size_t length=0;
char *line=NULL;
bool firstpart = true;
int bytes_read;
int valid = 0, valid2 = 0;

passport *pass;

int main(int argc, char **argv) {
	char passport_data[1000]; // nicht schön, aber läuft und sollte reichen
	if (argc < 2) {
		printf ("Bitte Reisepassdaten angeben.\n");
		return -1;
	}
	FILE *f = fopen(argv[1], "r");
	while (true) {
		bytes_read=getline(&line, &length, f);
		if (strcmp(line, "\n") && !feof(f)) {
			if (line[bytes_read-1] == 10) {
				line[bytes_read-1] = 0;
				strcat(line, " ");
			}
			if (firstpart) {
				strcpy(passport_data, line);
				firstpart = false;
			} else {
				strcat(passport_data, line);
				//strcat(passport_data, " ");
			}
		} else {
//			printf("%s", passport_data);
//			printf("Passport data: [%s]  ", passport_data);
			char tmp[1000];
			strcpy(tmp, passport_data);
			// tmp = passport_data;
			pass = new passport(passport_data);
			//pass->print_data();
			if (pass->is_valid()) {
				valid++;
//				printf("V ");
			} else printf ("  ");
			if (pass->is_valid2()) {
				valid2++;
				printf("%s\n", tmp);
//				printf("V ");
			} else printf ("  ");
//			printf("\n");
			delete pass;
			firstpart = true;
		}
		if (feof(f)) break;
	}
	fclose(f);
	free(line);
	printf ("Gültige Pässe: %d\n", valid);
	printf ("Gültige Pässe: %d\n", valid2);
}
