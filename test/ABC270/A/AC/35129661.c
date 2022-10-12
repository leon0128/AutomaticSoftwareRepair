#include<stdio.h>
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    if(a>=b){
        if(a==0){
            printf("0\n");
        }
        else if(a==1){
            printf("1\n");
        }else if(a==2){
            if(b==0){
                printf("2\n");
            }
            else if(b==1){
                printf("3\n");
            }else{
                printf("2\n");
            }
        }else if(a==3){
            printf("3\n");
        }else if(a==4){
            if(b==0){
                printf("4\n");
            }
            else if(b==1){
                printf("5\n");
            }else if(b==2){
                printf("6\n");
            }else if(b==3){
                printf("7\n");
            }else{
                printf("4\n");
            }
        }else if(a==5){
            if(b==0){
                printf("5\n");
            }
            else if(b==1){
                printf("5\n");
            }else if(b==2){
                printf("7\n");
            }else if(b==3){
                printf("7\n");
            }else if(b==4){
                printf("5\n");
            }else{
                printf("5\n");
            }
        }else if(a==6){
            if(b==0){
                printf("6\n");
            }
           else if(b==1){
                printf("7\n");
            }else if(b==2){
                printf("6\n");
            }else if(b==3){
                printf("7\n");
            }else if(b==4){
                printf("6\n");
            }else if(b==5){
                printf("7\n");
            }else{
                printf("6\n");
            }
        }else{
            printf("7\n");
        }
    }else{
        int tmp=a;
        a=b;
        b=tmp;
        if(a==1){
            printf("1\n");
        }else if(a==2){
            if(b==1){
                printf("3\n");
            }else{
                printf("2\n");
            }
        }else if(a==3){
            if(b==1){
                printf("3\n");
            }else if(b==2){
                printf("3\n");
            }else{
                printf("3\n");
            }
        }else if(a==4){
            if(b==1){
                printf("5\n");
            }else if(b==2){
                printf("6\n");
            }else if(b==3){
                printf("7\n");
            }else{
                printf("4\n");
            }
        }else if(a==5){
            if(b==1){
                printf("5\n");
            }else if(b==2){
                printf("7\n");
            }else if(b==3){
                printf("7\n");
            }else if(b==4){
                printf("5\n");
            }else{
                printf("5\n");
            }
        }else if(a==6){
            if(b==1){
                printf("7\n");
            }else if(b==2){
                printf("6\n");
            }else if(b==3){
                printf("7\n");
            }else if(b==4){
                printf("6\n");
            }else if(b==5){
                printf("7\n");
            }else{
                printf("6\n");
            }
        }else{
            printf("7\n");
        }
    }
    return 0;
}