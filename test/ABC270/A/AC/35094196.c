//AtCoder用
//プリプロセッサ系
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MOD 1000000007
#define INFTY 2147483646
#define DEBUG 1
#define END printf("\n");return 0;
#define QS09(how_data,data) qsort(data,how_data,sizeof(long),(int (*)(const void *,const void *))qsort_09);
#define QS90(how_data,data) qsort(data,how_data,sizeof(long),(int (*)(const void *,const void *))qsort_90);
//↓この2つはCE対策のために適当にdefineしてるだけだから使う際は「構造体クイックソート設定」をコピペ
#define ST_NAME _GD
#define KEY_NAME how_vertex

#define ST09(how_data,data) qsort(data,how_data,sizeof(ST_NAME),(int (*)(const void *,const void *))qsort_st09);
#define ST90(how_data,data) qsort(data,how_data,sizeof(ST_NAME),(int (*)(const void *,const void *))qsort_st90);
#define In(a) long a;scanf("%ld",&a);
#define Out(a) printf("%ld\n",a);
#define dprintf if(DEBUG)printf
#define ifdebug if(DEBUG)
#define MAKE_ARRAY_DATA In(how_data);long data[how_data];input_array(how_data,data);
#define update_max(a,b) a=(a>b?a:b);
#define update_min(a,b) a=(a<b?a:b);
#define input_long(A) int A;scanf("%d",&A)

//構造体クイックソート設定 使用時はmainに以下をコピペ、ST_NAMEとKEY_NAMEを書き換え
/*
    #undef ST_NAME
    #undef KEY_NAME
    #define ST_NAME _GD
    #define KEY_NAME how_vertex
    ST09(how_data,data);
*/


//関数
void input_array(long how_data,long *data); //配列の入力
void output_array(long how_data,long *data); //配列の出力
void input_array2(long first , long second , long data[][3]); //2次元配列の入力
void format_array(long how_data ,long *data,long what); //配列初期化
long get_random(long min, long max); //min～max範囲の乱数生成
long factorial(long n); //n!
long fibonacci(long n); //n番目のフィボナッチ
int qsort_09(const int *sys1 , const int *sys2);
int qsort_90(const int *sys1 , const int *sys2);
int qsort_st09(const void *c1, const void *c2);
int qsort_st90(const void *c1, const void *c2);
long sel_max(long a , long b);
long sel_min(long a , long b);
long array_max(long how_data,long *data);
long array_min(long how_data,long *data);
long array_search(long how_data,long *data,long what);
long can_DP(long how_data,long *data,long how_can,bool *can);
long array_sum(long how_data,long *data);
long Leven_dist(char *now , char *target);
long get_digit(long target);
long rounding(double target);
long roundingdown(double target);
long roundingup(double target);
long ncr(long n , long r);
long npr(long n , long r);
long nhr(long n , long r);
int fifw(long add,long *data);
long fifr(long *data);
void GRAPH_input(void);
void GRAPH_dfs(long now);
bool check_prime(long target);
long get_lcm(long a,long b);
long get_gcd(long a,long b);
void digit_cut(int how_data,char *s,int *i);  //文字列として与えられた数列を1桁ずつ分割
//グローバル変数一覧
long fifo[1000]={0};//fifo[0]はデータ件数
long loop1,loop2,loop3,loop4,loop5;
long g_ans=0; //answerグローバル変数用

typedef struct{
    long how_vertex;
    long how_edge;
    long edge_data[1000][2];
    bool aleady_searched_vertex[500];
    bool all_searched;
} _GD;//GraphData

_GD GRAPH={0,0,{{0}},{0},0};

char c_temp;
//loop5 loop4 loop3 loop2 loop1 input_long
//--------------ここから

int main(void){
    int a,b;
    scanf("%d%d",&a,&b);
    bool t1,t2,t3;
    t1=0;t2=0;t3=0;
    if(a>=4){
        t3=1;
        a-=4;
    }
    if(a>=2){
        t2=1;
        a-=2;
    }
    if(a>=1){
        t1=1;
        a-=1;
    }
    if(b>=4){
        t3=1;
        b-=4;
    }
    if(b>=2){
        t2=1;
        b-=2;
    }
    if(b>=1){
        t1=1;
        b-=1;
    }
    printf("%d\n",t1*1+t2*2+t3*4);
    return 0;
}




//--------------ここまで
 
void input_array(long how_data,long *data){
    long loop;
    for(loop=0;loop<how_data;loop++){
        scanf("%ld",&data[loop]);
    }
    return ;
}
void output_array(long how_data,long *data){
    long loop;
    for(loop=0;loop<how_data;loop++){
        printf("%ld",data[loop]);
        if(loop!=how_data-1){
            printf(" ");
        }
    }
    printf("\n");
    return ;
}
void input_array2(long first,long second,long data[][3]){
    long loopA,loopB;
    for(loopA=0;loopA<first;loopA++){
        for(loopB=0;loopB<second;loopB++){
            scanf("%ld",&data[loopA][loopB]);
        }
    }
    return ;
}
void format_array(long how_data ,long *data,long what){
    long loopA;
    for(loopA=0;loopA<how_data;loopA++){
        data[loopA]=what;
    }
    return ;
}
long get_random(long min, long max){   //指定の範囲から乱数を1つ返すやつ
    //srand((unsigned int)time(0));   //現在時刻で疑似乱数初期化
    rand();rand();rand();rand();    //乱数を空打ち
    return (rand()%(max+1-min))+min;
}
long factorial(long n){//n!のMOD10^9+7を返すやつ
    unsigned long long int ret=1;
    for(long i=1;i<=n;i++)ret=(ret*i)%1000000007;
    return (long)ret;
}
int qsort_09(const int *sys1 , const int *sys2){ //小さいのが上にくるやつ
    //qsort(data,how_data,sizeof(long),(int (*)(const void *,const void *))qsort_09);
    if(*sys1<*sys2){
        return -1;
    }else if(*sys1==*sys2){
        return 0;
    }else{
        return 1;
    }
}
int qsort_90(const int *sys1, const int *sys2){ //大きいのが上にくるやつ
    //qsort(data,how_data,sizeof(long),(int (*)(const void *,const void *))qsort_90);
    if(*sys1<*sys2){
        return 1;
    }else if(*sys1==*sys2){
        return 0;
    }else{
        return -1;
    }
}
int qsort_st09(const void *c1, const void *c2){
    ST_NAME hikaku1= *(ST_NAME *)c1;
    ST_NAME hikaku2= *(ST_NAME *)c2;
    return hikaku1.KEY_NAME - hikaku2.KEY_NAME;
}
int qsort_st90(const void *c1, const void *c2){
    ST_NAME hikaku1= *(ST_NAME *)c1;
    ST_NAME hikaku2= *(ST_NAME *)c2;
    return hikaku2.KEY_NAME - hikaku1.KEY_NAME;
}
long fibonacci(long n){
    switch(n){
        case 0:return 0;
        case 1:return 1;
        default :return fibonacci(n-1)+fibonacci(n-2);
    }
}
long sel_max(long a,long b){
    if(a>b)return a;
    return b;
}
long sel_min(long a,long b){
    if(a>b)return b;
    return a;
}

long can_DP(long how_data,long *data,long how_can,bool *can){//Typical DP Contest A
    //data内で組み合わせられる和をcanに0 or 1で入れる
    //返り値はパターン数
    long loopA,loopB;
    long ret=0;
    for(loopA=0;loopA<how_can;loopA++){//初期化
        can[loopA]=0;
    }
    can[0]=1;//絶対にありえる
    for(loopA=0;loopA<how_data;loopA++){
        for(loopB=how_can-1;loopB>=0;loopB--){
            if(can[loopB]==1 && loopB+data[loopA]<how_can){
                can[loopB+data[loopA]]=1;
            }
        }
    }
    for(loopA=0;loopA<how_can;loopA++){
        if(can[loopA]==1){
            ret++;
        }
    }
    return ret;
}
long array_max(long how_data,long *data){
    long loop;
    long ret=data[0];
    for(loop=0;loop<how_data;loop++){
        if(ret<data[loop])ret=data[loop];
    }
    return ret;
}
long array_min(long how_data,long *data){
    long loop;
    long ret=data[0];
    for(loop=0;loop<how_data;loop++){
        if(ret>data[loop])ret=data[loop];
    }
    return ret;
}
long array_sum(long how_data,long *data){
    long ret=0;
    long loop;
    for(loop=0;loop<how_data;loop++){
        ret+=data[loop];
    }
    return ret;
}
long array_search(long how_data,long *data,long what){
    long loop;
    for(loop=0;loop<how_data;loop++){
        if(data[loop]==what){
            return loop;
        }
    }
    return -1;
}
long Leven_dist(char *now , char *target){
    long loopA,loopB;
    //レーベンシュタイン距離を求める
    // 参考文献
    // http://nw.tsuda.ac.jp/class/algoB/c13.html  (アルゴリズム理解)
    // http://d.hatena.ne.jp/ohnishiakira/20090809/1249845529  (実装)
    long len_now=strlen(now)+1;
    long len_target=strlen(target)+1;
    long d[len_now][len_target]; //計算用
    for(loopA=0;loopA<len_now;loopA++) d[loopA][0]=loopA;
    for(loopA=0;loopA<len_target;loopA++) d[0][loopA]=loopA;
    for(loopA=1;loopA<len_now;loopA++){
        for(loopB=1;loopB<len_target;loopB++){
            long cost=(now[loopA-1]==target[loopB-1] ? 0:1);
            d[loopA][loopB]=sel_min(sel_min(d[loopA-1][loopB]+1,d[loopA][loopB-1]+1),d[loopA-1][loopB-1]+cost);
        }
    }
    return d[len_now-1][len_target-1];
}
long get_digit(long target){
    return (long)(log10(target)+1);
}
long ncr(long n , long r){
    //パスカルの三角形
    long loopA,loopB;
    long pascal[100][102]={{0}};
    pascal[1][0]=1;
    pascal[1][1]=1;
    for(loopA=2;loopA<100;loopA++){
        pascal[loopA][0]=1;
        for(loopB=1;loopB<loopA;loopB++){
            pascal[loopA][loopB]=pascal[loopA-1][loopB-1]+pascal[loopA-1][loopB];
        }
        pascal[loopA][loopA]=1;
    }
    return pascal[n][r];
}
long npr(long n, long r){
    return ncr(n,r)*factorial(r);
}
long nhr(long n , long r){
    return ncr(n+r-1,r);
}
long rounding(double target){
    return (long)target+0.50;
}
long roundingup(double target){
    return (long)ceil(target);
}
long roundingdown(double target){
    return (long)floor(target);
}
int fifw(long add,long *data){
    data[data[0]+1]=add;
    data[0]++;
    return data[0]; //現在のデータ件数を返す
}
long fifr(long *data){
    long ret=data[1];
    data[0]--;
    for(int i=1;i<999;i++){
        data[i]=data[i+1];
    }
    return ret;
}
void GRAPH_input(void){
    scanf("%ld %ld\n",&GRAPH.how_vertex,&GRAPH.how_edge);
    for(long loopA=0;loopA<GRAPH.how_edge;loopA++){
        scanf("%ld %ld\n",&GRAPH.edge_data[loopA][0],&GRAPH.edge_data[loopA][1]);
    }
    return;
}
void GRAPH_dfs(long now){
    GRAPH.aleady_searched_vertex[now]=1;
    for(int loopA=0;loopA<GRAPH.how_edge;loopA++){
        if(GRAPH.edge_data[loopA][0]==now && GRAPH.aleady_searched_vertex[GRAPH.edge_data[loopA][1]]==0){
            GRAPH_dfs(GRAPH.edge_data[loopA][1]);
        }
        if(GRAPH.edge_data[loopA][1]==now && GRAPH.aleady_searched_vertex[GRAPH.edge_data[loopA][0]]==0){
            GRAPH_dfs(GRAPH.edge_data[loopA][0]);
        }
    }
    return ;
}
bool check_prime(long target){//素数判定、素数なら1
    if(target==2)return 1;
    if(target<=1 || target%2==0)return 0;
    for(int loopA=3;loopA<=sqrt(target)+1;loopA+=2)if(target%loopA==0)return 0;
    return 1;
}
long get_lcm(long a,long b){//最小公倍数
    return (a*b)/get_gcd(a,b);
}
long get_gcd(long a,long b){//最大公約数 参考：https://webkaru.net/clang/find-gcd-of-two-number/
    // a>b
    if(a<b){
        int tem=a;
        a=b;
        b=tem;
    }
    long r=a%b;
    while(r!=0){
        a=b;
        b=r;
        r=a%b;
    }
    return b;
}
void digit_cut(int how_data,char *s,int *i){
    for(int loopA=0;loopA<how_data;loopA++){
        i[loopA]=atoi(&s[loopA]);
    }
    return ;
}

