// nth_element(v.begin(),v.begin()+1,v.end(),greater<int>()); //o(n) on avg;second greatest element ;
// nth_element(v.begin(),v.begin()+1,v.end()); //o(n) on avg;second smallest element ;

// -------------------------------------------------------------------------------
// // for ordered set 
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds; 

// #define pbds tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> 
// pbds Set;                      //less_equal  for multiset

// 1. Set.order_of_key(Val) -> this gives the number of integers strictly less than Val in the Set.// in logn
// 2. Set.find_by_order(k-1) -> this will give the pointer to kth smallest number. // in logn 

// these 2 are extra thing that we can do efficiently from the normal set ; 



// -------------------------------------------------------------------------------

int main(){
      long decimalnum, quotient, remainder;
    int i, j = 0;
    char hexadecimalnum[100];
 
    scanf("%ld", &decimalnum);
 
    quotient = decimalnum;
 
    while (quotient != 0)
    {
        remainder = quotient % 16;
        if (remainder < 10)
            hexadecimalnum[j++] = 48 + remainder;
        else
            hexadecimalnum[j++] = 55 + remainder;
        quotient = quotient / 16;
    }
       if(j==1)  printf("0");
    for (i = j; i >= 0; i--)
            printf("%c", hexadecimalnum[i]);
    return 0;
}