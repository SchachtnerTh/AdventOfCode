#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "passport.h"

passport::passport(char *inputline) {
	char *element;
	char *lastptr;
	
	byr = -1;
	iyr = -1;
	eyr = -1;
	hgt = NULL;
	hcl = NULL;
	ecl = NULL;
	pid = NULL;
	cid = -1;
	lastptr = inputline;
	int length=1;
	while (true) {
		element = strsep(&inputline, " "); 
		if (strlen(element) > 0)
			parse_element(element);
		else 
			return;
	}
}

void passport::parse_element(char *inputline) {
	char *key;
	char *value;
	int tmpint;
	char *tmpstr;
	
	tmpstr = strsep(&inputline,":");
	tmpint = strlen(tmpstr);
	key = new char[tmpint];
	strcpy(key, tmpstr);
	tmpstr = strsep(&inputline,":");
	tmpint = strlen(tmpstr);
	value = new char[tmpint];
	strcpy(value, tmpstr);
	
	// printf ("key: %s, value: %s\n", key, value);
	
	if (!strcmp(key, "byr")) { byr = atoi(value); }
	if (!strcmp(key, "iyr")) { iyr = atoi(value); }
	if (!strcmp(key, "eyr")) { eyr = atoi(value); }
	if (!strcmp(key, "hgt")) { 
		hgt = new char[strlen(value)];
		strcpy(hgt, value); 
	}
	if (!strcmp(key, "hcl")) { 
		hcl = new char[strlen(value)];
		strcpy(hcl, value);
	}
	if (!strcmp(key, "ecl")) { 
		ecl = new char[strlen(value)];
		strcpy(ecl, value); 
	}
	if (!strcmp(key, "pid")) { 
		pid = new char[strlen(value)];
		strcpy(pid, value);
	}
	if (!strcmp(key, "cid")) { cid = atoi(value); }
	delete key;
	delete value;
}

void passport::print_data() {
	printf("byr:%d\n",byr);
	printf("iyr:%d\n",iyr);
	printf("eyr:%d\n",eyr);
	printf("hgt:%s\n",hgt);
	printf("hcl:%s\n",hcl);
	printf("ecl:%s\n",ecl);
	printf("pid:%s\n",pid);
	printf("cid:%d\n",cid);
	printf("----------------\n");
}

passport::~passport(){
	delete hgt;
	delete hcl;
	delete ecl;
	delete pid;
}

bool passport::is_valid() {
	if ((byr != -1) && (iyr != -1) && (eyr != -1) && (hgt != NULL) && (hcl != NULL) && (ecl != NULL) && (pid != NULL)) {
		return true;
	} else
		return false;
}

bool passport::heightcheck() {
	if (strstr(hgt, "cm")) {
		int hght = atoi (hgt);
		if (hght >= 150 && hght <= 193) {
//			printf ("h+");
			return true; 
		} else {
//			printf ("h-");
			return false;
		}
	}
	if (strstr(hgt, "in")) {
		int hght = atoi(hgt);
		if (hght >= 59 && hght <= 76) return true; else return false;
	}
	return false;
}

bool passport::colorcheck() {
	if (strlen(hcl) != 7) return false;
	if (hcl[0] != '#')  return false;
	for (int i=1; i < 7; i++) {
		if (hcl[i] < '0') return false;
		if (hcl[i] > 'z') return false;
		if (hcl[i] > '9' && hcl[i] < 'a') return false;
	}
	return true;
}

bool passport::eclcheck() {
	if (!strcmp(ecl, "amb")) return true;
	if (!strcmp(ecl, "blu")) return true;
	if (!strcmp(ecl, "brn")) return true;
	if (!strcmp(ecl, "gry")) return true;
	if (!strcmp(ecl, "grn")) return true;
	if (!strcmp(ecl, "hzl")) return true;
	if (!strcmp(ecl, "oth")) return true;
	return false;
}

bool passport::pidcheck() {
	if (strlen(pid) != 9) return false; else return true;
}

bool passport::is_valid2() {
	if ((byr != -1) && 
	(iyr != -1) && 
	(eyr != -1) && 
	(hgt != NULL) && 
	(hcl != NULL) && 
	(ecl != NULL) && 
	(pid != NULL) && 
	(byr <= 2002) && (byr >= 1920) &&
	(iyr <= 2020) && (iyr >= 2010) &&
	(eyr <= 2030) && (eyr >= 2020) &&
	heightcheck() &&
	colorcheck() &&
	eclcheck() &&
	pidcheck()) {
//		print_data();
		return true;
	} else
		return false;
}
