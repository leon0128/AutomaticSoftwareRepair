#include<stdio.h>
int main()
{
    int a[2], x[5]={0,2,2,0,2}, c[4]={0,1,2,4};
    scanf("%d %d", &a[0], &a[1]);
    if( a[0]==7 || a[1]==7 )
        printf("7\n");
    else
    {
        for( int k = 0 ; k < 2 ; k++ )
        {
            for( int i = 0 ; i < 3; i++ )
                for( int j = i+1 ; j < 4 ; j++)
                    if( c[i]+c[j] == a[k])
                        x[c[i]]--, x[c[j]]--;
            //printf("%d %d %d\n", x[1], x[2], x[4]);
        }
        int sum = 0;
        for( int i = 0 ; i < 5 ; i++)
            if( x[i] == 2 )
                sum += i;
        printf("%d\n",7 - sum);
    }
    return 0;
}