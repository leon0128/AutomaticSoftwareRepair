#include<stdio.h>


int main()
{
    int N;
    int y;
    int x;
    char m;
    char l;

    scanf("%d", &N);
        
    y=N/16;
    x=N%16;
    if(y>9){
        switch(y)
        {
            case 10:
                m='A';
                break;
            case 11:
                m='B';
                break;
            case 12:
                m='C';
                break;
            case 13:
                m='D';
                break;
            case 14:
                m='E';
                break;
            case 15:
                m='F';
                break;
            default:
                break;
        }
    }

    if(x>9){
        switch(x)
        {
            case 10:
                l='A';
                break;
            case 11:
                l='B';
                break;
            case 12:
                l='C';
                break;
            case 13:
                l='D';
                break;
            case 14:
                l='E';
                break;
            case 15:
                l='F';
                break;
            default:
                break;
        }
    }
    if(y<10&&x<10)
        printf("%d%d",y,x);
    else if(y>9 && x<10)
        printf("%c%d ",m,x);
    else printf("%d%c",y,l);
    return 0;
}