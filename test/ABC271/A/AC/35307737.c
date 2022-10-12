#include <stdio.h>

void Answer(int);

int main(void){
    int N;
    scanf("%d", &N);
    
    if(N / 16 < 1)
    {
        printf("0");
        Answer(N);
    }
    else
    {
        Answer(N / 16);
        Answer(N % 16);
    }   
        
    return 0;
}

void Answer(int answer)
{
    switch (answer)
    {
        case 10:
            printf("A");
            break;
        case 11:
            printf("B");
            break;
        case 12:
            printf("C");
            break;
        case 13:
            printf("D");
            break;
        case 14:
            printf("E");
            break;
        case 15:
            printf("F");
            break;
        default:
            printf("%d", answer);
            break;
        }
}