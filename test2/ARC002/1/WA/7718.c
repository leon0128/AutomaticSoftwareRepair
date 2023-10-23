    #include <stdio.h>
    int main(void)
    {
    int a;
    scanf("%d", &a);
    if(a%4)
    printf("NO");
    else if(!(a%400))
    printf("YES");
    else if(a % 100)
    printf("NO");
    else printf("YES");
    puts("");
    return 0;
    }