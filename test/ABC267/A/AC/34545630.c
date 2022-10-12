#include <stdio.h>
#include <string.h>

int main()
{
    char s[16];
    char *str[5]={"Monday","Tuesday","Wednesday","Thursday","Friday"};
    int i;
    int m=5;
    int n=0;

    scanf("%s\n",s);

    for(i=0;i<5;i++){
        if(strcmp(s,str[i])==0){
            n=i;
            break;
        }
    }

    printf("%d\n",m-n);

    return 0;
}