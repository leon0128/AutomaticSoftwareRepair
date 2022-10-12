#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define l(x) (x<<1)
#define r(x) ((x<<1)|1)
#define LL long long
#define INF 0x3f3f3f3f

int a,b,c,d;

int Abs(int x){return (x<0)?-x:x;}
int Min(int a,int b){return (a<b)?a:b;}
int Max(int a,int b){return (a>b)?a:b;}

int read(){
    int p=0,f=1;    char    c=getchar();
    while (c<48||c>57)    {if (c=='-')    f=-1;    c=getchar();}
    while (c>=48&&c<=57)    p=(p<<1)+(p<<3)+c-48,c=getchar();
    return p*f;
}

void write(int x) {
    static int sta[35];
    if (x<0)    {putchar('-');    x=-x;}
    register int top=0;
    do{
        sta[top++]=x%10,x/=10;
    }while (x);
    while (top) putchar(sta[--top]+48);
}

int cmp(int a, int b){
	return a<=b;
}

void Merge(int a[], int b[], int low, int high, int (*cmp)(int,int)){
	int mid = (low + high) >> 1, q = low, w = ((low + high) >> 1) + 1, e = low, i = 0;
	if (low == high) return;
	Merge(a, b, low, mid, cmp);	Merge(a, b, mid+1, high, cmp);
	while (q<=mid && w<=high)
		b[e++] = cmp(a[q], a[w])?a[q++]:a[w++];
	while (q <= mid)	b[e++] = a[q++];
	while (w <= high)	b[e++] = a[w++];
	for (i=low;i<=high;i++)	a[i] = b[i];
}

int main(){
	#ifdef __Marvolo
	freopen("zht.in","r",stdin);
	freopen("zht.out","w",stdout);
	#endif
	a=read();	b=read();
	c=read();	d=read();
	printf("%d\n", (a+b)*(c-d));
	puts("Takahashi");
    return 0;
}
