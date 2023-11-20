#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
	char* birthday;
} person;

int main() {
	person p;
	strcpy(p.birthday, "thing");
	printf("%s\n", p.birthday);
}
