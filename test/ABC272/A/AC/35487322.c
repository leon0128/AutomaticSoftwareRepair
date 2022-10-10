#include <stdio.h> 
#include <stdlib.h>
main(){
	int length;
	int total = 0;
	scanf("%d",&length);
	int iArray[length];	
	int i;
	for(i=0;i<length;i++){
		scanf("%d",&iArray[i]);
	    total = total + iArray[i];
	}
	printf("%d", total);
	system("pause");
} 