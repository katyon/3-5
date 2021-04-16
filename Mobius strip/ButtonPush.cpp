#include <stdio.h>
#include "ButtonPush.h"
#include "AliceLib/AliceLib.h"
//#define BPGet ButtonPush::getInstance()

#define BPGet ButtonPush::getInstance()

void ButtonPush::init()
{
	// �Δ̎��ʔԍ�����
	// 11 12 13 14 15
	// 21 22 23 24 25
	// 31 32 33 34 35
	// 41 42 43 44 45
	// 51 52 53 54 55  �����Ȃ��Ă�͂�
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			stone_board[i][j] = ((i + 1) * 10) + (j + 1);
		}
	}

	// �����̐���������
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
		// �����ƍ����Ă��邩�m�F
		if (storage_board[i] == answer_board[i])// �����Ă���Ȃ�
		{
			// �������true��
			provisional_judge = true;
		}
		else // �ԈႦ�Ă���ꍇ
		{
			//provisional_judge = false;
			// 1�ł��Ԉ���Ă�����storage_board�����ׂ�0�ɖ߂�
			for (int i = 0; i < 5; i++)
			{
				storage_board[i] = 0;
			}
			return false;
		}

		// 5�ڂ܂Ŕ��肵�I���ĂȂ������肪true�Ȃ��
		if (i == 4 && provisional_judge == true)
		{
			// �ŏI�����true��
			//final_judge = true;
			return true;
		}
	}
}

void ButtonPush::update()
{
	// �����ɃL�[����
	//if (input::TRG('A'))
	//{
	//	push_botton(0, 0);
	//}
	// 5���ׂĉ������画��
	if (storage_board[4] != 0) {
		// false�̏ꍇ��judge_answe����storage_board������������܂�
		final_judge = judge_answer();
	}

	// ��肪�������ꍇ�̏���
	if (final_judge)
	{

	}

}

void ButtonPush::push_botton(int height, int width)
{
	// storage_board�ɋ�(0)������΂����ɓ����
	for (int i = 0; i < 5; i++)
	{
		if (storage_board[i] == 0)
		{
			storage_board[i] = stone_board[height][width];
			break;
			// ���ꂽ������������Ȃ�
		}
	}
}
