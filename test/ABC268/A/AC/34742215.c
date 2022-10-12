#include <stdio.h>
/*pointer*/
int *p1;

/*kozotai*/

/*kansu*/
void keisan(int *);

int main(void)
{
	/*sengen*/
	int nyu[5], i, ans = 0;
	
	/*yomikomi*/
	for(i = 0;i < 5;i++)
	scanf("%d", &nyu[i]);
	p1 = &ans;
	
	/*keisan*/
	keisan(nyu);
	
	/*hyoji*/
	printf("%d", ans);
	return 0;	
}

void keisan(int *kazu)
{
	/*sengen*/
	int i, j, count = 0;
	
	for(i = 0;i < 5;i++)
	{
		for(j = 0;j < 5;j++)
		{
		if ((kazu[i] == kazu[j]) && (i < j))
			{
			count++;
			break;
			}
		}
	}
	*p1 = 5 - count;
}
