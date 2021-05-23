#pragma once
#include "AliceLib/AliceLib.h"

struct Buttons
{
	SkinnedMesh model;
	const FLOAT3	scale;
	XMMATRIX		world_matrix;

	FLOAT3	pos;
	Quaternion posture;
	//PostureVector posture_vec;

	bool isPush;
	bool Pushflg = false;
};

class ButtonPush
{
private:

public:
	Buttons button[5][5];
	Buttons base;

	ButtonPush();
	~ButtonPush() = default;

	int stone_board[5][5] = {}; // 石板の識別番号
	int storage_board[5] = {};  // 押したボタンの番号
	int answer_board[5] = {};   // 答えのボタンの番号
	bool final_judge;
	bool provisional_judge;
	//int timer = 60;
	bool isPlay = true;

	void init();
	bool judge_answer();
	void update(const Camera& camera);
	// 押されたボタンの番号を保存する
	// push_botton(配列番号の縦, 横);
	void push_botton(int height, int width);
	void Render(const Camera& camera);

	static ButtonPush* getInstance()
	{
		static ButtonPush instance;
		return &instance;
	}


};

