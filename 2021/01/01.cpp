#include <iostream>
#include <cstdio>

using namespace std;
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " <input file name>" << endl;
		return -1;
	}
	FILE *f;
	f = fopen(argv[1], "r");
	
	int previous = 0;
	int now;
	int readcount;
	int deeper = 0;
	
	while (readcount = fscanf(f, "%d", &now) != EOF)
	{
		if (previous != 0)
		{
			if (previous < now) {
				deeper++;
			}
		}
		previous =  now;
	}
	cout << "Count deeper (simple): " << deeper << endl;
	fclose (f);
	
	f = fopen(argv[1], "r");
	
	int m1 = 0;
	int m2 = 0;
	int m3 = 0;
	previous = 0;
	deeper = 0;
	now = 0;
	
	while (readcount = fscanf(f, "%d", &now) != EOF)
	{
		m3 = m2;
		m2 = m1;
		m1 = now;
		if (m1 != 0 && m2 != 0 && m3 != 0)
		{
			if (previous != 0 && m1 != 0 && m2 != 0 && m3 != 0)
			{
				if (previous < m1 + m2 + m3) {
					deeper++;
				}
			}
			previous =  m1 + m2 + m3;
		}
	}
	cout << "Count deeper (3-sliding window): " << deeper << endl;
	fclose (f);
	
}