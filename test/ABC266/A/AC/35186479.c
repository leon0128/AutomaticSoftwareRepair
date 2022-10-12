#include <stdio.h>


int main()
{
    char str[100];
    int length;
    scanf("%s",str);
    length = strlen(str);
    printf("%c\n",str[(length/2)]);

    return 0;

}
