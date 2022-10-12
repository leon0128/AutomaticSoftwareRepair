#include<stdio.h>
/*pointer*/
int *p1;

/*kansu*/
void keisan(char saisho, char tugi);

int main(void)
{
	/*sengen*/
	char nyu[10];
	int ans = 0;
	
	/*yomikomi*/
	scanf("%s", nyu);
	p1 = &ans;
	
	/*keisan*/
	keisan(nyu[0], nyu[1]);
	
	/*hyoji*/
	printf("%d", ans);
}
		
void keisan(char saisho, char tugi)
{
	if(saisho == 'M')
	*p1 = 5;
	else if(saisho == 'W')
	*p1 = 3;
	else if(saisho == 'F')
	*p1 = 1;
	else if(tugi == 'u')
	*p1 = 4;
	else
	*p1 = 2;
}
		