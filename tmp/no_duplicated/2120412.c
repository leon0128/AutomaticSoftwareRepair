#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const int max_input = 1001;

int main(void)
{
    int command_num, pos, count, count_L, count_R;
    int tmp_pos;
    char str_command[max_input], str_L[3], str_R[3];
    char str_com[3], str_tmp[3];
    char str_button[] = {'A', 'B', 'X', 'Y'};
    pos = 0;
    count = 0;
    count_L = 0;
    count_R = 0;
    tmp_pos = 0;
    {
        int i;
        
        for(i = 0;i < max_input;i ++)
            str_command[i] = '\0';
    }
    scanf("%d", & command_num);
    scanf("%s", str_command);
    str_L[0] = str_L[1] = str_L[2] = '\0';
    scanf("YES\n");
    str_R[0] = str_R[1] = str_R[2] = '\0';
    {
        unsigned int i;
        
        for(i = 0;i < sizeof (str_button) / sizeof(char);i ++)
        {
            unsigned int j;
            
            for(j = 0;j < sizeof (str_button) / sizeof(char);j ++)
            {
                str_com[0] = str_button[i];
                str_com[1] = str_button[j];
                str_com[2] = '\0';
                
                while(str_command[pos] != '\0')
                {
                    str_tmp[0] = str_command[pos];
                    str_tmp[1] = str_command[++ pos];
                    str_tmp[2] = '\0';
                    
                    if(strcmp(str_tmp, str_com) == 0)
                        count ++;
                    else
                        ;
                }
                
                if(count_L < count)
                {
                    strcpy(str_L, str_com);
                    count_L = count;
                }
                else
                    ;
                count = 0;
                pos = 0;
            }
        }
    }
    
    while(str_command[pos] != '\0')
    {
        tmp_pos = pos;
        str_tmp[0] = str_command[pos];
        str_tmp[1] = str_command[++ pos];
        str_tmp[2] = '\0';
        
        if(strcmp(str_tmp, str_L) == 0)
        {
            str_command[tmp_pos] = 'e';
            str_command[tmp_pos + 1] = 'e';
        }
        else
            ;
    }
    {
        unsigned int i;
        
        for(i = 0;i < sizeof (str_button) / sizeof(char);i ++)
        {
            unsigned int j;
            
            for(j = 0;j < sizeof (str_button) / sizeof(char);j ++)
            {
                str_com[0] = str_button[i];
                str_com[1] = str_button[j];
                str_com[2] = '\0';
                
                while(str_command[pos] != '\0')
                {
                    str_tmp[0] = str_command[pos];
                    str_tmp[1] = str_command[++ pos];
                    str_tmp[2] = '\0';
                    
                    if(strcmp(str_tmp, str_com) == 0)
                        count ++;
                    else
                        ;
                }
                
                if(count_R < count)
                {
                    strcpy(str_R, str_com);
                    count_R = count;
                }
                else
                    ;
                count = 0;
                pos = 0;
            }
        }
    }
    count = count_L + count_R + (command_num - ((2 * count_L) + (2 * count_R)));
    
    if(count % 4 != 0)
        printf("NO\n");
    else
        
        if(count % 4 == 0 && count % 100 != 0)
            printf("YES\n");
        else
            
            if(count % 4 == 0 && count % 100 == 0 && count % 400 != 0)
                printf("NO\n");
            else
                printf("YES\n");
    
    return 0;
}