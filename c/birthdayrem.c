#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct person {
	int bYear;
};

struct person parseLine(char* ln) {
	struct person p;

	p.bYear = 43;

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
		printf("%s :: %d\n", line, x.bYear);
    }

	fclose(f);

	return 0;
}
