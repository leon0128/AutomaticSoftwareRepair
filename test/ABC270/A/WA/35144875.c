#include<stdio.h>
int main()
{
    int a[2], x[5]={0,2,2,0,2};
    scanf("%d %d", &a[0], &a[1]);
    if( a[0]==7 || a[1]==7 )
        printf("7\n");
    else
    {
        for( int k = 0 ; k < 2 ; k++ )
        {
            for( int i = 0 ; i < 3; i++ )
                for( int j = 1 ; j < 5 ; j++)
                    if( i+j == a[k] )
                        x[i]--, x[j]--;
        }
        int sum = 0;
        for( int i = 0 ; i < 5 ; i++)
            if( x[i] == 2 )
                sum += i;
        printf("%d\n",7 - sum);
    }
    return 0;
}