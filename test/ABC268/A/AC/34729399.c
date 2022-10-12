#include <stdio.h>
int main(void) {
	int t;
	// scanf("%d", &t);
    t = 1;
    int arr[5];
	while(t--){
        int n = 5;
	    for(int i = 0; i < n; i++){
            scanf("%d", &arr[i]);
        }
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                if(arr[i] < arr[j]){
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
        int ans = 1;
        for(int i = 0; i < n - 1; i++){
            if(arr[i] != arr[i + 1]){
                ans++;
            }
        }
        printf("%d\n", ans);
	}
	return 0;
}

