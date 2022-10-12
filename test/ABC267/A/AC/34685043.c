#include <stdio.h>
#include <string.h>
int main() {
	char day[10]={0};
    int r=1;
    scanf("%s",day);
    if (!strcmp(day,"Monday")) r=5;
    else if (!strcmp(day,"Tuesday")) r=4;
    else if (!strcmp(day,"Wednesday")) r=3;
    else if (!strcmp(day,"Thursday")) r=2;
    printf("%d\n",r);
	return 0;
}