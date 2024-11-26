#include <stdio.h>

int LIST[7] = {4, 5, 3, 6, 1, 8, 2};
int biggest, i;

void main() {
	int *p = (int *) 0x7000;

	biggest = LIST[0];
	for (i=1; i<=6; i++) {
		if (LIST[i] > biggest)
			biggest = LIST[i];
	}
	*p = biggest;
}
