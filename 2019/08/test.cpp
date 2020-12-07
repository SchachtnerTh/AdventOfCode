#include <stdio.h>

int width = 25;
int height = 6;
int layers = 100;

int main (int argc, char **argv) {
	FILE *f;
	f=fopen(argv[1], "r");
	int nuller[layers];
	int einser[layers];
	int zweier[layers];
	int layer[width][height][layers];
	int ergebnis[width][height];
	for (int l = 0; l < layers; l++) {
		nuller[l]=0;
		einser[l]=0;
		zweier[l]=0;
		for (int h = 0; h < height; h++) {
			for (int w = 0; w < width; w++) {
				char c = fgetc(f);
				layer[w][h][l] = c;
				switch (c) {
					case '0': nuller[l]++; break;
					case '1': einser[l]++; break;
					case '2': zweier[l]++; break;
				}
			}
		}
	}
	int min_layer;
	int min_nuller = 0;
	for (int l = 0; l < layers; l++) {
		printf ("Layer %d: Nuller: %d\n", l, nuller[l]);
		if (min_nuller == 0 || nuller[l] < min_nuller) {
			min_nuller = nuller[l];
			min_layer = l;
		}
	}
	printf ("Ergebnis: Layer %d, Produkt aus %d und %d: %d\n", min_layer, einser[min_layer], zweier[min_layer], einser[min_layer] * zweier[min_layer]);
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			for (int l=0; l < layers; l++) {
				if (layer[w][h][l] != '2') {
					ergebnis[w][h] = layer[w][h][l];
					break;
				}
			}
		}
	}
	
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			if (ergebnis[w][h] == '1') printf("*");
			if (ergebnis[w][h] == '0') printf(" ");
			if (ergebnis[w][h] == '2') printf(".");
		}
		printf("\n");
	}
	fclose(f);
}