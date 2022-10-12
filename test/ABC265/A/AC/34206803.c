#include<stdio.h>
#include<string.h>
#include<math.h>
#define NUMBER 5

int i, j; //ループ用
void vswap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void vsort(int n, int a[])
{
	for (i = 0; i < n - 1; i++)
		for (j = n - 1; j > i; j--)
			if (a[j - 1] > a[j])
				vswap(&a[j - 1], &a[j]);
}

void cswap(char w[], char z[])
{
	char temp[100];
	strcpy(temp, w);
	strcpy(w, z);
	strcpy(z, temp);
}

void csort(int n, char s[][NUMBER])
{
	for (i = 0; i < n - 1; i++)
		for (j = n - 1; j > i; j--)
			if (strcmp(s[j - 1], s[j]) > 0)
				cswap(s[j - 1], s[j]);
}

int main(void)
{
	int count = 0; //カウント用
	int x, y, n;
	
	scanf("%d %d %d",&x,&y,&n);

	int ans1, ans2;

	ans1 = n / 3;
	if (n % 3 == 0) {
		ans1 = ans1 * y;
	}
	else if (n % 3 == 1) {
		ans1 = ans1 * y + x;
	}
	else {
		ans1 = ans1 * y + x + x;
	}

	ans2 = x * n;
	if (ans1 <= ans2) {
		printf("%d", ans1);
	}
	else {
		printf("%d", ans2);
	}

	return 0;
}
