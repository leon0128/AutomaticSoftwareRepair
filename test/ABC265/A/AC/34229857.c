#include <stdio.h>
int main (void){

int X,Y,N,x,y;

scanf("%d%d%d",&X,&Y,&N);
if(N==1||N==2||3*X<Y){
X=X*N;
printf("%d\n",X);}
else if(3*X>=Y){
for(int i=1;3*i<=N;++i){

    y=i;
}
x=N-3*y;
N=X*x+Y*y;
printf("%d\n",N);

}
return 0;
}