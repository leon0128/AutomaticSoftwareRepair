#include<stdio.h>

int main()
{
    int arr[5], t = 5;
    for(int i = 0; i < 5; i++)
    {
        scanf("%d", &arr[i]);
        for(int j = 0; j < i; j++)
            if(arr[i] == arr[j])
            {
                t--;
                break;
            }
    }
    printf("%d", t);
    return 0;
}