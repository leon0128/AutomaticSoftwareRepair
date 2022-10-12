#include <stdio.h>
int main()
{int x,y,n,a,b;
    scanf("%d%d%d",&x,&y,&n);
   a= n%3;
   b=n-a; 
if(3*x >y){
    printf("%d",b*y/3 +a* x);}
    else 
    printf("%d",x*n);

    return 0;
}