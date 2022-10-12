#include <stdio.h>
int main(void){
    char str[10];
    scanf("%s", str);
    int a=0;
    
    if(str[0]=='M')a=5;
    if(str[0]=='T'&&str[1]=='u')a=4;
    if(str[0]=='W')a=3;
    if(str[0]=='T'&&str[1]=='h')a=2;
    if(str[0]=='F')a=1;
    
    printf("%d",a);
    
 
    return 0;
}