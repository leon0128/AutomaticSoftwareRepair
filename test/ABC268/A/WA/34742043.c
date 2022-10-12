#include <stdio.h>

int main()
{
    int integers[5];
    for(int i=0; i<5; i++) {
        scanf("%i", &integers[i]);
    }
    
    unsigned int num_distinct_nums = 5;
    for (int curr_num_to_check=0; curr_num_to_check<4; curr_num_to_check++) {
        for (int i=curr_num_to_check+1; i<5; i++) {
            if (integers[curr_num_to_check] == integers[i]) {
                num_distinct_nums--;
            }
        }
    }
    
    printf("%i\n", num_distinct_nums);

    return 0;
}