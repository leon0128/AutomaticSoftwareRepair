#include <stdio.h>
#include<string.h>
int main()
{
        char s[100];
        char a;
        int i,counter=0;

        fgets(s,sizeof(s),stdin);

        for(i=0;i<strlen(s);i++)
                counter++;

        for(i=0;i<strlen(s);i++)
        {
                if(i==(counter/2))
                        printf("%c\n",s[i-1]);
        }
        return 0;
}