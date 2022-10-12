#include<stdio.h>
#include<string.h>
int main(){
	char sat[20];
	char mon[20]="Monday",tue[20]="Tuesday",wed[20]="Wednesday",thu[20]="Thursday",fri[20]="Friday";
	scanf("%s",sat);
	if(strcmp(sat,mon)==0)printf("%d",5);
	else if(strcmp(sat,tue)==0)printf("%d",4);
	else if(strcmp(sat,wed)==0)printf("%d",3);
	else if(strcmp(sat,thu)==0)printf("%d",2);
	else if(strcmp(sat,fri)==0)printf("%d",1);
	return 0;
}