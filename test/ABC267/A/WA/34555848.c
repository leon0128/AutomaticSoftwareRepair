#include <stdio.h>
int main()
{
    char s[6][30]={"","Friday","Thursday"," Wednesday","Tuesday","Monday"};
    scanf("%s",s[0]);
    int i;
    for(i=1;i<5;i++)
    {
        if(s[i]==s[0])
        break;
    }
    printf("%d",i);

}