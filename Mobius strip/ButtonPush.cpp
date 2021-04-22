#include <stdio.h>
#include "ButtonPush.h"
#include "AliceLib/AliceLib.h"
#include "Shelter.h"
//#define BPGet ButtonPush::getInstance()

#define BPGet ButtonPush::getInstance()
#define DownPos 2.5

ButtonPush::ButtonPush()
{

	button[0][0].model.load("Data/Buttons/botan1.fbx");
	button[0][1].model.load("Data/Buttons/botan2.fbx");
	button[0][2].model.load("Data/Buttons/botan3.fbx");
	button[0][3].model.load("Data/Buttons/botan4.fbx");
	button[0][4].model.load("Data/Buttons/botan5.fbx");
	button[1][0].model.load("Data/Buttons/botan6.fbx");
	button[1][1].model.load("Data/Buttons/botan7.fbx");
	button[1][2].model.load("Data/Buttons/botan8.fbx");
	button[1][3].model.load("Data/Buttons/botan9.fbx");
	button[1][4].model.load("Data/Buttons/botan10.fbx");
	button[2][0].model.load("Data/Buttons/botan11.fbx");
	button[2][1].model.load("Data/Buttons/botan12.fbx");
	button[2][2].model.load("Data/Buttons/botan13.fbx");
	button[2][3].model.load("Data/Buttons/botan14.fbx");
	button[2][4].model.load("Data/Buttons/botan15.fbx");
	button[3][0].model.load("Data/Buttons/botan16.fbx");
	button[3][1].model.load("Data/Buttons/botan17.fbx");
	button[3][2].model.load("Data/Buttons/botan18.fbx");
	button[3][3].model.load("Data/Buttons/botan19.fbx");
	button[3][4].model.load("Data/Buttons/botan20.fbx");
	button[4][0].model.load("Data/Buttons/botan21.fbx");
	button[4][1].model.load("Data/Buttons/botan22.fbx");
	button[4][2].model.load("Data/Buttons/botan23.fbx");
	button[4][3].model.load("Data/Buttons/botan24.fbx");
	button[4][4].model.load("Data/Buttons/botan25.fbx");
	base.model.load("Data/Buttons/hako.fbx");

}

void ButtonPush::init()
{
	// 初期座標
	base.pos = { 10,2,0 };

	button[0][0].pos = {10+ -2.6,3,2.8 };
	button[0][1].pos = {10+ -1.3,3,2.8 };
	button[0][2].pos = {10+ 0,3,2.8 };
	button[0][3].pos = {10+ 1.3,3,2.8 };
	button[0][4].pos = {10+ 2.6,3,2.8 };

	button[1][0].pos = {10 + -2.6,3,1.4 };
	button[1][1].pos = {10 + -1.3,3,1.4 };
	button[1][2].pos = {10 + 0,3,1.4 };
	button[1][3].pos = {10 + 1.3,3,1.4 };
	button[1][4].pos = {10 + 2.6,3,1.4 };

	button[2][0].pos = {10 + -2.6,3,0 };
	button[2][1].pos = {10 + -1.3,3,0 };
	button[2][2].pos = {10 + 0,3,0 };
	button[2][3].pos = {10 + 1.3,3,0 };
	button[2][4].pos = {10 + 2.6,3,0 };

	button[3][0].pos = { 10 + -2.6,3,-1.4 };
	button[3][1].pos = { 10 + -1.3,3,-1.4 };
	button[3][2].pos = { 10 + 0,3,-1.4 };
	button[3][3].pos = { 10 + 1.3,3,-1.4 };
	button[3][4].pos = { 10 + 2.6,3,-1.4 };

	button[4][0].pos = {10+ -2.6,3,-2.8 };
	button[4][1].pos = {10+ -1.3,3,-2.8 };
	button[4][2].pos = {10+ 0,3,-2.8 };
	button[4][3].pos = {10+ 1.3,3,-2.8 };
	button[4][4].pos = {10+ 2.6,3,-2.8 };

	// 石板の識別番号設定
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
	answer_board[1] = 12;
	answer_board[2] = 13;
	answer_board[3] = 14;
	answer_board[4] = 15;

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
				int tens = storage_board[i] / 10 % 10 - 1;
				int ones = storage_board[i] % 10 - 1;
				button[tens][ones].pos.y = 3;
				button[tens][ones].Pushflg = false;

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

void ButtonPush::update(const Camera& camera)
{
	FLOAT3 start, end;
	FLOAT3 HitPos[2];
	bool result = false;
	float dis = 0.0f;
	int operation_x = -1;
	int operation_y = -1;

	// ここにキー操作
	if (input::TRG(input::MOUSE_L)&& !final_judge) {
		
		getMouseRay(camera, start, end);
		
		for (int i = 0; i < 5; i++) 
		{
			for (int j = 0; j < 5; j++) 
			{
				button[i][j].isPush = false;
				if (ColLineOBB(start, end, { button[i][j].pos,FLOAT3(1, 1, 1),button[i][j].posture }, HitPos[0])) 
				{
					if (!result)
					{
						HitPos[1] = HitPos[0];
						dis = start.distanceFrom(HitPos[1]);
						operation_y = i;
						operation_x = j;
						result = true;
					}
					else
					{
						float s_h = start.distanceFrom(HitPos[0]);
						if (s_h < dis)
						{
							operation_y = i;
							operation_x = j;
							HitPos[1] = HitPos[0];
							dis = start.distanceFrom(HitPos[1]);
						}
					}
				}
			}
		}
		button[operation_y][operation_x].isPush = true;
		
		if (button[0][0].isPush && !button[0][0].Pushflg)
		{
			push_botton(0, 0);
			button[0][0].isPush = false;
			button[0][0].pos.y = DownPos;
			button[0][0].Pushflg = true;
		}
		if (button[1][0].isPush && !button[1][0].Pushflg)
		{
			push_botton(1, 0);
			button[1][0].isPush = false;
			button[1][0].pos.y = DownPos;
			button[1][0].Pushflg = true;
		}
		if (button[2][0].isPush && !button[2][0].Pushflg)
		{
			push_botton(2, 0);
			button[2][0].isPush = false;
			button[2][0].pos.y = DownPos;
			button[2][0].Pushflg = true;
		}
		if (button[3][0].isPush && !button[3][0].Pushflg)
		{
			push_botton(3, 0);
			button[3][0].isPush = false;
			button[3][0].pos.y = DownPos;
			button[3][0].Pushflg = true;
		}
		if (button[4][0].isPush && !button[4][0].Pushflg)
		{
			push_botton(4, 0);
			button[4][0].isPush = false;
			button[4][0].pos.y = DownPos;
			button[4][0].Pushflg = true;
		}

		if (button[0][1].isPush && !button[0][1].Pushflg)
		{
			push_botton(0, 1);
			button[0][1].isPush = false;
			button[0][1].pos.y = DownPos;
			button[0][1].Pushflg = true;
		}
		if (button[1][1].isPush && !button[1][1].Pushflg)
		{
			push_botton(1, 1);
			button[1][1].isPush = false;
			button[1][1].pos.y = DownPos;
		}
		if (button[2][1].isPush && !button[2][1].Pushflg)
		{
			push_botton(2, 1);
			button[2][1].isPush = false;
			button[2][1].pos.y = DownPos;
			button[2][1].Pushflg = true;
		}
		if (button[3][1].isPush && !button[3][1].Pushflg)
		{
			push_botton(3, 1);
			button[3][1].isPush = false;
			button[3][1].pos.y = DownPos;
			button[3][1].Pushflg = true;
		}
		if (button[4][1].isPush && !button[4][1].Pushflg)
		{
			push_botton(4, 1);
			button[4][1].isPush = false;
			button[4][1].pos.y = DownPos;
			button[4][1].Pushflg = true;
		}

		if (button[0][2].isPush && !button[0][2].Pushflg)
		{
			push_botton(0, 2);
			button[0][2].isPush = false;
			button[0][2].pos.y = DownPos;
			button[0][2].Pushflg = true;
		}
		if (button[1][2].isPush && !button[1][2].Pushflg)
		{
			push_botton(1, 2);
			button[1][2].isPush = false;
			button[1][2].pos.y = DownPos;
			button[1][2].Pushflg = true;
		}
		if (button[2][2].isPush && !button[2][2].Pushflg)
		{
			push_botton(2, 2);
			button[2][2].isPush = false;
			button[2][2].pos.y = DownPos;
			button[2][2].Pushflg = true;
		}
		if (button[3][2].isPush && !button[3][2].Pushflg)
		{
			push_botton(3, 2);
			button[3][2].isPush = false;
			button[3][2].pos.y = DownPos;
		}
		if (button[4][2].isPush && !button[4][2].Pushflg)
		{
			push_botton(4, 2);
			button[4][2].isPush = false;
			button[4][2].pos.y = DownPos;
			button[4][2].Pushflg = true;
		}

		if (button[0][3].isPush && !button[0][3].Pushflg)
		{
			push_botton(0, 3);
			button[0][3].isPush = false;
			button[0][3].pos.y = DownPos;
			button[0][3].Pushflg = true;
		}
		if (button[1][3].isPush && !button[1][3].Pushflg)
		{
			push_botton(1, 3);
			button[1][3].isPush = false;
			button[1][3].pos.y = DownPos;
			button[1][3].Pushflg = true;
		}
		if (button[2][3].isPush && !button[2][3].Pushflg)
		{
			push_botton(2, 3);
			button[2][3].isPush = false;
			button[2][3].pos.y = DownPos;
			button[2][3].Pushflg = true;
		}
		if (button[3][3].isPush && !button[3][3].Pushflg)
		{
			push_botton(3, 3);
			button[3][3].isPush = false;
			button[3][3].pos.y = DownPos;
			button[3][3].Pushflg = true;
		}
		if (button[4][3].isPush && !button[4][3].Pushflg)
		{
			push_botton(4, 3);
			button[4][3].isPush = false;
			button[4][3].pos.y = DownPos;
			button[4][3].Pushflg = true;
		}

		if (button[0][4].isPush && !button[0][4].Pushflg)
		{
			push_botton(0, 4);
			button[0][4].isPush = false;
			button[0][4].pos.y = DownPos;
			button[0][4].Pushflg = true;
		}
		if (button[1][4].isPush && !button[1][4].Pushflg)
		{
			push_botton(1, 4);
			button[1][4].isPush = false;		
			button[1][4].pos.y = DownPos;
			button[1][4].Pushflg = true;
		}
		if (button[2][4].isPush && !button[2][4].Pushflg)
		{
			push_botton(2, 4);
			button[2][4].isPush = false;
			button[2][4].pos.y = DownPos;
			button[2][4].Pushflg = true;
		}
		if (button[3][4].isPush && !button[3][4].Pushflg)
		{
			push_botton(3, 4);
			button[3][4].isPush = false;
			button[3][4].pos.y = DownPos;
			button[3][4].Pushflg = true;
		}
		if (button[4][4].isPush && !button[4][4].Pushflg)
		{
			push_botton(4, 4);
			button[4][4].isPush = false;
			button[4][4].pos.y = DownPos;
			button[4][4].Pushflg = true;
		}



	}
	// 5つすべて押したら判定
	if (storage_board[4] != 0) {
		 //falseの場合はjudge_answe内でstorage_boardが初期化されます
		final_judge = judge_answer();
	}

	// 問題が解けた場合の処理
	if (final_judge)
	{
		//font::OutPut(L"clear", { 100,100 }, { 10,10 }, { 1,1,0,1 });
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) 
			{
				if (button[i][j].pos.y > DownPos) {
					button[i][j].pos.y -= 0.05;
				}
			}
		}

	}else
	{

	}
	font::OutPut(L"ButtonPush", { 0,0 }, { 1,1 }, { 1,0,0,1 });

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

void ButtonPush::Render(const Camera& camera)
{
	SkinnedMeshRender(base.model, camera, base.pos, FLOAT3(0.1, 0.1, 0.1), base.posture, camera.LightFloamCamera());

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			SkinnedMeshRender(button[i][j].model, camera, button[i][j].pos, FLOAT3(0.1, 0.1, 0.1), button[i][j].posture, camera.LightFloamCamera());
		}
	}
}
