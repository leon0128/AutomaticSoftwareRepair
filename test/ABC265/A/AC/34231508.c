#include <stdio.h>
//using namespace std;
int main ()
{
    int a1, a3, n, i, j , m, x, y;
    //cin >> a1 >> a3 >> n;
    scanf ("%d%d%d", &a1, &a3, &n);
    if (n<3 || a1*3< a3)
    {
        x=a1*n;
    }
    else
    {
        y=n%3;
        m=n/3;
        x= m*a3 + y*a1;
    }
    //cout << x <<endl;
    printf ("%d", x);
    return 0;
}