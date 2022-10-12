#include<stdio.h>

int main(){
    int s[5], i, j;
    int cnt = 0;
    
    for(i = 0;i < 5;i++){
        int flag = 0;
        scanf("%d", &s[i]);

        for(j = 0;j < i;j++) if(s[i] == s[i - j - 1]) flag = 1;

        if(flag == 0) cnt++;

    }

    printf("%d", cnt);

    return 0;

}