#pragma once

#include "AliceLib/AliceLib.h"

namespace Balance
{
	//�X���̕���
	enum BalanceResult
	{
		BR_Right,
		BR_Equal,
		BR_Left
	};

	//�d���̒P��
	using B_weight = int;

	//�X�����擾
	//�����ł�Z������]���ɂ�����]�����쐬���Ȃ�����
	//X����]��Y����]���܂މ�]���s���ꍇ�̓N�I�[�^�j�I����2�ȏ�ɕ����邱��
	BalanceResult getTilt(const B_weight& right, const B_weight& left, Quaternion* _tile = nullptr);

	//��L�̊֐��ō쐬�����N�I�[�^�j�I�����g��Z���̌X�������X�ɂ��Ă���
	void makeAnAngle(Quaternion& posture,const Quaternion& tile,float complementary = 0.3f);


	void demoPlay();
}

