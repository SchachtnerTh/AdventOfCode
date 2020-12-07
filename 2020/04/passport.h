#ifndef PASSPORT_H
#define PASSPORT_H

class passport {
	private:
	int byr;
	int iyr;
	int eyr;
	char* hgt;
	char *hcl;
	char *ecl;
	char* pid;
	int cid;
	
	char *marker1, marker2;
	int valid;
	
	void parse_element(char *inputline);
	bool heightcheck();
	bool colorcheck();
	bool eclcheck();
	bool pidcheck();
	

	public:
	passport(char *inputline);
	~passport();
	void add_info(char *inputline);
	bool is_valid();
	bool is_valid2();
	void print_data();
	
};

#endif