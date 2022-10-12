#include <stdio.h>
int main(void){
    // Your code here!
    int a, b;
    scanf("%d %d\n", &a, &b);
    int score = 0;
    
    int correct[3] = {0, 0, 0};
    int point[3] = {1, 2, 4};
    while(a > 0){
        if (a - 4 >= 0){
            
            a -= 4;
            correct[2] = 1;
        }
        if (a - 2 >= 0){
            
            a -=2;
            correct[1] = 1;
        }
        if (a - 1 >= 0){
            
            a -= 1;
            correct[0] = 1;
        }
    }
    
    while(b > 0){
        if (b - 4 >= 0){
            
            b -= 4;
            correct[2] = 1;
        }
        if (b - 2 >= 0){
            
            b -=2;
            correct[1] = 1;
        }
        if (b - 1 >= 0){
            
            b -= 1;
            correct[0] = 1;
        }
    }
    
    for (int i = 0; i < 3; i++){
        if (correct[i] == 1){
            score += point[i];
        }
    }
    
    printf("%d\n", score);
}
