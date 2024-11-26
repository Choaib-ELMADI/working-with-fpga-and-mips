#include <stdio.h>

int i, count = 0;

void main() {
	int *t = (int *) 0x7000;
	int *d = (int *) 0x7004;

	*t = 0xFFFF;

	for (i=0; i<32; i++) {
		if (*t & 0x0001) {
			count++;
		}
		*t = *t >> 1;
	}

	*d = count;
}
