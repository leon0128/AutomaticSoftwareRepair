#include <stdio.h>

/* 値を入れ替える関数 */
void swap (int *x, int *y) {
  int temp;    // 値を一時保存する変数

  temp = *x;
  *x = *y;
  *y = temp;
}

/* pushdouwn操作 */
void pushdown (int array[], int first, int last) {
  int parent = first;   // 親
  int child = 2*parent;   // 左の子
  while (child <= last) {
    if ((child < last) && (array[child] < array[child+1])) {
       child++;   // 右の子の方が大きいとき、右の子を比較対象に設定
    }
    if (array[child] <= array[parent]) { break; }   // ヒープ済み
    swap(&array[child], &array[parent]);
    parent = child;
    child = 2* parent;
  }
}

/* ヒープソート */
void heap_sort (int array[], int array_size) {
  int i;

  for (i = array_size/2; i >= 1; i--) {
    pushdown(array, i, array_size);   // 全体をヒープ化
  }
  for (i = array_size; i >= 2; i--) {
    swap(&array[1], &array[i]);   // 最大のものを最後に
    pushdown(array, 1, i-1);   // ヒープ再構築
  }
}


int main(void){
    int N,M;
    scanf("%d %d",&N,&M);
    int A[N],array[N+1];
    for(int i=0; i<N; i++){
        scanf("%d ", &A[i]);
    }

    for(int i=0; i<N; i++){
        array[i]=A[i];
    }
    heap_sort(array, N);
    int max=array[N-1];


    
    long long M_sum=M*(M+1)*(1/2);
    long long sum,ans;
    for(int i=0; i<N-M+1; i++){
        sum=0;
        for(int j=0; j<M; j++){
            sum += (j+1)*A[i+j];
             M_sum-=j-1;

            if(i!=0&&(sum<ans-max*(M_sum))){
                break;
            }
            //printf("%lld\n",sum);
        }
        if(i==0||sum > ans){
                ans=sum;
        }
    }
    
    printf("%lld\n",ans);
}
