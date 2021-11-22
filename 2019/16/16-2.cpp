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
	printf("X");
	for (int i = 0; i < signal_length; i++)
	{
		if (i % 1000 == 0) { printf("."); fflush(NULL); }
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
	if (argc != 3) {
		printf ("Usage: %s <filename> <number of multiplications>\n", argv[0]);
	}
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
	int multiplications = atoi(argv[2]);
	printf("\n");
	printf("Signal ist %d Zahlen lang.\n", signal_length);
	fclose(f);
	
	multiply_signal(multiplications);
	// return 0;
	base_pattern[0] = 0;
	base_pattern[1] = 1;
	base_pattern[2] = 0;
	base_pattern[3] = -1;

/*	printf ("Ausgangssignal: ");
	for (int i = 0; i < signal_length; printf("%d", signal[i++]));
	printf ("\n");
	*/
	
	printf("Prepare output array.\n");
	result = new char[signal_length];
	printf("Starting FFT\n");
	for (int rounds = 0; rounds < 100; rounds++)
	{
		printf ("Round %d\n", rounds + 1);
		fft_round();
		FILE *f2;
		char filename[20];
		sprintf(filename, "round%0d.num", rounds);
		f2=fopen(filename, "w");
		for (int i = 0; i < signal_length; fputc(result[i++] + '0', f2));
		fclose(f2);
	}
	printf("FFT finished.");
	
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