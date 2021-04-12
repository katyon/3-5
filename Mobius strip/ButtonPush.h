#pragma once


class ButtonPush 
{
private:

public:
	ButtonPush();
	~ButtonPush() = default;
	
	int stone_board[5][5] = {}; // 石板の識別番号
	int storage_board[5] = {};  // 押したボタンの番号
	int answer_board[5] = {};   // 答えのボタンの番号
	bool final_judge;
	bool provisional_judge;

	void init();
	bool judge_answer();
	void update();
	// 押されたボタンの番号を保存する
	// push_botton(配列番号の縦, 横);
	void push_botton(int height, int width);

	static ButtonPush* getInstance() 
	{
		static ButtonPush instance;
		return &instance;
	}


};
