#include <stdio.h>
int main()
{
    char s[10][50]={"Thursday","Fr","Th","We","Tu","Mo"};
    scanf("%s",s[0]);
    int i=0;

    for(i=1;i<5;i++)
    {
        if(s[0][0]==s[i][0])
        if(s[0][1]==s[i][1])

        break;
    }
    printf("%d",i);

}