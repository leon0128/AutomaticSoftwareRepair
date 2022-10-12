#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    int len;
    char substr[100];

    scanf("%s",substr);
    len = strlen(substr);
    len = (len+1)/2;

    char *str = malloc(len);

    /*printf("len = %d\n",len);*/
    printf("%c\n",substr[len-1]);
    
    /*free(str)
    exit(EXIT_SUCCESS);*/




    /*printf("%s\n %d\n",substr,len); */
  
}