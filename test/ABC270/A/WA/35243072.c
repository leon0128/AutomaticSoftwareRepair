#include <stdio.h>
#include <string.h>

int main(){
	int x,y,z;
	scanf("%d %d %d", &x, &y, &z);
	int ans=0;
	if(x>0){
		if(y<0){
			ans = x;
		}
		else{
			if(z>y) ans = -1;
			else{
				int f = z*2;
				if(f<0) f = -f;
				ans = f+x;
			} 
		}
	}
	else{
		if(y>0){
			ans = -x;
		}
		else{
			if(z<y) ans = -1;
			else{
				int f = z*2;
				if(f<0) f = -f;
				ans = f+(-x);
			} 
		}
	}
	printf("%d\n", ans);
	return 0;
}