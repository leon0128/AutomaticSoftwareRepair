#include<stdio.h>

int main(void){
    int array[5];
    int tmp;
    for(int i = 0; i < 5; i++){
        scanf("%d", &tmp);
        array[i] = tmp;
    }

    int count = 1;
    for(int i = 1; i < 5; i++){
        int tmp = 0;
        for(int j = 0; j < i; j++){
            if(array[i] == array[j]){
                tmp++;
            }
        }
        if(tmp == 0){
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}