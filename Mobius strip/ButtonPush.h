#pragma once


class ButtonPush 
{
private:

public:
	ButtonPush();
	~ButtonPush() = default;
	
	int stone_board[5][5] = {}; // �Δ̎��ʔԍ�
	int storage_board[5] = {};  // �������{�^���̔ԍ�
	int answer_board[5] = {};   // �����̃{�^���̔ԍ�
	bool final_judge;
	bool provisional_judge;

	void init();
	bool judge_answer();
	void update();
	// �����ꂽ�{�^���̔ԍ���ۑ�����
	// push_botton(�z��ԍ��̏c, ��);
	void push_botton(int height, int width);

	static ButtonPush* getInstance() 
	{
		static ButtonPush instance;
		return &instance;
	}


};
