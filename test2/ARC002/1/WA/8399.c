#include<stdio.h>

int main(){
	int y;
	scanf("%d",&y);
	if((y%4==0)&&(y%100==0)&&(y%400==0)){ //全規則OK
				printf("YES\n");
	}
	else if(y%4==0){//1→○ 2→×　3→× または1→○　2→×　3→○
		 if((y%100!=0) &&(y%400!=0))
				printf("NO\n");
		 else if(((y%100!=0) &&(y%400==0)))
				printf("YES\n");
	}
	else if(y%4 != 0){	//1→×　2→○　3→×または1→×　2→○　3→○または1→×　2→×　3→○
		if((y%100==0) &&(y%400!=0))
			printf("NO\n");
		else if((y%100==0) &&(y%400==0))
			printf("YES\n");
		else if((y%100!=0) &&(y%400==0))
			printf("YES\n");
	}
	else	//どの規則も当てはまらない
		printf("NO\n");
	
	return 0;
}