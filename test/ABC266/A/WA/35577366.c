#include <stdio.h>
#include <stdlib.h>

int main()
{
        char arr[1024];
        char a;
        int i,counter=0;

        fgets(arr,sizeof(arr),stdin);

        for(i=0;i<strlen(arr);i++)
                counter++;

        for(i=0;i<strlen(arr);i++)
        {
                if(i==(counter/2))
                        printf("%c\n",arr[i]);
        }
        return 0;
}
