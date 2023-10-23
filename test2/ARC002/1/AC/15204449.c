#include <stdio.h>
int main(int argc, char **argv) {
	int y;
	scanf("%i", &y);
	printf("%s\n", y % 400 == 0 || y % 4 == 0 && y % 100 != 0 ? "YES" : "NO");
	return 0;
}
