#include <stdio.h>
#include <math.h>
#define NUMBASE 4

char *pattern;
int length;
char base_pattern[NUMBASE];

char *signal;
char *result;
int signal_length;

void generate_pattern(int position)
{
	if (pattern != NULL) 
	{
		delete pattern;
		pattern = NULL;
	}
	length = NUMBASE * (position + 1);
	pattern = new char[length];
	for (int i = 0; i < NUMBASE; i++) {
		for (int j = 0; j < position + 1; j++) {
			pattern[i * (position + 1) + j] = base_pattern[i];
		}
	}
/*	printf ("Position: %d, Pattern: ", position);
	for (int i = 0; i < length; printf("%d ", pattern[i++]));
	printf ("\n");*/
}

int get_next_pattern_element(bool reset)
{
	int retval;
	static int position;
	if (reset) 
		position = 1;
	return pattern[position++ % length];
}

void print_pattern_multiple(int count)
{
	for (int i = 0; i < count; i++) {
		int z;
		if (i == 0)
			z = get_next_pattern_element(true);
		else
			z = get_next_pattern_element(false);
		printf ("%2d ", z);
	}
	printf("\n\n");
}

void fft_round()
{
	printf(".");
	for (int i = 0; i < signal_length; i++)
	{
		generate_pattern(i);
		int sum=0;
		for (int j = 0; j < signal_length; j++)
		{
			sum += signal[j] * get_next_pattern_element(j == 0 ? true : false);
		}
		result[i] = abs(sum % 10); // ensures positive results
	}
	/*
	printf ("Ausgangssignal: ");
	for (int i = 0; i < signal_length; printf("%d", signal[i++]));
	printf (", Ergebnis: ");
	for (int i = 0; i < signal_length; printf("%d", result[i++]));
	printf ("\n");
	*/
	for (int i = 0; i < signal_length; signal[i++] = result[i]);

	/*
	printf ("Ausgangssignal: ");
	for (int i = 0; i < signal_length; printf("%d", signal[i++]));
	printf (", Ergebnis: ");
	for (int i = 0; i < signal_length; printf("%d", result[i++]));
	printf ("\n");
	*/
}

void multiply_signal(int count)
{
	signal = (char *)realloc(signal, signal_length * count);
	for (int i = 1; i < count; i++)
	{
		for (int j = 0; j < signal_length; j++)
		{
			signal[i * signal_length + j] = signal[j];
		}
	}
	signal_length *= count;
	/*printf ("Ausgangssignal: ");
	for (int i = 0; i < signal_length; printf("%d", signal[i++]));
	printf ("\n");
	printf("Das neue Signal ist %d Zahlen lang.\n", signal_length);*/
}


int main(int argc, char **argv)
{
	FILE *f;
	f = fopen(argv[1], "r");
	while (!feof(f)) {
		char c = fgetc(f);
		if (c >= '0' && c <= '9')
		{
			signal_length++;
			signal = (char *)realloc(signal, signal_length);
			signal[signal_length - 1] = c - '0';
		}
		
		printf ("%0X ", signal[signal_length - 1]);
	}
	printf("\n");
	printf("Signal ist %d Zahlen lang.\n", signal_length);
	
	//multiply_signal(10000);
	// return 0;
	base_pattern[0] = 0;
	base_pattern[1] = 1;
	base_pattern[2] = 0;
	base_pattern[3] = -1;
/*
	signal_length = 32;	
	signal = new char[signal_length];
	//80871224585914546619083218645595
	signal[0] = 8;
	signal[1] = 0;
	signal[2] = 8;
	signal[3] = 7;
	signal[4] = 1;
	signal[5] = 2;
	signal[6] = 2;
	signal[7] = 4;
	signal[8] = 5;
	signal[9] = 8;
	signal[10] = 5;
	signal[11] = 9;
	signal[12] = 1;
	signal[13] = 4;
	signal[14] = 5;
	signal[15] = 4;
	signal[16] = 6;
	signal[17] = 6,
	signal[18] = 1;
	signal[19] = 9;
	signal[20] = 0;
	signal[21] = 8;
	signal[22] = 3;
	signal[23] = 2;
	signal[24] = 1;
	signal[25] = 8;
	signal[26] = 6;
	signal[27] = 4;
	signal[28] = 5;
	signal[29] = 5;
	signal[30] = 9;
	signal[31] = 5;
*/
	printf ("Ausgangssignal: ");
	for (int i = 0; i < signal_length; printf("%d", signal[i++]));
	printf ("\n");
	
	
	result = new char[signal_length];
	for (int rounds = 0; rounds < 100; rounds++)
	{
		fft_round();
	}
	
	printf ("Ergebnis: ");
	for (int i = 0; i < signal_length; printf("%d", result[i++]));
	printf ("\n");
		
	/* generate_pattern(0);
	print_pattern_multiple(20);
	
	generate_pattern(1);
	print_pattern_multiple(20);
	generate_pattern(2);
	print_pattern_multiple(20);
	generate_pattern(3);
	print_pattern_multiple(20);
	generate_pattern(4);
	print_pattern_multiple(20);
	generate_pattern(5);
	print_pattern_multiple(20);
	generate_pattern(6);
	print_pattern_multiple(20);*/
}