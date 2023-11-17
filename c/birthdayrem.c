#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct person {
	char birthday[10];
	char* bYear;
	char* bMonth;
	char* bDay;
	char* name;
	char deathday[10];
	char* dYear;
	char* dMonth;
	char* dDay;
};

struct person parseLine(char* ln) {
	struct person p;

	char *token = ",\n";

	char *b = strtok(ln, token);
	strcpy(p.birthday, b);

	p.name = strtok(NULL, token);
	char *d = strtok(NULL, token);

	token = "-";
	p.bYear = strtok(b, token);
	p.bMonth = strtok(NULL, token);
	p.bDay = strtok(NULL, token);

	if (d != NULL) {
		strcpy(p.deathday, d);
		p.dYear = strtok(d, token);
		p.dMonth = strtok(NULL, token);
		p.dDay = strtok(NULL, token);
	} else {
		strcpy(p.deathday, "");
		p.dYear = "";
		p.dMonth = "";
		p.dDay = "";
	}

	return p;
}

int main() {
	char filename[100];
	strcpy (filename, getenv("HOME"));
	strcat (filename, "/.config/birthdayrem/birthdays");

	FILE *f = NULL;
	
	errno = 0;
	f = fopen(filename, "r");

	if (f == NULL) {
		fprintf(stderr, "Error opening %s for reading, errno: %d\n", filename, errno);
		exit(1);
	}

	char line[256];
	struct person x;

    while (fgets(line, sizeof(line), f)) {
		x = parseLine(line);
		printf(
			"%s %s %s %s %s %s %s %s %s\n", 
			x.birthday, x.bYear, x.bMonth, x.bDay, x.name, x.deathday, x.dYear, x.dMonth, x.dDay
		);
    }

	fclose(f);

	return 0;
}
