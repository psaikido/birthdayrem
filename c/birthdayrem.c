#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct Person {
	char name[50];
	char birthday[20];
	char bYear[5];
	char bMonth[3];
	char bDay[3];
	char deathday[20];
	char dYear[5];
	char dMonth[3];
	char dDay[3];
} person;

FILE* getFile(); 
person parseLine(char* ln);
void output(person p[], int count); 

int main() {
	FILE *f = getFile();

	person p[100];

	int i = 0;
	char line[256];

    while (fgets(line, sizeof(line), f)) {
		p[i++] = parseLine(line);
    }

	fclose(f);
	output(p, i);

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

person parseLine(char* ln) {
	person p;

	char* line = strdup(ln);
	char* token;
	int count = 0;
	int commaCount = 0;

	for (int i = 0; line[i] != 0; i++) {
		if (line[i] == ',') commaCount++;
	}

	strcpy(p.deathday, "");
	strcpy(p.dYear, "");
	strcpy(p.dMonth, "");
	strcpy(p.dDay, "");

	while((token = strtok_r(line, ",\n", &line)) != NULL) {
		if (count == 0) strcpy(p.birthday, token);
		if (count == 1) strcpy(p.name, token);
		if (count == 2) strcpy(p.deathday, token);
		count++;
	}

	sscanf(p.birthday, "%4s-%2s-%2s", p.bYear, p.bMonth, p.bDay);
	sscanf(p.deathday, "%4s-%2s-%2s", p.dYear, p.dMonth, p.dDay);

	return p;
}

void output(person p[], int count) {
	for (int i = 0; i < count; i++) {
		// printf(
		// 	"%d: %s %s %s %s %s %s %s %s %s\n", 
		// 	i, p[i].birthday, p[i].bYear, p[i].bMonth, p[i].bDay, p[i].name, p[i].deathday, p[i].dYear, p[i].dMonth, p[i].dDay
		// );
		printf(
			"%s %s %s\n", 
			p[i].birthday, p[i].name, p[i].deathday
		);
	}
}

