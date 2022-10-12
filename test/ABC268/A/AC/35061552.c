#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cmpnum(const void * n1, const void * n2)
{
	if (*(long *)n1 > *(long *)n2)
	{
		return 1;
	}
	else if (*(long *)n1 < *(long *)n2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
int main(void) {
    const int num = 5;
    long a[num];
    for (int i = 0; i < num; i++) {
        scanf("%ld", &a[i]);
    }
    int ans=1;
    qsort(a,sizeof(a)/sizeof(a[0]),sizeof(long),cmpnum);
    for (int i = 0; i < num-1; i++) {
    if(a[i]!=a[i+1]){
        ans++;
    }
    }
    printf("%d\n",ans);
    return 0;
}