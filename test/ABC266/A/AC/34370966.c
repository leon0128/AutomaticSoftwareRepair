#include<stdio.h>
int main(){
  char s[1000010],i;
  scanf("%s",s);
  for(i=0;s[i];i++);
  printf("%c\n",s[i/2]);
  return 0;
}
