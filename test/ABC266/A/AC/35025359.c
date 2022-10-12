#include<stdio.h>
int main(){
	char s[100];
    int i;
  
    scanf("%s",s);
    
    for(i=0;i < 100;i++){
    	if(s[i] == '\0'){
        	break;
        }
    }
  	if(i == 1){
    	printf("%s",s);
    }else{
      	printf("%c",s[(i+1)/2-1]);
    }
  	return 0;
}