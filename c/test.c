#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int getNow(int* m, int* d) {
	time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char month[3];
    char day[3];
    strftime(month, sizeof(month), "%m", tm);
    strftime(day, sizeof(day), "%d", tm);
	*m = atoi(month);
	*d = atoi(day);
}


int main() {
	int m, d;
	getNow(&m, &d);
	printf("%d %d\n", m, d);
}
