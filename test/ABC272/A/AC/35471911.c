#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

enum {
  OK = 1,
  NG = 0,
  NUM_COUNT = 100,
  MAX_LEN = 400,
};


static int32_t split_str2int(
  char     *str,
  int32_t   num,
  char     *del,
  int32_t  *split
)
{
  int32_t i = 0;
  char *tmp = str;
  char *ptr = NULL;

  if (!str || !split || num < 0) {
    return NG;
  }

  tmp = strtok_r(tmp, del, &ptr);
  for (i = 0; i < num; i++) {
    char *end = NULL;
    int32_t val = strtol(tmp, &end, 10);

    if (*end != '\0' && *end != '\n') {
      return NG;
    }
    split[i] = val;
    tmp = strtok_r(NULL, del, &ptr);
  }

  return OK;
}


static void main_logic(
  int32_t n,
  int32_t num[]
)
{
  int32_t i;
  int32_t sum = 0;

  for (i = 0; i < n; i++) {
    sum += num[i];
  }

  printf("%d\n", sum);

  return;
}


int32_t main(void)
{
  char      str[MAX_LEN]   = { 0 };
  int32_t   num[NUM_COUNT] = { 0 };
  char     *tmp       = NULL;
  int32_t   n = 0;

  tmp = fgets(str, MAX_LEN, stdin);
  n = strtol(str, NULL, 10);

  memset(str, 0, MAX_LEN);
  tmp = fgets(str, MAX_LEN, stdin);
  split_str2int(str, n, " ", num);

  main_logic(n, num);

  return 0;
}