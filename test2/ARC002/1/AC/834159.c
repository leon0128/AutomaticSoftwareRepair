#include <stdio.h>
#include <math.h>
#define swap(a, b) a^=b^=a^=b
	
main(void){	
	int m, v, n;
	

	scanf("%d", &m);
	
    if(m%4 == 0 && m%100 == 0){
		if(m%400 == 0) printf("YES\n");
		else printf("NO\n");
    } else if(m%4 == 0 && m%100 != 0) printf("YES\n");
    else printf("NO\n");
    return 0;
}
