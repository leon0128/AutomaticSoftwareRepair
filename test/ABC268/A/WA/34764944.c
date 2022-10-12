#include<stdio.h>
#include<string.h>
int main()
{
    char s[101], t[101];
    scanf("%s %s", s, t);
    int ls=strlen(s);
    int lt=strlen(t);
    if(ls>lt)
    {
        printf("No\n");
        return 0;
    }
    int i;
    for(i=0; i<ls; i++)
    {
        if(s[i]!=t[i])
        {
            printf("No\n");
            return 0;
        }
    }
    printf("Yes\n");
}
