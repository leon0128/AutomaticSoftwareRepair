#include <stdio.h>
#include <string.h>

void hexadecimal(int N){
  int div_num , mult, num_input = 1;
  char numbers[3] = "";
  
  for(div_num = N; div_num > 0; div_num /= 16){
    if(div_num % 16 >= 0 && div_num % 16 <= 9){
      numbers[num_input] = div_num % 16 + '0';
    }
    else{
      numbers[num_input] = div_num % 16 + 50;
    }
    num_input--;
  }
  
  if(num_input != -1){
    numbers[0] = '0';
  }
  
  puts(numbers);
}

int main (){
  int N;
  
  scanf("%d", &N);
  hexadecimal(N);
}