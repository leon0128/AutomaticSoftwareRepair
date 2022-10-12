#include<stdio.h>

void main()
{
    int count=0,i=0;
    char a[100];
    gets(a);
    
    while(a[i]!='\0'){
    count++;
    i++;  
    }
    int c=(count+1)/2-1;      
    printf("%c",a[c]);  
}