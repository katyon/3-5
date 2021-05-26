#pragma once

#include "AliceLib/AliceLib.h"
#include <stdlib.h>

namespace Balance
{
	//�X���̕���
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

	//�d���̒P��
	using B_weight = int;

	//�X�����擾
	//�����ł�Z������]���ɂ�����]�����쐬���Ȃ�����
	//X����]��Y����]���܂މ�]���s���ꍇ�̓N�I�[�^�j�I����2�ȏ�ɕ����邱��
	BalanceResult getTilt(const B_weight& right, const B_weight& left, Quaternion* _tile = nullptr);
	BalanceResult getTilt(const B_weight& right, const B_weight& left, float* _tile = nullptr);

	//��L�̊֐��ō쐬�����N�I�[�^�j�I�����g��Z���̌X�������X�ɂ��Ă���
	//complementary���⊮��0~�P�͈̔͂łO�ɋ߂Â��قǊ��炩�ɓ���
	void makeAnAngle(Quaternion& posture,const Quaternion& tile,float complementary = 0.3f);

	void makeAnAngle(int& frame, const float& rate);

	void Init();

	bool Update();
	bool Set();
	void Render();


	//�e�X�g�p
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
	bool Equilibrium = false;   // �A�C�e�����u���ꂽ�Ƃ�true�ɂ���

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

