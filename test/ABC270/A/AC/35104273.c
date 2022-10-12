#include <stdio.h>
int a,b,c,s[5],i;
int main(void){
    
    scanf("%d %d",&a,&b);
    c=0;
    if(a==1){
        s[1]=1;
    }else if(a==2){
        s[2]=2;
    }else if(a==3){
        s[1]=1; s[2]=2;
    }else if(a==5){
        s[1]=1; s[4]=4;
    }else if(a==4){
        s[4]=4;
    }else if(a==7){
        s[1]=1; s[2]=2;s[4]=4;
    }else if(a==0){
        s[0]=0;
    }else if(a==6){
        s[2]=2; s[4]=4;
    }
    
    
     
    if(b==1){
        s[1]=1;
    }else if(b==2){
        s[2]=2;
    }else if(b==3){
        s[1]=1; s[2]=2;
    }else if(b==5){
        s[1]=1; s[4]=4;
    }else if(b==4){
        s[4]=4;
    }else if(b==7){
        s[1]=1; s[2]=2;s[4]=4;
    }else if(b==0){
        s[0]=0;
    }else if(b==6){
        s[2]=2; s[4]=4;
    }
    for(i=0;i<5;i++){
        if(s[i]!=0){
            c+=s[i];
        }
    }
    printf("%d",c);
    
}
