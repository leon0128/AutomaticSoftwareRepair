#include <stdio.h>
#include <string.h>
int main()
{
    char str[10];
    scanf("%s", str);

    /* 文字列を比較する */
    if ( strcmp( str, "Monday" ) == 0 ) {
    printf( "5" );
    }
    else if ( strcmp( str, "Tuesday" ) == 0 ) {
    printf( "4" );
    }
    else if ( strcmp( str, "Wednesday" ) == 0 ) {
    printf( "3" );
    }
    else if ( strcmp( str, "Thursday" ) == 0 ) {
    printf( "2" );
    }
    else if ( strcmp( str, "Friday " ) == 0 ) {
    printf( "1" );
    }
    return 0;
}