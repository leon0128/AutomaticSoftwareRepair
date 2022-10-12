#include<stdio.h>

#include<string.h>

int main(){

    char *str[]={"Monday","Tuesday","Wednesday","Thursday","Friday","S"} ;

    char st[10];

    scanf("%s",st);

    for(int i=0;i<6;i++){

        if(strcmp(st,str[i])==0){

            printf("%d",(5-i));

            break;
        }
    }

return 0;

}
