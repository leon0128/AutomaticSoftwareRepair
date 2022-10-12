#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int min(int a, int b){
    return a < b ? a : b;
}
int max(int a, int b){
    return a > b ? a : b;
}
long long cmp(const void * a, const void * b) {
  return ( *(long long*)a - *(long long*)b );
}
long long power(int i){
    long long ans = 1;
    while(i--){
        ans *= 2;
    }
    return ans;
}
int main(){
    int test;
    // scanf("%d", &test);
    test = 1;
    while(test--){
        long long n;
        scanf("%lld", &n);
        int arr[16] = {0};
        long long temp = n;
        int len = 0;
        while(temp != 0){
            arr[len] = temp%2;
            len++;
            temp /= 2;
        }
        // for(int i = 0; i < len; i++){
        //     printf("%d", arr[i]);
        // }
        int temp2 = len;
        long long ans[1000000];
        len = 0;
        ans[len] = 0;
        len++;
        for(int i = 0; i < temp2; i++){
            if(arr[i] == 1){
                ans[len] = power(i);
                // printf("2 %lld\n", ans[len]);
                temp = len;
                len++;
                for(int j = 1; j < temp; j++){
                    ans[len] = ans[j] + ans[temp];
                    len++;
                }
            }
        }
        qsort(ans, len, sizeof(long long), cmp);
        for(int i = 0; i < len; i++){
            printf("%lld\n", ans[i]);
        }
        
    }
    return 0;
}

