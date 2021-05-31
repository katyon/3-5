#include "key_pad.h"
#include "Reticle.h"

void KeyPad::setAnswer()
{
	while (!answer.empty())
	{
		answer.pop();
	}
	answer.push(1);
	answer.push(10);
}

void KeyPad::init()
{
	setAnswer();
	locked = true;
	actived = false;
}

void KeyPad::update(const Camera& camera)
{
	if (!actived) return;

	StageObject* objects = StageManager::getIns()->getStageObjects();
	if (locked)
	{
		FLOAT3 hit_pos;
		float distance = 100.0f;

		static FLOAT3 ray_start, ray_end;
		getMouseRay(camera, ray_start, ray_end);

		// ボタン入力処理
		for (const auto& col : StageManager::getIns()->getColBoxs())
		{
			if (!((col.option <= -11) && (col.option >= -20))) continue;	//0~9までの入力キーごとのオプションを参照
			distance = 100.0f;

			if (ColLineOBB(ray_start, ray_end, col.obb, hit_pos)) { distance = ray_start.distanceFrom(hit_pos); }
			if (distance < 30.0f)
			{
				Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);
				KeyPad::getInstance()->pushButton(objects, col);
			}
		}

		// アニメーション再生
		for (int i = 0; i < StageData::MaxObjects; i++)
		{
			if (objects[i].ID == "Password_yoko.fbx")
			{
				if (objects[i].body.IsPlayAnimation())
				{
					objects[i].body.UpdateAnimation();
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < StageData::MaxObjects; i++)
		{
			if (objects[i].ID == "Password_yoko.fbx")
			{
				if (objects[i].body.IsPlayAnimation())
				{
					objects[i].body.UpdateAnimation();
				}
			}
		}
	}
}

void KeyPad::pushButton(StageObject* objects, const ColBox col)
{
	if (input::TRG(input::MOUSE_L))
	{
		if (objects)
		{
			for (int i = 0; i < StageData::MaxObjects; i++)
			{
				if (objects[i].ID == "Password_yoko.fbx")
				{
					int key = (col.option + 10)*-1;

					objects[i].body.PlayAnimation(key-1, false);
					KeyPad::getInstance()->inputNumber(key);
				}
			}
		}
	}
}

void KeyPad::inputNumber(int num)
{
	input.push(num);
	if (input.size() > 2) { input.pop(); }

	if (input == answer)
	{
		locked = false;

		StageObject* objects = StageManager::getIns()->getStageObjects();
		if (objects)
		{
			for (int i = 0; i < StageData::MaxObjects; i++)
			{

			}
		}
	}
}