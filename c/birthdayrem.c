#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct person {
	char* birthday;
	char* bYear;
	char* bMonth;
	char* bDay;
	char* name;
	char* deathday;
};

struct person parseLine(char* ln) {
	struct person p;

	char *token = ",\n";

	char *birthday = strtok(ln, token);
	char *name = strtok(NULL, token);
	char *deathday = strtok(NULL, token);

	token = "-";
	char *ch_bYear = strtok(birthday, token);
	char *ch_bMonth = strtok(NULL, token);
	char *ch_bDay = strtok(NULL, token);

	p.birthday = birthday;
	p.bYear = ch_bYear;
	p.bMonth = ch_bMonth;
	p.bDay = ch_bDay;
	p.name = name; p.deathday = deathday;

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
		printf("%s %s %s %s %s\n", x.bYear, x.bMonth, x.bDay, x.name, x.deathday);
    }

	fclose(f);

	return 0;
}
