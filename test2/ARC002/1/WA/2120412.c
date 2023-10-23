#include<stdio.h>
#include<string.h>
#include<stdlib.h>

const int max_input = 1001;

int main(void)
{
    int command_num, pos = 0, count = 0, count_L = 0, count_R = 0;
    int tmp_pos = 0;
    char str_command[max_input], str_L[3], str_R[3];
    char str_com[3], str_tmp[3];
    char str_button[] = {'A', 'B', 'X', 'Y'};

    for(int i = 0; i < max_input; i++)
    {
        str_command[i] = '\0';
    }

    scanf("%d", &command_num);
    scanf("%s", str_command);

    str_L[0] = str_L[1] = str_L[2] = '\0';
    str_R[0] = str_R[1] = str_R[2] = '\0';

    // Lに割り当てる文字列を検索する
    for(unsigned int i = 0; i < sizeof(str_button) / sizeof(char); i++)
    {
        for(unsigned int j = 0; j < sizeof(str_button) / sizeof(char); j++)
        {
            str_com[0] = str_button[i];
            str_com[1] = str_button[j];
            str_com[2] = '\0';

            while( str_command[pos] != '\0' )
            {
            	// Lに割り当てる文字列を検索する
                str_tmp[0] = str_command[pos];
                str_tmp[1] = str_command[++pos];
                str_tmp[2] = '\0';

                if( strcmp(str_tmp, str_com) == 0 )
                {
                    count++;
                }
            }

            if( count_L < count )
            {
                // Lに割り当てる文字列を出現回数が多い方とする
                strcpy(str_L, str_com);
                count_L = count;
            }

            count = 0;
            pos = 0;
        }
    }

    // Lに割り当てる文字列の箇所を、全体のコマンドから削除する
    while( str_command[pos] != '\0' )
    {
        tmp_pos = pos;
        str_tmp[0] = str_command[pos];
        str_tmp[1] = str_command[++pos];
        str_tmp[2] = '\0';

        if( strcmp(str_tmp, str_L) == 0 )
        {
            // 割り当てたコマンドの所は、関係の無い文字列で埋めておく
            str_command[tmp_pos] = 'e';
            str_command[tmp_pos + 1] = 'e';
        }
    }

    // Rに割り当てる文字列を検索する
    for(unsigned int i = 0; i < sizeof(str_button) / sizeof(char); i++)
    {
        for(unsigned int j = 0; j < sizeof(str_button) / sizeof(char); j++)
        {
            str_com[0] = str_button[i];
            str_com[1] = str_button[j];
            str_com[2] = '\0';

            while( str_command[pos] != '\0' )
            {
            	// Rに割り当てる文字列を検索する
                str_tmp[0] = str_command[pos];
                str_tmp[1] = str_command[++pos];
                str_tmp[2] = '\0';

                if( strcmp(str_tmp, str_com) == 0 )
                {
                    count++;
                }
            }

            if( count_R < count )
            {
                // Rに割り当てる文字列の出現回数
                strcpy(str_R, str_com);
                count_R = count;
            }

            count = 0;
            pos = 0;
        }
    }

    // コマンド入力回数の計算
    count = count_L + count_R + ( command_num - ( ( 2 * count_L ) + ( 2 * count_R ) ) );

    printf("%d\n", count);

    return 0;
}
