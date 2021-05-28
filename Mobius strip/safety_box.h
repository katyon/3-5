#pragma once
#include <iostream>
#include <queue>
#include "AliceLib/AliceLib.h"

struct StageObject;
struct ColBox;

class SafetyBox
{
private:
	enum COMMAND{ UP, DOWN };
	std::queue<COMMAND> answer;
	std::queue<COMMAND> input;


private:
	SafetyBox();
	void setAnswer();
	void inputCommand(COMMAND com);

public:
	bool locked;

	void init();
	void update(const Camera& camera);
	void render();

	void pushButton(StageObject* objects, const ColBox col);

	static SafetyBox* getInstance()
	{
		static SafetyBox instance;
		return &instance;
	}
};