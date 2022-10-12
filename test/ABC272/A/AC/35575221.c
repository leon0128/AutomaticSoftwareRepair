#include<stdio.h>
int main(){
int A,B, sum=0;

scanf("%d", &A);

for(int i=1; i<=A; i++){

    scanf("%d", &B);
    sum += B;

}
printf("%d", sum);
}
