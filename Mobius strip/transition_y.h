#pragma once
#include "AliceLib/AliceLib.h"

class Transition_y
{
private:

	static constexpr float speed_coeff = 150.0f;
	static constexpr float timer_coeff = 10.0f;

	static constexpr const wchar_t* file_pass = nullptr;
	const bool isFileExist;

	static constexpr float amout_s	= 6.0f * OnceInRadians;
	static constexpr float amout_m	= amout_s / 6.0f;
	static constexpr float amout_h	= amout_m / 6.0f;
	
	float alpha;

	float		s;
	float		m;
	float		h;

	void normal();
	

public:
	float delta_time;

	Transition_y() 
		:delta_time(0.0f),s(0.0f), m(0.0f), h(0.0f), alpha(0.0f),
		isFileExist(file_pass ? std::wifstream(Transition_y::file_pass).is_open() : false) {}
	
	void init();

	//フェイドが完了したときにtrueを返します
	bool fade_out();
	bool fade_in();
	
	void Rotation_r();
	void Rotation_l();
	
	void Render();
	
	virtual ~Transition_y() {}

	const float& getAlpha()const { return alpha; }
};

