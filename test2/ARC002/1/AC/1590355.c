#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool Uru(int y);

int main(void){
	int y;
	
	while(1){
	if(scanf("%d", &y) != 1){
		scanf("%*s", &y);
		printf("数字を入力してください.\n");
	}else
		break;
	}

	if(Uru(y))
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}

bool Uru(int y){
	bool uru = false;

	if(y % 400 == 0){
		uru = true;
	}else if(y % 100 == 0){
	}else if(y % 4 == 0){
		uru = true;
	}

	return uru;
}