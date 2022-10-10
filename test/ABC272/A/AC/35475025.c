#include <stdio.h>

int main(void){
    int n, i;
    int sum = 0;
    scanf("%d", &n);

    int num[n];

    for(i=0; i<n; i++){
        scanf("%d", &num[i]);
        sum += num[i];
    }

    printf("%d\n", sum);

    return 0;

}
