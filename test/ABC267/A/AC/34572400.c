#include<stdio.h>
#include<stdlib.h>

static char wd[5][20]={
"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"
};

int main(void)
{
  	int ii;
  	char bf[20];
	scanf("%s",&bf[0]);
  	for(ii=0;ii<5;ii++){
     	if(strcmp(bf,wd[ii])==0)
       		break;
    }
  	printf("%d\n",5-ii);
  
 	return 0; 
}