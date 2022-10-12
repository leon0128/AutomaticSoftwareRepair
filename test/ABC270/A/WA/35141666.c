#include<stdio.h>
int main(){
int a,b;
scanf("%d %d",&a,&b);

if(a>b){
    printf("%d\n",a+b-1);

}
else if(a<b){
    printf("%d\n",a+b);
}
else{
    printf("0\n");
}
}
