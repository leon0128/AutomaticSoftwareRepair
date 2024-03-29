/*
 * main.c
 *
 *  Created on: 2020/03/28
 *      Author: family
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX(a,b) (a > b ? a : b)
#define MIN(a,b) (a > b ? b : a)
typedef long long int ll;
typedef unsigned long long int ull;

int sort_inc(const void *a, const void *b) { return (*(int*)a - *(int*)b);}
int sort_dec(const void* a, const void* b) { return (*(int*)b - *(int*)a);}
int sort_dec_ll(const void *a, const void *b) {
    ll da = *(ll*)a, db = *(ll*)b;    int val = 0;
    if(da > db) { val = -1; }
    else if (da == db) { val = 0; }
    else { val = 1; }
    return val;
}
int sort_inc_ll(const void *a, const void *b) {
    ll da = *(ll*)a, db = *(ll*)b;    int val = 0;
    if(da > db) { val = 1; }
    else if (da == db) { val = 0; }
    else { val = -1; }
    return val;
}
int sort_dic(const void *a, const void *b) {
    char *pa = (char *)a;    char *pb = (char *)b;    int i = 0, val = 0, N = 10;
    for (i = 0; i < N; i++) {
    	char da = pa[i], db = pb[i];
    	if (da == db) continue;
  		if (da > db) val = 1; else val = -1;
        break;
    }
    return val;
}

void yesno(int ans) {
	if (ans == 1) {	printf("Yes\n");
	} else {		printf("No\n");	}
	return;
}

void okng(int ans) {
	if (ans == 1) { printf("OK\n");
	} else { 		printf("NG\n");	}
	return;
}

int p1 = 1;
int p2 = 2;
int p3 = 4;
int main()
{
	int A = 0, B = 0;
	scanf("%d %d", &A, &B);
	int ans = 0;
	// 1 1, 1 2, 1 4, 2 4
	if (A == 1) {
		ans += 1;
		if (B%2 != 0) {
			B -= 1;
		}
	} else if (A == (2)) {
		ans += 2;
		if (B == 2) {
			B = 0;
		}
		if (B == 3) {
			B -= 2;
		}
		if (B == 6) {
			B -= 2;
		}
	} else if (A == (4)) {
		ans += 4;
		if (B == 4) {
			B = 0;
		}
		if (B == 5) {
			B -= 4;
		}
		if (B == 6) {
			B -= 4;
		}
	} else if (A == (1+2)) {
		ans += 3;
		if (B == 3) {
			B = 0;
		}
		if (B == 1) {
			B = 0;
		}
		if (B == 2) {
			B = 0;
		}
	} else if (A == (1+4)) {
		ans += 5;
		if (B == 5) {
			B = 0;
		}
		if (B == 1) {
			B = 0;
		}
		if (B == 4) {
			B = 0;
		}
	} else if (A == (2+4)) {
		ans += 6;
		if (B == 6) {
			B = 0;
		}
		if (B == 2) {
			B = 0;
		}
		if (B == 4) {
			B = 0;
		}
	} else if (A == (1+2+4)) {
		ans += 7;
		if (B == 7) {
			B = 0;
		}
	} else {
		ans += 0;
	}

	if (B == 1) {
		ans += 1;
	} else if (B == (2)) {
		ans += 2;
	} else if (B == (4)) {
		ans += 4;
	} else if (B == (1+2)) {
		ans += 3;
	} else if (B == (1+4)) {
		ans += 5;
	} else if (B == (2+4)) {
		ans += 6;
	} else if (B == (1+2+4)) {
		ans += 7;
	} else {
		ans += 0;
	}

	if (ans > 7) {
		ans = 7;
	}
	printf("%d\n", ans);
	//yesno(ans);
	//okng(ans);
	return 0;
}
