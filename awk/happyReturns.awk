#!/usr/bin/awk -f

{ 
	if (NR > 2) {
		printf("%3s %s\n", NR-2, $0)
	} else {
		printf("%3s %s\n","  ", $0)
	}
}
