#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

enum {
  OK = 1,
  NG = 0,
  NUM_COUNT = 2,
  MAX_LEN = 16,
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
  int32_t num[]
)
{
  bool score_1 = false;
  bool score_2 = false;
  bool score_4 = false;
  int32_t score = 0;
  int32_t i;

  for (i = 0; i < NUM_COUNT; i++) {
    if (num[i] & 1) score_1 = true;
    if (num[i] & 2) score_2 = true;
    if (num[i] & 4) score_4 = true;
  }

  if (score_1) score += 1;
  if (score_2) score += 2;
  if (score_4) score += 4;

  printf("%d\n", score);

  return;
}


int32_t main(void)
{
  char      str[MAX_LEN] = { 0 };
  int32_t   num[NUM_COUNT] = { 0 };
  char     *tmp       = NULL;
  
  tmp = fgets(str, MAX_LEN, stdin);
  split_str2int(str, NUM_COUNT, " ", num);

  main_logic(num);

  return 0;
}