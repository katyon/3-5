#include <stdio.h>
#include "ButtonPush.h"
#include "AliceLib/AliceLib.h"
//#define BPGet ButtonPush::getInstance()

#define BPGet ButtonPush::getInstance()

void ButtonPush::init()
{
	// 石板の識別番号入力
	// 11 12 13 14 15
	// 21 22 23 24 25
	// 31 32 33 34 35
	// 41 42 43 44 45
	// 51 52 53 54 55  こうなってるはず
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			stone_board[i][j] = ((i + 1) * 10) + (j + 1);
		}
	}

	// 答えの数字を入れる
	answer_board[0] = 11;
	answer_board[1] = 22;
	answer_board[2] = 33;
	answer_board[3] = 44;
	answer_board[4] = 55;

	final_judge = false;
	provisional_judge = false;
}

bool ButtonPush::judge_answer()
{
	for (int i = 0; i < 5; i++)
	{
		// 答えと合っているか確認
		if (storage_board[i] == answer_board[i])// 合っているなら
		{
			// 仮判定をtrueに
			provisional_judge = true;
		}
		else // 間違えている場合
		{
			//provisional_judge = false;
			// 1つでも間違っていたらstorage_boardをすべて0に戻す
			for (int i = 0; i < 5; i++)
			{
				storage_board[i] = 0;
			}
			return false;
		}

		// 5つ目まで判定し終えてなお仮判定がtrueならば
		if (i == 4 && provisional_judge == true)
		{
			// 最終判定をtrueに
			//final_judge = true;
			return true;
		}
	}
}

void ButtonPush::update()
{
	// ここにキー操作
	//if (input::TRG('A'))
	//{
	//	push_botton(0, 0);
	//}
	// 5つすべて押したら判定
	if (storage_board[4] != 0) {
		// falseの場合はjudge_answe内でstorage_boardが初期化されます
		final_judge = judge_answer();
	}

	// 問題が解けた場合の処理
	if (final_judge)
	{

	}

}

void ButtonPush::push_botton(int height, int width)
{
	// storage_boardに空き(0)があればそこに入れる
	for (int i = 0; i < 5; i++)
	{
		if (storage_board[i] == 0)
		{
			storage_board[i] = stone_board[height][width];
			break;
			// 入れたらもう処理しない
		}
	}
}
