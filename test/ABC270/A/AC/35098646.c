#include <stdio.h>

int main(void){

	int a,b,ans=0;
	int aa[3]={0},bb[3]={0},cc[3]={1,2,4};
	scanf("%d %d",&a,&b);
	switch(a){
	case 1: aa[0]++; break;
	case 2: aa[1]++; break;
	case 3: aa[0]++; aa[1]++; break;
	case 4: aa[2]++; break;
	case 5: aa[0]++; aa[2]++; break;
	case 6: aa[2]++; aa[1]++; break;
	case 7: aa[0]++; aa[1]++; aa[2]++; break;
	}

	switch(b){
	case 1: bb[0]++; break;
	case 2: bb[1]++; break;
	case 3: bb[0]++; bb[1]++; break;
	case 4: bb[2]++; break;
	case 5: bb[0]++; bb[2]++; break;
	case 6: bb[2]++; bb[1]++; break;
	case 7: bb[0]++; bb[1]++; bb[2]++; break;
	}

	for(int i=0;i!=3;i++){
		if (aa[i]>0||bb[i]>0){
			ans+=cc[i];
		}
	}
	printf("%d\n",ans);
	return 0;
}
