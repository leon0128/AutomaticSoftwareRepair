#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void) {
    int n;

    scanf("%d",&n);
    int s[n];
    int sum=0;
for(int i=0;i<n;i++){
scanf("%d",&s[i]);
}
for(int i=0;i<n;i++){
sum=sum+s[i];
}

    printf("%d",sum);


    return 0;
	}


