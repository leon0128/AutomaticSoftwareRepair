#include <stdio.h>

int main(void){

	int a[5];
	int ans=1;
	for(int i=0;i!=5;i++){
		scanf("%d",&a[i]);
	}
	for(int j=1;j!=5;j++){
		ans++;
		for(int k=0;k!=j;k++){
			if(a[j]==a[k]){
				ans--;
				break;
			}
		}
	}

	printf("%d\n",ans);
	return 0;
}
