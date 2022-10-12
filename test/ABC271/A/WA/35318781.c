#include<stdio.h>
void decToHex(int decNum)
{
    char hexaDeciNum[50];
    int i = 0;
    if(decNum/16 == 0)
        {
            printf("0");
        }
    while (decNum != 0)
    {
        int temp = 0;
        temp = decNum % 16;
        if (temp < 10)
        {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else
        {   hexaDeciNum[i] = temp + 55;
            i++;
        }
        decNum = decNum / 16;
    }
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%0.2c",hexaDeciNum[j]);
    }
}
int main()
{
    int decNum;
    scanf("%d",&decNum);
    decToHex(decNum);
    return 0;
}
