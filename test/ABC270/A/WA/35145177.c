#include<stdio.h>
int main()
{
    int a,b, x[5]={0,2,2,0,2}, c[4]={0,1,2,4};
    scanf("%d %d", &a, &b);
    if( a==7 || b==7 )
        printf("7\n");
    else
    {
        for( int i = 0 ; i < 3; i++ )
            for( int j = i+1 ; j < 4 ; j++)
                if( c[i]+c[j] == (a||b))
                    x[c[i]]--, x[c[j]]--;
        int sum = 0;
        for( int i = 0 ; i < 4 ; i++)
            if( x[i] == 2 )
                sum += i;
        printf("%d\n",7 - sum);
    }
    return 0;
}