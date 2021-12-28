#include <iostream>
#include <map>
#include <cstring>
#include <list>

#define ROUNDS 40
#define PRECOMPUTE_ROUNDS 22

using namespace std;

map<string,char> rules;
map<char,unsigned long> histogram;
list<char> elements;
map<string,string> after15strings;
map<string, map<char,unsigned long>> after15histogram;

char *polymer, *orig;

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

void build_histogram()
{
	histogram.clear();
	for (char elem : elements)
	{
		unsigned long l = strlen(polymer);
		unsigned long count = 0;
		for (unsigned long i = 0; i < l; i++)
		{
			if(polymer[i] == elem) count++;
		}
		if (polymer[0] == elem) count--; // subtract count by one for the leading element
		histogram.insert(pair<char,unsigned long>(elem, count));
		//if (count > maxcount || maxcount == 0) maxcount = count;
		//if (count < mincount || mincount == 0) mincount = count;
	}	
}

int main(int argc, char **argv)
{
	FILE *f;
	f = fopen(argv[1], "r");
	char *str, *s1, *s2, *s3;
	
	// read polymer template
	fscanf(f, "%ms", &orig);
	
	// read polimerization rules
	while (fscanf(f, "%ms %ms %ms", &s1, &s2, &s3) != EOF)
	{
		cout << "Line " << s1 << " " << s2  << " " << s3 << " "  << endl;
		rules.insert(pair<string,char>((string)s1, *s3));
	}
	
	// initialize elements histogram
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
	unsigned long maxcount = 0;
	unsigned long mincount = 0;
	
	polymer = new char[strlen(orig) + 1];
	strcpy(polymer, orig);
	
	for (int i = 0; i < 10; i++)
	{
		polymerize();
		 maxcount = 0;
		 mincount = 0;
		
		// Count occurrance of each element
		for (char elem : elements)
		{
			unsigned long l = strlen(polymer);
			unsigned long count = 0;
			for (unsigned long i = 0; i < l; i++)
			{
				if(polymer[i] == elem) count++;
			}
			if (count > maxcount || maxcount == 0) maxcount = count;
			if (count < mincount || mincount == 0) mincount = count;
		}
	}
	
	for (char elem : elements)
	{
		unsigned long l = strlen(polymer);
		unsigned long count = 0;
		for (unsigned long i = 0; i < l; i++)
		{
			if(polymer[i] == elem) count++;
		}
		if (count > maxcount || maxcount == 0) maxcount = count;
		if (count < mincount || mincount == 0) mincount = count;
	}
	
	cout << "Maxcount: " << maxcount << endl;
	cout << "Mincount: " << mincount << endl;
	cout << "Result 1: " << maxcount - mincount << endl;
	
	int e=0;
	// Precompute all 2-combinations from the rules list after PRECOMPUTE_ROUNDS rounds
	for (map<string,char>::iterator it = rules.begin(); it != rules.end(); ++it)
	{
		cout << it->first << ": ";
		strcpy(polymer, it->first.c_str());
		for (unsigned long i = 0; i < PRECOMPUTE_ROUNDS; i++)
		{
			//cout << "Round " << i << endl;
			polymerize();
			
		}
		after15strings.insert(pair<string,string>(it->first, string(polymer)));
		build_histogram();
		after15histogram.insert(pair<string, map<char, unsigned long>>(it->first, histogram));
		// Zählen und Befüllen des jeweiligen Histogramms
		cout << "Combination " << ++e << ", Polymer length: " << strlen(polymer) << endl;
	}
	
	cout << "Remaining rounds: " << ROUNDS-PRECOMPUTE_ROUNDS << endl;
	strcpy(polymer, orig);
	for (int i = 0; i < ROUNDS - PRECOMPUTE_ROUNDS; i++)
	{
		polymerize();
	}
	histogram.clear();
	
	for (unsigned long i = 0; i < strlen(polymer) - 1; i++)
	{
		if (i % 10000 == 0)
			cout << i << " of " << strlen(polymer) - 1 << endl;
		char e_pair[3];
		strncpy(e_pair, polymer + i, 2);
		//cout << "Counting for " << pair << "." << endl;
		for (char elem : elements)
		{
			if (histogram.find(elem) == histogram.end())
			{
				unsigned long c = after15histogram.at(string(e_pair)).at(elem);
				histogram.insert(pair<char,unsigned long>(elem, c));
				//histogram.insert(pair<char,unsigned long>('A', 100));
			}
			else
			{
				histogram.at(elem) += after15histogram.at(string(e_pair)).at(elem);
			}
			//if (histogram.at(elem) )
		}
	}
	cout << "Intermediate polymer length: " << strlen(polymer) << endl;
	
	maxcount = 0;
	mincount = 0;
	for (char elem : elements)
	{
		unsigned long cnt = histogram.at(elem);
		if (maxcount == 0 || maxcount < cnt) maxcount = cnt;
		if (mincount == 0 || mincount > cnt) mincount = cnt;
	}
	cout << "Das häufigste Element kommt " << maxcount << " Mal vor, das seltenste " << mincount << " Mal. Die Lösung lautet " << maxcount - mincount;
	
	//cout << polymer << endl;
	delete orig;
	fclose(f);
}