#include <stdio.h>
int i, count;

main() {
	int *t = (int *) 0x7000;
	int *d = (int *) 0x7004;

	*t = 0xFFFF;

	count = 0;
	for (i=0; i<32; i++) {
		if (t[i]) {
			count++;
		}
	}

	*d = count;	
}