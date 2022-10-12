#include<stdio.h>
int main(){
	int XYN[3];
	scanf("%d %d %d", &XYN[0], &XYN[1], &XYN[2]);
	if(XYN[0] * 3 < XYN[1]){
		int ans = 0;
		ans = XYN[0] * XYN[2];
		printf("%d", ans);
	}else{
		int jyo = 0;
		jyo = ((XYN[2] / 3) * XYN[1]) + ((XYN[2] % 3) * XYN[0]);
		printf("%d", jyo);
	}
	return 0;
}