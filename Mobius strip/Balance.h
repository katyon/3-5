#pragma once

#include "AliceLib/AliceLib.h"

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

	//上記の関数で作成したクオータニオンを使いZ軸の傾きを徐々につけていく
	void makeAnAngle(Quaternion& posture,const Quaternion& tile,float complementary = 0.3f);


	void demoPlay();
}

