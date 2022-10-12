#include <stdio.h>
#include <string.h>

int main(void){
    long box[5] = {0};
    for(int i = 0; i < 5; i++){
        scanf("%ld", &box[i]);
    }
    int cnt = 1;
    for(long i = 0; i < 5; i++){
        for(long j = i + 1; j < 5; j++){
            if(box[i] == box[j]){
                break;
            } else if((box[i] != box[j]) && (j == 4)){
                cnt++;
            }
        }
    }
    printf("%d", cnt);
    return 0;
}