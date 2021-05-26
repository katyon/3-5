#include "safety_box.h"
#include "StageManager.h"
#include "reticle.h"

void SafetyBox::setAnswer()
{
	answer.push(COMMAND::UP);
	answer.push(COMMAND::DOWN);
	answer.push(COMMAND::DOWN);
	answer.push(COMMAND::UP);
	answer.push(COMMAND::UP);
	answer.push(COMMAND::UP);
	answer.push(COMMAND::DOWN);
	answer.push(COMMAND::DOWN);
	answer.push(COMMAND::UP);
	answer.push(COMMAND::DOWN);
}

void SafetyBox::init()
{
	setAnswer();
	locked = true;
}

void SafetyBox::update(const Camera& camera)
{
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
			if ((col.option != -7) && (col.option != -8)) continue;
			distance = 100.0f;

			if (ColLineOBB(ray_start, ray_end, col.obb, hit_pos)) { distance = ray_start.distanceFrom(hit_pos); }
			if (distance < 30.0f)
			{
				Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);
				SafetyBox::getInstance()->pushButton(objects, col);
			}
		}

		// アニメーション再生
		for (int i = 0; i < StageData::MaxObjects; i++)
		{
			if (objects[i].ID == "kinko.fbx")
			{
				if (objects[i].body.IsPlayAnimation())
				{
					objects[i].body.UpdateAnimation(0.1f);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < StageData::MaxObjects; i++)
		{
			if (objects[i].ID == "kinko.fbx")
			{
				if (objects[i].body.IsPlayAnimation())
				{
					objects[i].body.UpdateAnimation();
				}
			}
		}
	}
}

void SafetyBox::pushButton(StageObject* objects, const ColBox col)
{
	if (input::TRG(input::MOUSE_L))
	{
		if (objects)
		{
			for (int i = 0; i < StageData::MaxObjects; i++)
			{
				if (objects[i].ID == "kinko.fbx")
				{
					if (col.option == -7)
					{
						objects[i].body.PlayAnimation(1, false);
						SafetyBox::getInstance()->inputCommand(COMMAND::UP);
					}
					if (col.option == -8)
					{
						objects[i].body.PlayAnimation(2, false);
						SafetyBox::getInstance()->inputCommand(COMMAND::DOWN);
					}
				}
			}
		}
	}
}


void SafetyBox::inputCommand(COMMAND com)
{
	input.push(com);
	if (input.size() > 10) { input.pop(); }

	if (input == answer)
	{
		locked = false;

		StageObject* objects = StageManager::getIns()->getStageObjects();
		if (objects)
		{
			for (int i = 0; i < StageData::MaxObjects; i++)
			{
				if (objects[i].ID == "kinko.fbx")
				{
					objects[i].body.PlayAnimation(0, false);
				}
			}
		}
	}
}