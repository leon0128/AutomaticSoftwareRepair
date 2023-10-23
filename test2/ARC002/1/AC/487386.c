#include <stdio.h>

int main(int argc, const char * argv[]) {
    int N;
    
    scanf("%d", &N);
    
    if(N % 400 == 0){
        printf("YES\n");
    }else if(N % 100 == 0){
        printf("NO\n");
    }else if(N % 4 == 0){
        printf("YES\n");
    }else{
        printf("NO\n");
    }
    
    return 0;
}