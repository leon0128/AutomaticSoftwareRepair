#include <stdio.h>
#include <string.h>

int main(void)
{
	int i;
	char s[99];
	
	
	scanf("%s", s);
	
	i = strlen(s);
	if (i%2 == 0){
		while (1){
		scanf("%s", s);
		i = strlen(s);
		if (i%2 == 1){
			break;
		}
	    }
	}
	
	
	
	printf("%c\n", s[i/2]);
	return (0);
}