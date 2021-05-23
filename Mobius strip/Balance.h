#pragma once

#include "AliceLib/AliceLib.h"
#include <stdlib.h>

namespace Balance
{
	//傾きの方向
	enum BalanceResult
	{
		BR_Right,
		BR_Equal,
		BR_Left
	};

	//重さの単位
	using B_weight = int;

	//傾きを取得
	//ここではZ軸を回転軸にした回転しか作成しないため
	//X軸回転やY軸回転を含む回転を行う場合はクオータニオンを2つ以上に分けること
	BalanceResult getTilt(const B_weight& right, const B_weight& left, Quaternion* _tile = nullptr);
	BalanceResult getTilt(const B_weight& right, const B_weight& left, float* _tile = nullptr);

	//上記の関数で作成したクオータニオンを使いZ軸の傾きを徐々につけていく
	//complementary→補完率0~１の範囲で０に近づくほど滑らかに動く
	void makeAnAngle(Quaternion& posture,const Quaternion& tile,float complementary = 0.3f);

	void makeAnAngle(int& frame, const float& rate);

	void Init();

	bool Update();
	bool Set();
	void Render();


	//テスト用
	void demoPlay();
}

