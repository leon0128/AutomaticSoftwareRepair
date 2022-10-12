#include<stdio.h>
#include<string.h>
#include<math.h>

int main (void){
	
	int a,b;
	int arr[3]={0};
	scanf("%d %d",&a,&b);
	
	if(a==1){
		arr[0]=1;
	}else if(a==2){
		arr[1]=1;
	}else if(a==3){
		arr[0]=1;
		arr[1]=1;
	}else if(a==4){
		arr[2]=1;
	}else if(a==5){
		arr[0]=1;
		arr[2]=1;
	}else if(a==6){
		arr[1]=1;
		arr[2]=1;
	}else if(a==7){
		arr[0]=1;
		arr[1]=1;
		arr[2]=1;
	}
	if(b==1){
		arr[0]=1;
	}else if(b==2){
		arr[1]=1;
	}else if(b==3){
		arr[0]=1;
		arr[1]=1;
	}else if(b==4){
		arr[2]=1;
	}else if(b==5){
		arr[0]=1;
		arr[2]=1;
	}else if(b==6){
		arr[1]=1;
		arr[2]=1;
	}else if(b==7){
		arr[0]=1;
		arr[1]=1;
		arr[2]=1;
	}
	
//	int i;
//	for(i=0;i<3;i++){
//		printf("%d",arr[i]);
//	}
	int s=0;
	if(arr[0]==1){
		s+=1;
	}
	if(arr[1]==1){
		s+=2;
	}
	if(arr[2]==1){
		s+=4;
	}
	printf("%d",s);
}