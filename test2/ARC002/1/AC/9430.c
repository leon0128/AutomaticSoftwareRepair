#include <stdio.h>
#include <time.h>
main(){
    int x;
    scanf("%d",&x);
    puts(dysize(x)&1?"NO":"YES");
    return 0;
}
