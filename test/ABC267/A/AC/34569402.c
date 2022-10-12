#include<stdio.h>

int main()
{
    char S[15];
    
    
    scanf("%s",S);
    
    if(S[0]=='M')
        printf("5");
   else if(S[0]=='T' && S[1]=='u')
        printf("4"); 
    else if(S[0]=='W')
        printf("3");  
     else if(S[0]=='T')
        printf("2"); 
        
    else if(S[0]=='F')
        printf("1");  
        
    return 0;
}