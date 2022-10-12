#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* function(int num)
{
    char* str = (char*)malloc(sizeof(char) * 8);
    int n = 0;
    if (num == 0)
    {
        str[0] = '0';
        str[1] = '0';
        str[2] = '\0';
        return str;
    }
    if (num < 16)
    {
        str[0] = '0';
        if (num < 10)
        {
            str[1] = num + '0';
            str[2] = '\0';
            return str;
        }
        else
        {
            str[1] = num - 10 + 'A';
            str[2] = '\0';
            return str;
        }
    }

    while (num != 0)
    {
        int temp = num & 0xF;
        if (temp < 10)
        {
            str[n++] = temp + '0';
        }
        else
        {
            str[n++] = temp - 10 + 'A';
        }
        num >>= 4;
    }
    int indexLeft = 0;
    int indexRight = n - 1;
    while (indexLeft < indexRight)
    {
        char temp = str[indexLeft];
        str[indexLeft] = str[indexRight];
        str[indexRight] = temp;
        indexLeft++;
        indexRight--;
    }
    str[2] = '\0';
    return str;
}

int main()
{
    int a = 0;
    scanf("%d", &a);
    printf("%s", function(a));
    return 0;
}