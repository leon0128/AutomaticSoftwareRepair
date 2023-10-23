#include <stdio.h>
#include <stdlib.h>
int main() {
int a, i;
scanf("%d", &a);
if (a % 4 == 0) {
if (a % 400 == 0) {
printf("YES\n");
exit(0);
} else if (a % 100 == 0) {
printf("NO\n");
exit(0);
} printf("YES\n");
exit(0);
}else if (a % 4 == 0 && a % 400 == 0) {
printf("YES\n");
} else {
printf("NO\n");
} return 0;
}