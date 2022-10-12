#include<stdio.h>
#include<math.h>

int main(void){
  
  int x,N,n;
  char M ='Y'; /*Yはない意味*/
  char m ='y'; /*yはない意味*/
  
  
  scanf("%d",&x);
  N = x/16;
  n = x%16;
  
  if(N==10) M = 'A'; if(N==11) M = 'B'; if(N==12) M = 'C'; if(N==13) M = 'D'; if(N==14) M = 'E'; if(N==15) M = 'F';
  if(N==10) m = 'A'; if(N==11) m = 'B'; if(N==12) m = 'C'; if(N==13) m = 'D'; if(N==14) m = 'E'; if(N==15) m = 'F';
  if(M =='Y') printf("%d",N);
  else printf("%c",M);
  if(m =='y') printf("%d",n);
  else printf("%c",m);
  
  return 0;
}
