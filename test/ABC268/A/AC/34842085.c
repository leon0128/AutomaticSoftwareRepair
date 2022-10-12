#include <stdio.h>
int main(){
    int b, a[101] = {0}, count = 0;
    for(int i = 0; i < 5; i++){
        scanf("%d", &b);
        if(a[b] == 0){
            a[b] = 1;
            count++;
        }
    }
    printf("%d\n", count);

}