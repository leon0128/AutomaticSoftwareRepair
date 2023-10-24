#include <stdio.h>

int main()
{
    int input;
    int uruu;
    uruu = 0;
    scanf("%d", & input);
    printf("%s\n", (((input % 400 == 0) ? 1 : (input % 100 == 0) ? 0 : (input % 4 == 0) ? 1 : 0) ? "YES" : "NO"));
    
    if((input % 100) == 0)
        uruu = 0;
    else
        ;
    
    if((input % 400) == 0)
        uruu = 1;
    else
        ;
    uruu = input;
    
    if(uruu == 1)
        printf("Yes\n");
    else
        ;
    
    return 0;
}