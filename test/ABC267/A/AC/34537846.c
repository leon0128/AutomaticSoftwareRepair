#include <stdio.h>
#include <string.h>
#define N 10

typedef struct{
	char str[N];
	int day;
} Data;

int main(void){
	char str[N];
	Data data[5] = {{"Monday", 5}, {"Tuesday", 4}, {"Wednesday", 3}, 
									{"Thursday", 2}, {"Friday", 1}};
	scanf("%s", str);

	for(int i = 0; i < 5; i++){
		if(strcmp(str, data[i].str) == 0){
			printf("%d\n", data[i].day);
		}
	}
	
	return (0);
}