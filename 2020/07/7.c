#include <stdio.h>
#include <string.h>
#include <stdlib.h>



char needle[1000];
int count = 0;
char filename[1000];

char *farben[1000];

void find_farbe(char * farbe, int depth) {
	char *c0;
	char *c1;
	char *line;
	c0 = malloc(20 * sizeof(char));
	c1 = malloc(20 * sizeof(char));
	line = malloc(1000 * sizeof(char));
	int n1,n2,n3,n4,n5;
	char e1,e2,e3,e4,e5;
	FILE *f;
	f = fopen(filename, "r");
	if (!f) printf ("FEHLER!\n");
	//printf ("newinst\n");
	int schonmal = 0;
	while (!feof(f)) {
		fgets(line, 1000, f);
		char *tmp, *tmp2;
		tmp = strstr(line, "bags contain");
		strncpy(c0, line, tmp-line - 1); // Aussentasche
		c0[tmp-line-1] = 0;
		tmp += 13;
		do {
			char *space, *aftercolor;
			tmp2 = strstr(tmp, ",");
			n1 = atoi(tmp);
			space = strstr(tmp+1, " ");
			aftercolor = strstr(space, "bag");
			strncpy (c1, space + 1, aftercolor-space - 2);
			c1[aftercolor-space - 2]=0;
			// printf("%d: (%ld, %ld) Aussenfarbe [%s]: [%d] mal [%s]\t", count, strlen(c0), strlen(c1), c0, n1, c1);
			if (!strcmp(c1, farbe)) {
					int maxcolor=0;
					int schonmalgehabt = 0;
					//printf ("Treffer! Außen: %s\n", c0);
					for (int i = 0; i < 1000; i++) {
						if (farben[i] == 0) {
							maxcolor = i;
							break;
						}
						if (!strcmp(c0, farben[i])) {
							schonmalgehabt = 1;
							//printf ("schon mal gehabt\n");
						}
					}
					if (!schonmalgehabt) {
						count++;
						//printf("%s wird gezählt.\n", c0);
						farben[maxcolor] = malloc(strlen(c0) + 2);
						strcpy (farben[maxcolor], c0);
					}
					//printf ("Call find_farbe(%s)\n", c0);
					find_farbe(c0, depth + 1);
				schonmal = 1;
			} else {
				//printf("\n");
			}
			if (tmp2) tmp = tmp2+1;
		} while (tmp2);
	}
	free (c1);
	free (c0);
	free (line);
	fclose(f);
}
int count_subbags(char * farbe) {
	int taschen=0;
	char *c0;
	char *c1;
	char *line;
	c0 = malloc(20 * sizeof(char));
	c1 = malloc(20 * sizeof(char));
	line = malloc(1000 * sizeof(char));
	int n1,n2,n3,n4,n5;
	char e1,e2,e3,e4,e5;
	FILE *f;
	f = fopen(filename, "r");
	if (!f) printf ("FEHLER!\n");
	int schonmal = 0;
	int found = 0;
	while (!feof(f)) {
		fgets(line, 1000, f);
		char *tmp, *tmp2;
		tmp = strstr(line, "bags contain");
		strncpy(c0, line, tmp-line - 1); // Aussentasche
		c0[tmp-line-1] = 0;
		if (!strcmp(c0, farbe))
		{
			taschen++;
			found = 1;
			tmp += 13;
			do {
				char *space, *aftercolor;
				tmp2 = strstr(tmp, ",");
				n1 = atoi(tmp);
				space = strstr(tmp+1, " ");
				aftercolor = strstr(space, "bag");
				strncpy (c1, space + 1, aftercolor-space - 2);
				c1[aftercolor-space - 2]=0;
				//if (print) printf("A %s bag must contain %d %s bags\n", c0, n1, c1);
				//if (print) printf("A %s bag must contain %d * %d bags\n", c0, n1, count_subbags(c1));
				taschen += n1 * count_subbags(c1);
				if (n1 == 0) {
					//if (print) printf ("%s: nur eine Tasche.\n", c0);
					taschen = 1;
				}
				if (tmp2) tmp = tmp2+1;
			} while (tmp2);
		}
	}
	free (c1);
	free (c0);
	free (line);
	fclose(f);
	
	return taschen;
}

int main(int argc, char** argv) {
	if (argc < 3) {
		printf("Bitte Dateinamen und Farbe als Argument angeben!\n");
		return -1;
	}
	for (int i = 0; i < 1000; farben[i++] = 0);
	strcpy(filename, argv[1]);
	find_farbe(argv[2], 0);
	printf("Count: %d\n", count);
	printf ("Taschen: %d\n", count_subbags(argv[2]) - 1);
}