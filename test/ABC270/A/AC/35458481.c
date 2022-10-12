/*-----------------------------------------------*/
/*-	at coder 270 - A: 							-*/
/*-----------------------------------------------*/

#include <stdio.h>

/* 問題数 */
#define MAX_QUEST_SU		(3)

/* 設問ごとの配点 */
const c_quest_score[MAX_QUEST_SU]	= { 1, 2, 4};

int main (int argc, char** argv) 
{
	int n_score_t;	/* 得点: 高橋君 */
	int n_score_a;	/* 得点: 青木君 */
	int n_score_s;	/* 得点: すぬけ君 */

	/* 初期化 */
	n_score_t = 0;
	n_score_a = 0;
	n_score_s = 0;

	/* 入力 */
	scanf("%d %d", &n_score_t, &n_score_a);

	/* スコア計算 */
	for ( int i=0; i<MAX_QUEST_SU; i++) {
		int f_taka = (c_quest_score[i] & n_score_t) ? 1 : 0;
		int f_aoki = (c_quest_score[i] & n_score_a) ? 1 : 0;

		n_score_s += (f_taka | f_aoki) ? c_quest_score[i] : 0;
	}

	/* 出力 */
	printf("%d\n", n_score_s);

	return 0;
}

