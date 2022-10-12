#include <stdio.h>
#include <string.h>

int main() {
  char *Mon = "Monday";
  char *Tue = "Tuesday";
  char *Wed = "Wednesday";
  char *Thu = "Thursday";
  char *Fri = "Friday";

  char buffer[256];

  scanf("%s", buffer);
  if(strcmp(buffer, Mon) == 0) {
    printf("5\n");
  }
  else if(strcmp(buffer, Tue) == 0){
    printf("4\n");
  }
  else if(strcmp(buffer, Wed) == 0){
    printf("3\n");
  }
  else if(strcmp(buffer, Thu) == 0){
    printf("2\n");
  }
  else if(strcmp(buffer, Fri) == 0){
    printf("1\n");
  }
  return 0;
}