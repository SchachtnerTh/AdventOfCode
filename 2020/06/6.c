#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Bitte Dateinamen als Argument angeben!\n");
		return -1;
	}
	FILE *f;
	char line[28];
	char question_answered[26];
	char numbytes;
	int gesamtcount=0;
	int people = 0;
	int gesamtcount2 = 0;
	
	f = fopen(argv[1], "r");
	for (int i = 0; i < 26; question_answered[i++] = 0);
	while (!feof(f)) {
		fgets(line, 30, f);
		numbytes = strlen(line);
		if (line[0] != 10 && line[0] != 13) {
			people++;
			for (int i = 0; i < strlen(line); i++) {
				if (line[i] >= 'a' && line[i] <= 'z') { 
					question_answered[line[i] - 'a']++;
				}
			}
		} else {
			int count = 0, count2=0;
			for (int i = 0; i < 26; i++) {
				if (question_answered[i] >= 1) count++;
				if (question_answered[i] == people && people != 0) count2++;
			}
			printf("People: %d, Count: %d\n", people, count);
			people = 0;
			for (int i = 0; i < 26; question_answered[i++] = 0);
			
			gesamtcount += count;
			gesamtcount2 += count2++;
		}
	}
	printf("Gesamtcount: %d\n", gesamtcount);
	printf("Gesamtcount2: %d\n", gesamtcount2);
}