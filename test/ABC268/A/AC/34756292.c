#include <stdio.h>

int main(){
	int a[4] = {0};
	int i,x,m;
	int b[4] = {0};
	for(i=0;i<5;++i){
		scanf("%d",&a[i]);
	}
	m=5;
	for(i=0;i<5;++i){
		if(i==1&&a[0] == a[1]){
			--m;
		}
		if(i==2&&(a[0] == a[2]||a[1] == a[2])){
			--m;
		}
		if(i==3&&(a[0] == a[3]||a[1] == a[3]||a[2]==a[3])){
			--m;
		}
		if(i==4&&(a[0] == a[4]||a[1] == a[4]||a[2] == a[4]||a[3] == a[4])){
			--m;
		}
	}
	printf("%d\n",m);
	return 0;
}