#include<stdio.h>

int main()
{
    int n;
    int arr[n];
    int sum = 0;

    for (int i = 0; i<n;i++)
    {
        scanf("%d", arr[i]);
        sum += arr[i];
    }
    printf ("%d", sum);
    return 0 ; 
}