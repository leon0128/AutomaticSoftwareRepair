#include <stdio.h>
#include <string.h>
int main (void){
char s[10]="inu";
char a[]="Monday";
char b[]="Tuesday";
char c[]="Wednesday";
char d[]="Thursday";
char e[]="Friday";



scanf("%s",&s[1]);
if (strcmp(s,a)==1){
printf("5\n");}
else if (strcmp(s,b)==1){
printf("4\n");}
else if (strcmp(s,c)==1){
printf("3\n");}
else if(strcmp(s,d)==1){
printf("2\n");}
else if(strcmp(s,e)==1){
printf("1\n");}
return 0;
}
