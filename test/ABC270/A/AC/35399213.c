#include <stdio.h>
int main(){
	int a,b,p,q,r,s;
	p=1;
	q=2;
	r=4;
	s=0;
	scanf("%d %d",&a,&b);
	if (a==0&&b==0){
		printf("%d",s);
	}
	
if (a==0&&b==1){
	printf("%d",p);
}
if (a==0&&b==2){
	printf("%d",q);
}
if (a==0&&b==3){
	printf("%d",p+q);}
if (a==0&&b==4){
	printf("%d",r);}
if (a==0&&b==5){
	printf("%d",p+r);
}
if (a==0&&b==6){
	printf("%d",q+r);
	}	
if (a==0&&b==7)
{
	printf("%d",p+q+r);
}
if (a==1&&b==0){
	printf("%d",p);
}
if (a==1&&b==1){
	printf("%d",p);
}
if (a==1&&b==2){
	printf("%d",p+q);
}
if (a==1&&b==3){
	printf("%d",p+q);
}
if (a==1&&b==4){
	printf("%d",p+r);
}
if (a==1&&b==5){
	printf("%d",p+r);
}
if (a==1&&b==6){
	printf("%d",q+r+p);
}
if (a==1&&b==7){
	printf("%d",p+q+r);
}
if (a==2&&b==0){
	printf("%d",q);
}
if (a==2&&b==1){
	printf("%d",q+r);
}
if (a==2&&b==2){
	printf("%d",q);
}
if (a==2&&b==3){
	printf("%d",p+q);
}
if (a==2&&b==4){
	printf("%d",q+r);
}
if (a==2&&b==5){
	printf("%d",p+q+r);
}
if(a==2&&b==6){
	printf("%d",q+r);
}
if (a==2&&b==7){
	printf("%d",p+q+r);
}
if (a==3&&b==0){
	printf("%d",p+q);
}
if (a==3&&b==1){
	printf("%d",p+q);
}
if (a==3&&b==2){
	printf("%d",p+q);
}
if (a==3&&b==3){
	printf("%d",p+q);
}
if (a==3&&b==4){
	printf("%d",p+q+r);
}
if (a==3&&b==5){
	printf("%d",p+q+r);
}
if(a==3&&b==6){
	printf("%d",p+q+r);
}
if (a==3&&b==7){
	printf("%d",p+q+r);
}
if (a==4&&b==0){
	printf("%d",r);
}
if (a==4&&b==1){
	printf("%d",r+p);
}
if (a==4&&b==2){
	printf("%d",r+q);
}
if (a==4&&b==3){
	printf("%d",p+q+r);
}
if (a==4&&b==4){
	printf("%d",r);
}
if (a==4&&b==5){
	printf("%d",p+q+r);
}
if (a==4&&b==6){
	printf("%d",q+r);
}
if (a==4&&b==7){
	printf("%d",p+q+r);
}
if (a==5&&b==0){
	printf("%d",p+r);
}
if (a==5&&b==1){
	printf("%d",p+r);
}
if (a==5&&b==2){
	printf("%d",p+q+r);
}
if (a==5&&b==3){
	printf("%d",p+q+r);
}
if (a==5&&b==4){
	printf("%d",p+r);
}
if (a==5&&b==5){
	printf("%d",p+r);
}
if (a==5&&b==6){
	printf("%d",p+q+r);
}
if (a==5&&b==7){
	printf("%d",p+q+r);
}
if (a==6&&b==0){
	printf("%d",q+r);
}
if (a==6&&b==1){
	printf("%d",p+q+r);
}
if (a==6&&b==2){
	printf("%d",q+r);
}
if (a==6&&b==3){
	printf("%d",p+q+r);
}
if (a==6&&b==4){
	printf("%d",q+r);
}
if (a==6&&b==5){
	printf("%d",p+q+r);
}
if (a==6&&b==6){
	printf("%d",q+r);
}
if (a==6&&b==7){
	printf("%d",p+q+r);
}
if (a==7&&b==0){
	printf("%d",p+q+r);
}
if (a==7&&b==1){
	printf("%d",p+q+r);
}
if (a==7&&b==2){
	printf("%d",p+q+r);
}
if (a==7&&b==3){
	printf("%d",p+q+r);
}
if (a==7&&b==4){
	printf("%d",p+q+r);
}
if (a==7&&b==5){
	printf("%d",p+q+r);
}

if (a==7&&b==7){
	printf("%d",p+q+r);
}
return 0;
}