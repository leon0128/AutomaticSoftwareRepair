#include <stdio.h>
#include <stdlib.h>

int main()
{
    int integers[5];
    for(int i=0; i<5; i++) {
        if (scanf("%i", &integers[i]) != 1) {
            printf("Inappropriate value.\n");
            return 1;
        }
    }
    
    int num_distinct_nums = 1;
    int nums_match = 0;
    for (int curr_num_to_check=0; curr_num_to_check<4; curr_num_to_check++) {
        for (int i=curr_num_to_check+1; i<5; i++) {
            if (integers[curr_num_to_check] == integers[i]) {
                nums_match = 1;
            }
        }
        if (nums_match == 0) {num_distinct_nums++;}
        nums_match = 0;
    }
    
    // int final_value = 1 > num_distinct_nums ? 1: num_distinct_nums;
    printf("%i\n", num_distinct_nums);

    return 0;
}