#include<stdio.h>
#include<string.h>

int main(void){
    int num = 0;
    char S[10]={0};
    int judge = 1;

    // ポインタによる文字列の表現
    char *day[]={"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    // 曜日を入力してもらう
    gets(S);

    for(int i=0;i<5;i++){
        if(strcmp(S,day[i]) == 0){
            num = i;
            break;
        }
    }
    
    // 結果を出力
    // puts(1);     // ダブルクォーテーションで囲まないと
    printf("%d",5-num);

    return 0;
}