#include<stdio.h>

int main(void){
	int x, y, z, ret = 0;
    scanf("%d %d %d", &x, &y, &z);
    if(x * 3 < y){
    	y = x * 3;
    }
    ret += (z/3)*y;
    ret += (z%3)*x;
    printf("%d\n", ret);
}