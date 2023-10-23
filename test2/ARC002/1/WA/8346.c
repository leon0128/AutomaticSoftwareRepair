#include <stdio.h>
 
int getDays(int y, int m){
if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
return 31;
if(m == 4 || m == 6 || m == 9 || m == 11)
return 30;
if(m == 2)
if(y % 400 == 0 || (y%4==0 && y%100 != 0))
return 29;
else
return 28;
return -1;
}
int main(void){
int y = 0, m=0, d=0, i, j ,k;
char nu;
scanf("%4d%c%02d%c%02d", &y, &nu, &m, &nu, &d);
j=m;k=d;
for(i=y;i<10000;i++){
for(;j<=12;j++){
for(;k<=getDays(i, j);k++){
if((i % j == 0) && ((i / j) % k == 0)){
printf("%d/%02d/%02d\n", i, j, k);
return 0;
}
}
k = 1;
}
j = 1;
}
return 0;
}
