#include <stdio.h>

int main()
{
    int day;
    scanf("%d", & day);
    printf(day % 4 == 0 ? (day % 100 == 0 ? (day % 400 == 0 ? "YES\n" : "NO\n") : "YES\n") : "NO\n");
    
    return 0;
}