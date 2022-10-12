    #include <stdio.h>
     
    int main(void){
     
    	char list[17]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    	int n;
    	scanf("%d",&n);
    	int a=n/16;
     
    	if(n<=16){
    		printf("0%c\n",list[n%16]);
    	}else{
    		printf("%c%c\n",list[a],list[n%16]);
    	}
     
    	return 0;
    }