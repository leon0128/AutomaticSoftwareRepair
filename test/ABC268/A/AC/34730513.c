/*-----------------------------------------------*/
/*-	at coder - NNN: -*/
/*-----------------------------------------------*/

#include <stdio.h>

int main (int argc, char** argv) 
{
	int		stac[100];
	int		N = 5;

	memset( stac, 0x00, sizeof(int) * 100);

	for ( int i=0; i<5; i++) {
		int		IN;
		scanf("%d", &IN);
		if ( stac[IN] == 1 ) N--;
		stac[IN]	= 1;
	}

	printf("%d\n", N);

	return 0;
}

