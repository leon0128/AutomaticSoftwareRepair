#include <stdio.h>

void QSort(int x[ ], int left, int right);
void Swap(int x[ ], int i, int j);

  /* クイックソートを行う */
void QSort(int x[ ], int left, int right)
{
    int i, j;
    int pivot;

    i = left;                      /* ソートする配列の一番小さい要素の添字 */
    j = right;                     /* ソートする配列の一番大きい要素の添字 */

    pivot = x[(left + right) / 2]; /* 基準値を配列の中央付近にとる */

    while (1) {                    /* 無限ループ */

        while (x[i] < pivot)       /* pivot より大きい値が */
            i++;                   /* 出るまで i を増加させる */

        while (pivot < x[j])       /* pivot より小さい値が */
            j--;                   /*  出るまで j を減少させる */
        if (i >= j)                /* i >= j なら */
            break;                 /* 無限ループから抜ける */

        Swap(x, i, j);             /* x[i] と x[j]を交換 */
        i++;                       /* 次のデータ */
        j--;
    }

    if (left < i - 1)              /* 基準値の左に 2 以上要素があれば */
        QSort(x, left, i - 1);     /* 左の配列を Q ソートする */
    if (j + 1 <  right)            /* 基準値の右に 2 以上要素があれば */
        QSort(x, j + 1, right);    /* 右の配列を Q ソートする */
}

  /* 配列の要素を交換する */
void Swap(int x[ ], int i, int j)
{
    int temp;

    temp = x[i];
    x[i] = x[j];
    x[j] = temp;
}



int main(void){

    int N;
    scanf("%d",&N);

    int A[N];
    for(int i=0; i<N; i++){
        scanf("%d", &A[i]);
    }
   
    int ans=0,fl=0;
        QSort(A, 0,N-1);
         for(int i=N; i>1; i--){
            for(int j=i-1; j>0; j--){
                ans=0;
                ans=A[i-1]+A[j-1];
            if(ans%2==0){
                fl++;
                break;
            }
            }
            if(fl>0){
                break;
            }
         }
         if(fl==0){
             ans=-1;
         }
    
    
    
    printf("%d\n",ans);
}

    

