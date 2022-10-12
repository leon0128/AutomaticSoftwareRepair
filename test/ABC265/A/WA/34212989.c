
/*import java.util.*;
class MyClass {
    public static void main(String args[]) {
     Scanner sc = new Scanner(System.in);
     long x = sc.nextLong();
     long y = sc.nextLong();
     long n = sc.nextLong();
     long ans =0;
     if(3*x>y)
     ans = y*(n/3) + x*(n%3);
     else
     ans = x*n;
      System.out.println(ans);
    }
}
*/
#include<stdio.h>
int main()
{
   long x;
  scanf("%l", &x);
     long y;
  scanf("%l", &y);
     long n;
  scanf("%l", &n);
  long ans =0;
  if(3*x>y)
  {
    ans = y*(n/3) + x*(n%3);
  }
  else
  {
    ans = x*n;
  }
  printf("%l", &ans);
  return 0;
}

 
