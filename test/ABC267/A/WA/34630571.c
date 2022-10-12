#include <stdio.h>
#include <string.h>

int main() {
	char s[100];

	//scanf_s("%s", s,100);//文字列のとき，第２引数にサイズを書く

	if (memcmp(s, "Monday", sizeof("Monday")) == 0) {//配列が一致してたら0を返す　第3引数によってどこまで比較するのかのサイズを指定
		printf("5\n");
	}
	else if (memcmp(s, "Tuesday", sizeof("Tuesday")) == 0) {
		printf("4\n");
	}
	else if (memcmp(s, "Wednesday", sizeof("Wednesday")) == 0) {
		printf("3\n");
	}
	else if (memcmp(s, "Thursday", sizeof("Thursday")) == 0) {
		printf("2\n");
	}
	else {
		printf("1\n");
	}
}