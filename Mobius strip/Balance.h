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


	//SkinnedMesh cross_weight;  // weight = 10
	//SkinnedMesh gold_weight;   // weight = 5
	//SkinnedMesh iron_weight;   // weight = 3
	//SkinnedMesh wood_weight;   // weight = 2

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

class Libra
{
private:
	SkinnedMesh cross_weight;  // weight = 10
	SkinnedMesh gold_weight;   // weight = 5
	SkinnedMesh iron_weight;   // weight = 3
	SkinnedMesh wood_weight;   // weight = 2

	SkinnedMesh tenbin_1;
	SkinnedMesh tenbin_2;

	FLOAT3 position;
	FLOAT3 cross_scale;
	FLOAT3 iron_scale;
	FLOAT3 gold_scale;
	Quaternion posture;

public:
	bool Equilibrium = false;   // アイテムが置かれたときtrueにする

	Libra();

	void Init();
	void Update();
	void Render(const Camera& camera);
	void Release();

	static Libra* getInstance()
	{
		static Libra instance;
		return &instance;
	}
};

