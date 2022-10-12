#include <stdio.h>
#include<string.h>


int main()
{
    char str[50],st[20][20]={"Monday","Tuesday","Wednesday","Thursday","Friday"};
    int i,x,temp;
    scanf("%s",str);
    for(i=0;i<5;i++)
    {
        if(strcmp(st[i],str)==0)
        {
            printf("%d\n",5-i);
            break;
        }
    }
    return 0;
}