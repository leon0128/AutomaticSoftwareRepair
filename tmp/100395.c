#include <stdio.h>

int main(void)
{
    int i, j;
    int daymin, monmin;
    int uruu, flg;
    int waridata, waridata1;
    int year, mon, day;
    int mondata[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, mondata1[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    float wari, wari1;
    scanf("%d/%d/%d", & year, & mon, & day);
    uruu = 0;
    
    if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        uruu = 1;
    else
        ;
    wari = (float)year / mon / day;
    waridata = wari;
    wari = wari - waridata;
    
    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}