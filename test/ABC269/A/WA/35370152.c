#include<stdio.h>
int main()
{
    int n = 0;
    int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
	for(int i = 1 ; i <= 10 ; i ++ )
    {
        char s[15];
        scanf("%s",s);
        for(int j = 1 ; j <= 10 ; j ++)
        {
            if(s[j] == '#')
            {
                if(x1 == -1) 
                x1 = i, y1 = j;
                x2 = i, y2 = j;
            }
        }
    }
    printf("%d %d\n",x1,x2);
    printf("%d %d\n",y1,y2);
    return 0;
 }