#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
int main(int argc, char **argv)
{
	int xpos = 0;
	int ypos = 0;
	int count;
	char direction[20];
	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " <input file name>" << endl;
		return -1;
	}
	FILE *f;
	f = fopen(argv[1], "r");
	
	int readcount;
	
	while (readcount = fscanf(f, "%s %d", direction, &count) != EOF)
	{
		cout << "Direction: " << direction << ", steps: " << count << endl;
		if (!strcmp(direction, "forward")) { xpos += count; }
		if (!strcmp(direction, "down")) { ypos += count; }
		if (!strcmp(direction, "up")) { ypos -= count; }
	}
	
	cout << "Horiz: " << xpos << ", Vert: " << ypos << ", Code: " << xpos * ypos << endl;
	
	fclose (f);
	
	xpos = 0;
	ypos = 0;
	int aim = 0;

	f = fopen(argv[1], "r");
	
	readcount;
	
	while (readcount = fscanf(f, "%s %d", direction, &count) != EOF)
	{
		cout << "Direction: " << direction << ", steps: " << count << endl;
		if (!strcmp(direction, "forward")) { xpos += count; ypos += count * aim;}
		if (!strcmp(direction, "down")) { aim += count; }
		if (!strcmp(direction, "up")) { aim -= count; }
	}
	
	cout << "Horiz: " << xpos << ", Vert: " << ypos << ", Code: " << xpos * ypos << endl;
	
	fclose (f);

	
}