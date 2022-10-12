#include <stdio.h>
#include <stdlib.h>
 

int main()
{
    int arr[5], ans = 0;
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &arr[i]);
        int check = 0;
        for (int j = 0; j < i; j++)
        {
            if (arr[i] == arr[j])
            {
                check++;
                break;
            }
            
        }
        if (check == 0)
        {
            ans++;
        }
    }
    printf("%d\n", ans);
    
    return 0;
}