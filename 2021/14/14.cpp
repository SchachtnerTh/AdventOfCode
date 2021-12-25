#include <iostream>
#include <map>
#include <cstring>
#include <list>

using namespace std;

map<string,char> rules;
map<char,int> histogram;
list<char> elements;

char *polymer;

void polymerize()
{
	string replacement;
	
	int curlen = strlen(polymer) + 1; // including trailing \0
	int newlen = 2 * curlen - 2;
	
	char *newstr = new char[newlen];
	newstr[newlen - 1] = 0;
	
	char *oldptr, *newptr;
	oldptr = polymer;
	newptr = newstr;
	
	while (oldptr != (polymer + curlen - 2))
	{
		*newptr++ = *oldptr;
		replacement.clear();
		replacement.push_back(*oldptr);
		replacement.push_back(*(oldptr + 1));
		map<string,char>::iterator it = rules.find(replacement);
		*newptr++ = it->second;
		oldptr++;
	}
	*newptr = *oldptr;
	
	delete polymer;
	polymer = new char[newlen];
	strcpy(polymer, newstr);
	delete newstr;
}

int main(int argc, char **argv)
{
	FILE *f;
	f = fopen(argv[1], "r");
	char *str, *s1, *s2, *s3;
	fscanf(f, "%ms", &polymer);
	while (fscanf(f, "%ms %ms %ms", &s1, &s2, &s3) != EOF)
	{
		cout << "Line " << s1 << " " << s2  << " " << s3 << " "  << endl;
		rules.insert(pair<string,char>((string)s1, *s3));
	}
	
	for (map<string,char>::iterator it = rules.begin(); it != rules.end(); ++it)
	{
		cout << "Key: " << it->first << ", Value: " << it-> second << endl;
		bool found = false;
		for (char c : elements)
		{
			if (c == (it->first)[0]) found = true;
		}
		if (!found) elements.push_back((it->first)[0]);
		found = false;
		for (char c : elements)
		{
			if (c == (it->first)[1]) found = true;
		}
		if (!found) elements.push_back((it->first)[1]);
		found = false;
		for (char c : elements)
		{
			if (c == it->second) found = true;
		}
		if (!found) elements.push_back(it->second);
	}
	int maxcount = 0;
	int mincount = 0;
	
	for (int i = 0; i < 10; i++)
	{
		polymerize();
		 maxcount = 0;
		 mincount = 0;
		
		for (char elem : elements)
		{
			int l = strlen(polymer);
			int count = 0;
			for (int i = 0; i < l; i++)
			{
				if(polymer[i] == elem) count++;
			}
			if (count > maxcount || maxcount == 0) maxcount = count;
			if (count < mincount || mincount == 0) mincount = count;
		}
		cout << "Maxcount: " << maxcount << endl;
		cout << "Mincount: " << mincount << endl;
		cout << "Result 1: " << maxcount - mincount << endl << endl;;

	}
	return 0;

	
	for (char elem : elements)
	{
		int l = strlen(polymer);
		int count = 0;
		for (int i = 0; i < l; i++)
		{
			if(polymer[i] == elem) count++;
		}
		if (count > maxcount || maxcount == 0) maxcount = count;
		if (count < mincount || mincount == 0) mincount = count;
	}
	
	cout << "Maxcount: " << maxcount << endl;
	cout << "Mincount: " << mincount << endl;
	cout << "Result 1: " << maxcount - mincount << endl;
	
	for (int i = 0; i < 30; i++)
	{
		cout << "Round " << i << endl;
		polymerize();
	}
	
	cout << "polymerization done" << endl;

	 maxcount = 0;
	 mincount = 0;
	
	for (char elem : elements)
	{
		int l = strlen(polymer);
		int count = 0;
		for (int i = 0; i < l; i++)
		{
			if(polymer[i] == elem) count++;
		}
		if (count > maxcount || maxcount == 0) maxcount = count;
		if (count < mincount || mincount == 0) mincount = count;
	}

	//cout << polymer << endl;
	
	fclose(f);
}