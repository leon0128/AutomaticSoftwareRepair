#include<stdio.h>
int main(){
    char a[101]={};
 

    int i=0;
    scanf("%s",a);
    (void)getchar();

    while(1){
        if(a[i]=='\0'){
            break;
        }
        ++i;
    }
    /*printf("%d\n",i);*/
    printf("%c",a[(i-1)/2]);
    return 0;
}