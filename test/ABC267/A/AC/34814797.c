#include<stdio.h>
/*
int main()
{
	int a, b ,c,d = 0;
	scanf("%d %d %d",&a,&b,&c);
	if(a * 3 < b)
	printf("%d",a * c);
	else
	{
    	d = c % 3;
    	c = c / 3;
    	printf("%d",a * d + b * c);
	}
    return 0;
}

int main()
{
	char S[100];
	gets(S);
	int i = 0;
	while(S[i] != 0)
		i++;
	printf("%c",S[i / 2]);
}
*/
int main()
{
    char c[10];
    int a = 0;
    scanf("%s",c);
    if(c[0] == 'M')
		a = 5;
    if(c[0] == 'T' && c[1] == 'u')
		a = 4;
    if(c[0] == 'W')
		a = 3;
    if(c[0] == 'T' && c[1] == 'h')
		a = 2;
    if(c[0] == 'F')
		a = 1; 
    printf("%d",a);
    return 0;
}
/*
int main()
{
    int A,B,C,D,E,F,X,m = 0,n = 0,i;
    scanf("%d %d %d %d %d %d %d",&A,&B,&C,&D,&E,&F,&X);
    for(i = 0;i < X;i++)
	{
        if(i % (A + C) < A)
            n += B;
        if(i % (D + F) < D)
            m += E;
    }
    if(m < n)
        printf("Takahashi\n");
    else if(m > n)
        printf("Aoki\n");
    else
        printf("Draw\n");
 
    return 0;
}

int main()
{
	int n,i,t,x = 0;
	char a[12];
	scanf("%s",&a);
	for(n = 0;n < 9;n++)
	x = x + a[n];
	printf("%d",477 - x);
}

int main() 
{
    char s[8];
    s[0] = '0';
    gets(s + 1);
    s[4] = 0;
    puts(s);
}
*/
