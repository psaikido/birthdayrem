#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

FILE* getFile(); 
struct Person parseLine(char* ln);

struct Person {
	char* name;
	char birthday[10];
	char* bYear;
	char* bMonth;
	char* bDay;
	char deathday[10];
	char* dYear;
	char* dMonth;
	char* dDay;
};

void output(struct Person people[], int count) {
	for (int i = 0; i < count; i++) {
		printf("%d: %s\n", i, people[i].name);
	}
}

int main() {
	FILE *f = getFile();

	char line[256];
	struct Person p[100];

	int i = 0;

    while (fgets(line, sizeof(line), f)) {
		p[i] = parseLine(line);
		// printf(
		// 	"%d: %s %s %s %s %s %s %s %s %s\n", 
		// 	i, p[i].birthday, p[i].bYear, p[i].bMonth, p[i].bDay, p[i].name, p[i].deathday, p[i].dYear, p[i].dMonth, p[i].dDay
		// );

		i++;
    }

	fclose(f);

	// output(p, i);
	printf("%s\n", p[4].name);

	return 0;
}

FILE* getFile() {
	char filename[100];
	strcpy (filename, getenv("HOME"));
	strcat (filename, "/.config/birthdayrem/birthdays");

	FILE *f = NULL;
	
	errno = 0;
	f = fopen(filename, "r");

	if (f == NULL) {
		fprintf(stderr, "Error opening %s for reading, errno: %d\n", filename, errno);
		exit(1);
	} else {
		return f;
	}
}

struct Person parseLine(char* ln) {
	struct Person p;

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

