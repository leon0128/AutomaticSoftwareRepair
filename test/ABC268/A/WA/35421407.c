    #include <stdio.h>
    int main(){
    	int numbers[5];
      	int count=0;
      	int flag=0;
     	scanf("%d %d %d %d %d",&numbers[0],&numbers[1],&numbers[2],&numbers[3],&numbers[4]);
      	for(int i=0;i<5;i++){
        	for(int j=i+1;j<5;j++){
            	if(numbers[i]==numbers[j]){
                	flag=1;
                  	break;
                }
            }  
        	if(!flag)
              count++;
          	flag=0;
        }
    }
     
     