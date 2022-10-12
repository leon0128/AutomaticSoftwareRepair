#include<stdio.h>
int main(){
    int n,a[200000];
    long long m,i,r,z=0,p=0;
    scanf("%d%lld",&n,&m);
    for(i=0;i<n;i++)scanf("%d",&a[i]);
    for(i=0;i<m;i++){
        z+=(i+1)*a[i];
        p+=a[i];
    }
    r=z;
    for(i=m;i<n;i++){
        z=z-p+m*a[i];
        p=p+a[i]-a[i-m];
        if(r<z)r=z;
    }
    printf("%lld",r);
    return 0;
}