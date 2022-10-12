#include <stdio.h>
#include <string.h>
int main()
{
    char str[10];
    int nokori;
    scanf("%s", str);

    /* 文字列を比較する */
    if ( strcmp( str, "Monday" ) == 0 ) {
    nokori = 5;
    printf("%d",nokori);
    }
    else if ( strcmp( str, "Tuesday" ) == 0 ) {
    nokori = 4;
    printf("%d",nokori);
    }
    else if ( strcmp( str, "Wednesday" ) == 0 ) {
    nokori = 3;
    printf("%d",nokori);
    }
    else if ( strcmp( str, "Thursday" ) == 0 ) {
    nokori = 2;
    printf("%d",nokori);
    }
    else if ( strcmp( str, "Friday " ) == 0 ) {
    nokori = 1;
    printf("%d",nokori);
    }
    return 0;
}