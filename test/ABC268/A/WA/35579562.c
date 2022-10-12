#include <stdio.h>

int main()
{	
	int a, b, c, d, e;
	int i=0, s=0, cnt=0;
	scanf("%d %d %d %d %d",&a, &b, &c, &d, &e);
	int f[5] = {a, b, c, d, e};
	for (;i<5;i++){
		for(;s<5;s++){
			if(f[i]==f[s]) cnt++;
		}
	}
	printf("%d",cnt);
	
	
	
	return 0;
}