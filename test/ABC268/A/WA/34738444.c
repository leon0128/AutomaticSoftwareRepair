#include<stdio.h>

int cmpnum(const void* num1, const void*num2){
    if(*(int*)num1 > *(int*)num2){
        return 1;
    }else if(*(int*)num1 < *(int*)num2){
        return -1;
    }else{
        return 0;
    }
}

int main(){
    int num[5];
    int ans = 5;
    for(int i = 0; i < 5; i++){
        scanf("%d", &num[i]);
    }

    qsort(num, sizeof(num)/sizeof(num[0]), sizeof(int), cmpnum);

    if(num[0] != num[1] && num[1] != num[2] && num[2] != num[3] && num[3] != num[4]){
        printf("%d", ans);
    }

    for(int i = 0; i < 4; i++){
        if(num[i] == num[i+1]){
            ans--;
        }
    }

    printf("%d", ans);
    return 0;
}