
#include <stdio.h>

char solve(char* input){
    int i=0;
    while(input[i]!='\0'){
        i++;
    }
    return input[((i+1)/2)-1];
}

int main(int argc, char **argv){
    char* input = argv[1];
    solve(input);
    return 0;
}