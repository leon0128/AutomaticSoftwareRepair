#include <stdio.h>
#include <string.h>

int main(void) {
    char s[20] = {0}, weekday[5][20] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    scanf("%s", s);

    for (int i = 0; i < 5; i += 1) {
        if (strcmp(s, weekday[i]) == 0) {
            printf("%d", 5 - i);
            break;
        }
    }

    return 0;
}