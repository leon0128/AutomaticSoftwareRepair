#include <stdio.h>
#include <string.h>

int main ()
{
	int nums[5],i,j,count=5;
  	for(i=0;i<5;i++){
    	scanf("%d",&nums[i]);
    }
  	for(i=0;i<5;i++){
      if(i>=1){
      	if(nums[i-1]==nums[i]){
        	continue;
        }
      }
    	for(j=i+1;j<5;j++){
        	if(nums[i]==nums[j]){
            	count--;
            }
        }
    }
  	
  	printf("%d",count);
}