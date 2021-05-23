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

	int stone_board[5][5] = {}; // �Δ̎��ʔԍ�
	int storage_board[5] = {};  // �������{�^���̔ԍ�
	int answer_board[5] = {};   // �����̃{�^���̔ԍ�
	bool final_judge;
	bool provisional_judge;
	//int timer = 60;
	bool isPlay = true;

	void init();
	bool judge_answer();
	void update(const Camera& camera);
	// �����ꂽ�{�^���̔ԍ���ۑ�����
	// push_botton(�z��ԍ��̏c, ��);
	void push_botton(int height, int width);
	void Render(const Camera& camera);

	static ButtonPush* getInstance()
	{
		static ButtonPush instance;
		return &instance;
	}


};

