#include <stdio.h>
#include <string.h>
int main (void){
int f=1,g=2,h=3,i=4,j=5;
char s[10]="inu";
char a[]="Monday";
char b[]="Tuesday";
char c[]="Wednesday";
char d[]="Thursday";
char e[]="Friday";



scanf("%s",&s[1]);
if (strcmp(s,a)==1){
printf("%d\n",f);}
else if (strcmp(s,b)==1){
printf("%d\n",g);}
else if (strcmp(s,c)==1){
printf("%d\n",h);}
else if(strcmp(s,d)==1){
printf("%d\n",i);}
else if(strcmp(s,e)==1){
printf("%d\n",j);}
return 0;
}