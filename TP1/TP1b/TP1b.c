#include <stdio.h>
int LIST[7] = {4, 5, 3, 6, 1, 8, 2};
int biggest, i;
main()
{
	biggest = LIST[0];
	for ( i = 1; i <= 6; i++)
	{
		if ( LIST[i] > biggest )
			biggest = LIST[i];
	}
	printf( "Le nombre le plus grand est: %d \n", biggest );
	
}