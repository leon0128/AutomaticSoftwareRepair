#include<stdio.h>
int main()
{
    char a[103];
    int l, s;
    gets(a);
    l=strlen(a);
    s=(l/2);
    printf("%c", a[s]);
}
