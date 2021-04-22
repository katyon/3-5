#pragma once
#include "AliceLib\AliceLib.h"
#include "StageData.h"
#include "Shelter.h"

static void cOBB(Camera& eye)
{
	static FLOAT3 pos, scale = ScalarToFloat3(1.0f), angle;
	ImGui::Begin("OBB DATA");
	ImGui::InputFloat("pos::X", &pos.x, 1.0f, -1.0f);
	ImGui::InputFloat("pos::Y", &pos.y, 1.0f, -1.0f);
	ImGui::InputFloat("pos::Z", &pos.z, 1.0f, -1.0f);
	ImGui::InputFloat("scale::X", &scale.x, 0.1f, -0.1f);
	ImGui::InputFloat("scale::Y", &scale.y, 0.1f, -0.1f);
	ImGui::InputFloat("scale::Z", &scale.z, 0.1f, -0.1f);
	ImGui::InputFloat("angle::X", &angle.x, 1.0f, -1.0f);
	ImGui::InputFloat("angle::Y", &angle.y, 1.0f, -1.0f);
	ImGui::InputFloat("angle::Z", &angle.z, 1.0f, -1.0f);
	//ImGui::InputFloat3("pos", pos.GetAddress(), -1.0f, 1.0f);
	//ImGui::InputFloat3("scale", scale.GetAddress(), -1.0f, 1.0f);
	//ImGui::InputFloat3("angle", angle.GetAddress(), -1.0f, 1.0f);
	ImGui::End();

	Geometric::Cube(eye, pos, scale, toRadian(angle), eye.LightFloamCamera());
}
//るしあ
static const OBB colbox_w[] =
{
	//{{/*pos*/},{/*scale*/},{/*toRadian(angle)*/}},
	{{-43.0f,5.0f,-19.0f},{16.8f,10.7f,20.1f},{/*toRadian(angle)*/}},
	{{-47.0f,12.0f,-41.0f},{13.0f,25.9f,15.1f},{}},
	{{-49.0f,12.0f,32.0f},{17.0f,31.4f,36.7f},{}},
	{{-7.0f,40.0f,-11.0f},{1.0f,10.5f,42.7f},{}},
	{{-29.0f,41.0f,9.0f},{50.0f,10.5f,1.0f},{}},
	{{-44.0f,49.0f,-35.0f},{9.0f,24.0f,16.4f},{}},
	{{-40.0f,40.0f,-8.0f},{17.0f,6.1f,23.8f},{}},

};
//ゆか
static const OBB colbox_f[] =
{
	//{{/*pos*/},{/*scale*/},{/*toRadian(angle)*/}},
	{{0.0f,-5.0f,0.0f},{110.0f,10.7f,110.0f},{/*toRadian(angle)*/}},
	{{8.0f,12.0f,-51.0f},{17.4f,49.8f,40.3f},{ toRadian({0.0f,0.0f,46.0f})}},
	{{13.0f,24.0f,-31.0f},{9.0f,47.6f,1.4f},{ toRadian({0.0f,0.0f,46.0f})}},
	{{-31.0f,34.0f,-24.0f},{53.0f,4.0f,72.3f},{}},
};
//アイテム
static const ItemBox colbox_i[] =
{
	//{{/*pos*/},{/*scale*/},{/*toRadian(angle)*/},-1},
	{{-44.0f,13.0f,-38.0f},{9.3f,4.9f,4.6f},{},0},//紙
	{{-44.0f,15.0f,-19.0f},{9.3f,11.4f,14.4f},{},1},//天秤
	{{-53.0f,13.0f, 0.0f},{9.0f,24.0f,12.6f},{},2},//出口
};
void getMouseRay(const Camera& eye, FLOAT3& start, FLOAT3& end);

//アイテムなどの当たり判定
inline bool ItemisClick2(const Camera& eye, int& operation)
{
	bool result = false;
	operation = -1;
	float dis = 0.0f;
	FLOAT3 hitPos[2] = {};
	static FLOAT3 s, e;
	getMouseRay(eye, s, e);
	for (const auto& item : colbox_i)
	{
		if (ColLineOBB(s, e,
			item.obb,
			hitPos[0]))
		{
			if (!result)
			{
				hitPos[1] = hitPos[0];
				dis = s.distanceFrom(hitPos[1]);
				operation = item.option;
				result = true;
			}
			else
			{
				float s_h = s.distanceFrom(hitPos[0]);
				if (s_h < dis)
				{
					operation = item.option;
					hitPos[1] = hitPos[0];
					dis = s.distanceFrom(hitPos[1]);
				}
			}
		}
	}
	return result;
}