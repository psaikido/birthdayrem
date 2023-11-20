#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>


typedef struct person {
	char name[50];
	char birthday[20];
	int bYear;
	int bMonth;
	int bDay;
	char deathday[20];
	int dYear;
	int dMonth;
	int dDay;
	int alive;
	int hadBirthday;
	int age;
	int next;
} person;


typedef struct now {
	int year;
	int month;
	int day;
} now;


FILE* getFile(); 
person parseLine(char* ln);
int dateSort(const void *p1, const void *p2);
now setNow(); 
person* beforeOrAfterBirthday(person p[], int count);
person* calcAges(person p[], int count);
void output(person p[], int count, int mode); 


int main() {
	FILE *f = getFile();

	person p[100];

	int i = 0;
	char line[256];

    while (fgets(line, sizeof(line), f)) {
		p[i++] = parseLine(line);
    }

	fclose(f);

	// Put in date order.
	qsort(p, i, sizeof(person), dateSort);

	// Those whose birthdays are yet to come this year go on top.
	person *sorted = beforeOrAfterBirthday(p, i);

	// Get the ages-now and next.
	person *withAges = calcAges(sorted, i);

	output(withAges, i, 0);

	return 0;
}


person* calcAges(person p[], int count) {
	now n = setNow();

	for (int i = 0; i < count; i++) {
		if (p[i].alive == 1) {
			if (p[i].hadBirthday) {
				p[i].age = n.year - p[i].bYear;
			} else {
				p[i].age = (n.year - p[i].bYear) - 1;
			}

			p[i].next = p[i].age + 1;
		} else {
			if (p[i].hadBirthday) {
				p[i].age = p[i].dYear - p[i].bYear;
			} else {
				p[i].age = (p[i].dYear - p[i].bYear) - 1;
			}

			p[i].next = -1;
		}
	}

	return p;
}


now setNow() {
	now n;

	time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    char year[5];
    char month[3];
    char day[3];

    strftime(year, sizeof(year), "%Y", tm);
    strftime(month, sizeof(month), "%m", tm);
    strftime(day, sizeof(day), "%d", tm);

	n.year = atoi(year);
	n.month = atoi(month);
	n.day = atoi(day);

	return n;
}


person* beforeOrAfterBirthday(person p[], int count) {
	now n = setNow();

	person before[100];
	person after[100];

	int countBefore = 0;
	int countAfter = 0;
	int countRes = 0;
	int i;

	for (i = 0; i < count; i++) {
		if (strlen(p[i].deathday) > 0) {
			p[i].alive = 0;
		} else {
			p[i].alive = 1;
		}

		if (p[i].bMonth < n.month) {
			p[i].hadBirthday = 1;
			before[countBefore++] = p[i];
		} else if (p[i].bMonth == n.month) {
			if (p[i].bDay < n.day) {
				p[i].hadBirthday = 1;
				before[countBefore++] = p[i];
			}
		} else {
			p[i].hadBirthday = 0;
			after[countAfter++] = p[i];
		}
	}

	// Reorder main array with those who are yet to have their birthdays on top.
	person res[100];

	for (i = 0; i < countAfter; i++) {
		res[countRes++] = after[i];
	}

	for (i = 0; i < countBefore; i++) {
		res[countRes++] = before[i];
	}

	p = res;

	return p;
}


int dateSort(const void *p1, const void *p2) {
	person *person1 = (person *)p1;
	person *person2 = (person *)p2;

	// Cast date parts to integers from the pointers 'person1' and 2.
	int y1 = person1->bYear; 
	int m1 = person1->bMonth; 
	int d1 = person1->bDay; 
	int y2 = person2->bYear; 
	int m2 = person2->bMonth; 
	int d2 = person2->bDay; 

	// Sort by month, then day then year.
	if (m1 < m2) {
		return -1;
	} else if (m1 == m2) {
		if (d1 < d2) {
			return -1;
		} else if (d1 == d2) {
			if (y1 <= y2) {
				return -1;
			} else {
				return 1;
			}
			return 0;
		} else {
			return 1;
		}
	} else {
		return 1;
	}
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

	while((token = strtok_r(line, ",\n", &line)) != NULL) {
		if (count == 0) strcpy(p.birthday, token);
		if (count == 1) strcpy(p.name, token);
		if (count == 2) strcpy(p.deathday, token);
		count++;
	}

	char b_tmpYear[5];
	char b_tmpMonth[3];
	char b_tmpDay[3];

	sscanf(p.birthday, "%4s-%2s-%2s", b_tmpYear, b_tmpMonth, b_tmpDay);

	p.bYear = atoi(b_tmpYear);
	p.bMonth = atoi(b_tmpMonth);
	p.bDay = atoi(b_tmpDay);

	char d_tmpYear[5];
	char d_tmpMonth[3];
	char d_tmpDay[3];

	sscanf(p.deathday, "%4s-%2s-%2s", d_tmpYear, d_tmpMonth, d_tmpDay);

	p.dYear = atoi(d_tmpYear);
	p.dMonth = atoi(d_tmpMonth);
	p.dDay = atoi(d_tmpDay);

	return p;
}


void output(person p[], int count, int mode) {
	char next[3];

	printf(
		"%s %10s %8s %8s\n", 
		"yyyy-mm-dd", "NAME", "AGE-NOW", "NEXT" 
	);

	printf(
		"%34s\n", 
		"---------------------------------------" 
	);

	for (int i = 0; i < count; i++) {
		if (mode == 0) {
			// The 'next' field can be either an integer or a hyphen if the person has died.
			if (p[i].next >= 0) {
				sprintf(next, "%d", p[i].next);
			} else {
				strcpy(next, "-");
			}

			printf(
				"%s %10s %8d %8s\n", 
				p[i].birthday, p[i].name, p[i].age, next
			);
		} else {
			printf(
				"%d: %s %d %d %d %s %s %d %d %d %d %d %d %d\n", 
				i, p[i].birthday, p[i].bYear, p[i].bMonth, p[i].bDay, p[i].name, p[i].deathday, p[i].dYear, p[i].dMonth, p[i].dDay, p[i].hadBirthday, p[i].alive, p[i].age, p[i].next
			);
		}
	}
}

