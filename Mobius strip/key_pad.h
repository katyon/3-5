#pragma once
#include <iostream>
#include <queue>
#include "AliceLib/AliceLib.h"
#include "StageManager.h"

class KeyPad
{
private:
	std::queue<int> answer;
	std::queue<int> input;

	bool actived;
	bool locked;

private:
	KeyPad() {}
	void setAnswer();
	void inputNumber(int num);

public:
	void init();
	void update(const Camera& camera);

	void pushButton(StageObject* objects, const ColBox col);
	void activate() { actived = true; }
	bool islocked() { return locked; }

	static KeyPad* getInstance()
	{
		static KeyPad instance;
		return &instance;
	}
};