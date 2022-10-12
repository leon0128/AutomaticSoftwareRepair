#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *arr = (char*)calloc(100, sizeof(char));
    scanf("%s", arr);
    printf("%c", arr[strlen(arr)/2]);
    return 0;
}
