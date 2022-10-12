#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  OK = 1,
  NG = 0,
  INPUT_ROW_COUNT = 1,
  NUM_COUNT = 4,
  MAX_LEN = 32,
  FALSE = 0,
  TRUE = 1,
};


static int split_str2int(
  char   *str,
  int     num,
  char   *del,
  int    *split
)
{
  int   i   = 0;
  char *tmp = str;
  char *ptr = NULL;

  if (!str || !split || num < 0) {
    return NG;
  }

  tmp = strtok_r(tmp, del, &ptr);
  for (i = 0; i < num; i++) {
    char *end = NULL;
    int val = strtol(tmp, &end, 10);

    if (*end != '\0' && *end != '\n') {
      return NG;
    }
    split[i] = val;
    tmp = strtok_r(NULL, del, &ptr);
  }

  return OK;
}


static void main_logic(
  int num[]
)
{
  printf("%d\n", (num[0] + num[1]) * (num[2] - num[3]));
  printf("Takahashi\n");

  return;
}

int main(void)
{
  char  str[MAX_LEN] = { 0 };
  int   num[NUM_COUNT] = { 0 };
  char *tmp = NULL;
  int   i;

  tmp = fgets(str, MAX_LEN, stdin);
  split_str2int(str, 4, " ", num);

  main_logic(num);

  return 0;
}