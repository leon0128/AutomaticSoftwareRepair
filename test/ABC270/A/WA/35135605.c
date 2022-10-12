#include<stdio.h>

int func(int a){
	if((a + 1) == 7){
		return 1;
	}
	if((a + 2) == 7 ){
		return 2;
	}
	if((a + 4) == 7 ){
		return 4;
	}

	return 0;
}

int main(){
	int A, B, C = 0;
	int i = 0;
	int a, b;

	scanf("%d", &A);
	void getch();
	scanf("%d", &B);

	a = func(A);
	b = func(B);

	if(a == 0){
		C += A;
	}
	if(b == 0 && A != B){
		C += B;
	}
	if(A == 7 || B == 7){
		C = 7;
	}

	if(a == b && a != 0 && b != 0){
		C = 7 - a;
	}
	else if(a == 1){
		if(b == 2){
			C = 2 + 4 + 1;
		}
		else if(b == 4){
			C = 2 + 4 +1;
		}
	}
	else if(a == 2){
		if(b==1){ 
			C = 1+4+2;
		}
		else if(b == 4){
			C = 1 + 4+2;
		}
	}
	else if(a == 4){C=7;}
	else if ( a == 0){
		if(b != 0){
			C = B;
		}
	}
	else if ( b == 0){
		if(a != 0){
			C = A;
		}
	}



	printf("%d\n", C);

	return 0;
}
