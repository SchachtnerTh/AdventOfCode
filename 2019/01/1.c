#include<stdio.h>
#include<stdlib.h>

int fuel_needed(int mass) {
	int tmpFuel = mass / 3 - 2;
	if (tmpFuel > 0) {
		int tmpNewFuel = fuel_needed(tmpFuel);
		if (tmpNewFuel > 0) {
			tmpFuel += tmpNewFuel;
		}
	} else {
		tmpFuel = 0;
	}
	return tmpFuel;
}

int main(int argc, char **argv) {
	if (argc > 2) {
		printf("Invalid number of arguments (%d)!\n", argc);
		return -1;
	}
	int mass;
	size_t massStrSize;
	char *massStr;
	unsigned long fuel = 0;
	int count = 0;
	if (argc == 1) {
		massStrSize = 10;
		massStr = (char *)malloc(massStrSize);
		while (count = getline(&massStr, &massStrSize, stdin) != -1) {
			printf ("Z:%1d  ", count);
			mass = atoi(massStr);
			printf ("M:%5d  ", mass);
			int deltaFuel = fuel_needed(mass);
			fuel += deltaFuel;
			printf ("F:%5d\n", deltaFuel);
		}
		printf("Gesamt-Treibstoffmenge: %ld\n", fuel);
	} else {
		printf("Fuel needed: %d\n", atoi(argv[1]) / 3 - 2);
	}
}
