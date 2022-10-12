#include<stdio.h>


int main()
{
    int N;
    int y;
    int x;

    scanf("%d", &N);
        
    y=N/16;
    x=N%16;
    if(y>9){
        switch(y)
        {
            case 10:
                y="A";
                break;
            case 11:
                y="B";
                break;
            case 12:
                y="C";
                break;
            case 13:
                y="D";
                break;
            case 14:
                y="E";
                break;
            case 15:
                y="F";
                break;
            default:
                break;
        }
    }

    if(x>9){
        switch(x)
        {
            case 10:
                y="A";
                break;
            case 11:
                y="B";
                break;
            case 12:
                y="C";
                break;
            case 13:
                y="D";
                break;
            case 14:
                y="E";
                break;
            case 15:
                y="F";
                break;
            default:
                break;
        }
    }

    printf("%d%d",y,x);

    return 0;
}