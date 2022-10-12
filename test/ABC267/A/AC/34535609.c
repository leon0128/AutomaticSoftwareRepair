#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int main(void){

char s[10];
scanf("%s",s);

if(s[0]=='M'){
    printf("5");
    return 0;
}
else if(s[1]=='u'){
    printf("4");
    return 0;
}
else if(s[0]=='W'){
    printf("3");
    return 0;
}
else if(s[0]=='T'){
    printf("2");
    return 0;
}

printf("1");
return 0;
    
}