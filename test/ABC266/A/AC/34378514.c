#include<stdio.h>
int main(){
char str[10000];
scanf("%s",str);
int len;
len=strlen(str);

  if(len==1)
        printf("%c\n",str[len-1]);
  else
    printf("%c\n",str[len/2]);



return 0;
}
