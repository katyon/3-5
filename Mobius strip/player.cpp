#include "player.h"
#include "StageManager.h"

#include <cassert>
#include <cmath>
#include <limits>

Player::Player() : pos(0, 0, 0), scale(0.1f, 0.1f, 0.1f)
{
	model.load("Data/actor/chara_anime.fbx");
	Audio::load(3, L"./Data/BGM/footsteps2.wav");
	//Audio::SetVolume(3, volume);
}

void Player::init()
{
	world_matrix = GetWorldMatrix(pos, scale, posture);
}

void Player::update(FPSCamera& camera)
{
	if (auto_control)
	{
		autoControl(camera);
		return;
	}

	world_matrix = GetWorldMatrix(pos, scale, posture);
	posture_vec.CreateVector(posture);
	updateDestVec(camera.GetTarget() - camera.GetPos());
	move(camera);
	horizontal_lay_start = pos + FLOAT3(0, 1.0f, 0);
	horizontal_lay_end = horizontal_lay_start + (Dest.target * 30.0f);
	vertical_lay_start = pos + FLOAT3(0, 1.0f, 0);
	vertical_lay_end = vertical_lay_start + FLOAT3(0, -50.0f, 0);
	Debug->SetString("プレイヤー座標 x:%f,z:%f", pos.x, pos.z);
	Debug->SetString("horizontal_lay_start %f %f %f", horizontal_lay_start.x, horizontal_lay_start.y, horizontal_lay_start.z);
	Debug->SetString("horizontal_lay_end %f %f %f", horizontal_lay_end.x, horizontal_lay_end.y, horizontal_lay_end.z);

	//restrictArea();
	//colWall();
	colFloor();

	changeAnimation();
	setAutoMode(camera);
	colFloor();
	colFloor();
	colFloor();
}

void Player::render(const Camera& camera)
{
	model.UpdateAnimation();

	posture.RotationYaw(toRadian(180));
	{
		SkinnedMeshRender(model, camera, GetWorldMatrix(pos - (camera.GetTarget() - camera.GetPos()), scale, posture), camera.LightFloamCamera());
	}
	posture.RotationYaw(-toRadian(180));
}

void Player::move(const Camera& camera)
{
	if (input::STATE('D'))
	{
		if (posture.TurnToTheFront(pos, pos + FLOAT3(camera.GetTarget().x - camera.GetPos().x,0, camera.GetTarget().z - camera.GetPos().z), 0.2f) == -1) { posture.RotationYaw(toAngle(1)); }
		Dest.target += Dest.right;
	}
	if (input::STATE('A'))
	{
		if (posture.TurnToTheFront(pos, pos + FLOAT3(camera.GetTarget().x - camera.GetPos().x, 0, camera.GetTarget().z - camera.GetPos().z), 0.2f) == -1) { posture.RotationYaw(toAngle(1)); }
		Dest.target += Dest.left;
	}
	if (input::STATE('W'))
	{
		if (posture.TurnToTheFront(pos, pos + FLOAT3(camera.GetTarget().x - camera.GetPos().x, 0, camera.GetTarget().z - camera.GetPos().z), 0.2f) == -1) { posture.RotationYaw(toAngle(1)); }
		Dest.target += Dest.forward;
		//pos += FLOAT3(camera.GetTarget().x - camera.GetPos().x, 0, camera.GetTarget().z - camera.GetPos().z) * 0.01;
	}
	if (input::STATE('S'))
	{
		if (posture.TurnToTheFront(pos, pos + FLOAT3(camera.GetTarget().x - camera.GetPos().x, 0, camera.GetTarget().z - camera.GetPos().z), 0.2f) == -1) { posture.RotationYaw(toAngle(1)); }
		Dest.target += Dest.back;
	}

	if (Dest.target.length() <= 0.000001)
	{
		moves = false;
		return;
	}
	else
	{
		Dest.target = Dest.target.normalize();

		pos += static_cast<FLOAT3>(Dest.target) * 0.7f;
		moves = true;
	}

	if (moves)
	{
		if (!Audio::isPlay(3))
		{
			Audio::play(3, false);
		}
	}
	else
	{
		Audio::stop(3);
		Audio::pause(3);
	}
}

void Player::updateDestVec(VECTOR3D forward)
{
	//　XZ平面上でのベクトル取得
	Dest.forward = { forward.x, 0, forward.z };
	Dest.forward = Dest.forward.normalize();
	Dest.back = -Dest.forward;

	Dest.right = VECTOR3D::cross(VECTOR3D(0, 1, 0), Dest.forward);
	Dest.right = Dest.right.normalize();
	Dest.left = -Dest.right;
	Dest.target = { 0,0,0 };
}

void Player::colWall()
{
	// 最小値比較用に初期値を大きく設定
	float distance = 10.0f;
	FLOAT3 hitPos[2];

	for (const auto& col : StageManager::getIns()->getColBoxs())
	{
		if (col.option != 0) continue;

		if (ColLineOBB(horizontal_lay_start, horizontal_lay_end,
			col.obb, hitPos[SAVE]))
		{
			float dist_temp = horizontal_lay_start.distanceFrom(hitPos[SAVE]);

			// 今回のレイとの接触地点が最小値より小さければ更新
			if (dist_temp < distance)
			{
				hitPos[MINIMUM] = hitPos[SAVE];
				distance = horizontal_lay_start.distanceFrom(hitPos[MINIMUM]);
			}
		}
	}

	if (distance < 5.0f)
	{
		// 押し戻し用ベクトル
		VECTOR3D vec = horizontal_lay_start - horizontal_lay_end;
		
		if(distance != 0)vec = vec.normalize();

		// 押し戻し処理
		pos = hitPos[MINIMUM] + vec * 5.0f;
		pos.y = 0;
		if (isnan(pos.x))
		{
			int hoge = 0;
		}
	}
}

void Player::colFloor()
{
	FLOAT3 hit_pos[2];
	float distance = 100.0f;

	for (const auto& col : StageManager::getIns()->getColBoxs())
	{
		if ((col.option != 1) && (col.option != 2)) continue;

		if (ColLineOBB(vertical_lay_start, vertical_lay_end,
			col.obb, hit_pos[SAVE]))
		{
			float dist_temp = vertical_lay_start.distanceFrom(hit_pos[SAVE]);
			if (dist_temp < distance) { hit_pos[MINIMUM] = hit_pos[SAVE]; }
		}
	}

	pos.y = hit_pos[MINIMUM].y;
}

void Player::restrictArea()
{
	if (pos.x > 50) { pos.x = 50; }
	if (pos.x < -50) { pos.x = -50; }
	if (pos.z > 50) { pos.z = 50; }
	if (pos.z < -50) { pos.z = -50; }
}

void Player::changeAnimation()
{
	if (moves)
	{
		if (model.GetPlayAnimationNum() != 0) { model.ChangeAnimation(0, true); }
	}
	else
	{
		if (model.GetPlayAnimationNum() != 1) { model.ChangeAnimation(1, true); }
	}
}

void Player::setAutoMode(FPSCamera& camera)
{
	if (input::STATE('G'))
	{
		attract_point = { -30.0f, 0, 0 };
		camera.setAutoFocus({ -54, 12.5f, 0 }, 0.1f);
		auto_control_timer = 0;
		auto_control_phase = AUTO_PHASE::MOVE_TO_DOOR;
		auto_control = true;
	}
}

void Player::autoControl(FPSCamera& camera)
{
	//if (auto_control_timer > 120)
	//{
	//	auto_control = false;
	//	FLOAT2 center = ToClient(GetWindowSize() / 2.0f);
	//	center.x = floorf(center.x);
	//	center.y = floorf(center.y);
	//	SetCursorPos(center.x, center.y);
	//	camera.autoFin();
	//}
	StageObject* objects = StageManager::getIns()->getStageObjects();
	VECTOR3D vec;

	switch (auto_control_phase)
	{
	case AUTO_PHASE::MOVE_TO_DOOR:

		vec = attract_point - pos;
		if (vec.length() > 0.5f)
		{
			vec = vec.normalize();
			vec.y = 0;
			pos += static_cast<FLOAT3>(vec) * 0.5f;
		}
		else { pos = attract_point; }

		if (auto_control_timer > 120)
		{
			if (objects)
			{
				for (int i = 0; i < StageData::MaxObjects; i++)
				{
					if (objects[i].ID == "spic2door.fbx")
					{
						objects[i].body.PlayAnimation(0, false);
					}
				}
			}
			pos = attract_point;
			auto_control_timer = 0;
			auto_control_phase = AUTO_PHASE::OPEN_THE_DOOR;
		}

		auto_control_timer++;
		break;

	case AUTO_PHASE::OPEN_THE_DOOR:

		if (objects)
		{
			for (int i = 0; i < StageData::MaxObjects; i++)
			{
				if (objects[i].ID == "spic2door.fbx")
				{
					objects[i].body.UpdateAnimation();
					if (!objects[i].body.IsPlayAnimation()) 
					{
						objects[i].body.PlayAnimation(1, false);
						objects[i].body.UpdateAnimation(0.0f);
						camera.setAutoFocus({ -80, 12.5f, 0 }, 0.1f);
						attract_point = { -70.0f, 0, 0 };
						auto_control_phase = AUTO_PHASE::LEAVE_THE_ROOM;
					}
					break;
				}
			}
		}
		break;

	case AUTO_PHASE::LEAVE_THE_ROOM:

		vec = attract_point - pos;
		if (vec.length() > 0.5f)
		{
			vec = vec.normalize();
			vec.y = 0;
			pos += static_cast<FLOAT3>(vec) * 0.5f;
		}
		else { pos = attract_point; }

		if (auto_control_timer > 120)
		{
			if (objects)
			{
				for (int i = 0; i < StageData::MaxObjects; i++)
				{
					if (objects[i].ID == "spic2door.fbx")
					{
						objects[i].body.PlayAnimation(1, false);
					}
				}
			}
			pos = attract_point;
			auto_control_timer = 0;
			auto_control_phase = AUTO_PHASE::CLOSE_THE_DOOR;
		}

		auto_control_timer++;
		break;

	case AUTO_PHASE::CLOSE_THE_DOOR:

		if (objects)
		{
			for (int i = 0; i < StageData::MaxObjects; i++)
			{
				if (objects[i].ID == "spic2door.fbx")
				{
					objects[i].body.UpdateAnimation();
					if (!objects[i].body.IsPlayAnimation())
					{
						objects[i].body.PlayAnimation(0, false);
						objects[i].body.UpdateAnimation(0.0f);
						auto_control_phase = AUTO_PHASE::PHASE_END;
					}
					break;
				}
			}
		}
		break;
		
	case AUTO_PHASE::PHASE_END:

		auto_control = false;
		FLOAT2 center = ToClient(GetWindowSize() / 2.0f);
		center.x = floorf(center.x);
		center.y = floorf(center.y);
		pos = { 0.5f, 0, 141.8f };
		camera.autoFin(GetWorldMatrix((pos + FLOAT3(0, 12.5f, 0)), FLOAT3(1, 1, 1), { 0,0,0 }), {pos.x, pos.y + 12.5f, pos.z});
		SetCursorPos(center.x, center.y);
	}


	//VECTOR3D vec = attract_point - pos;
	//if (vec.length() < 0.5f)return;
	//vec = vec.normalize();
	//vec.y = 0;
}


DirectX::XMMATRIX Player::getPlayerWorldMatrix()
{
	DirectX::XMMATRIX W;
	{
		DirectX::XMMATRIX S, R, T;
		S = GetScaleMatrix({ 1, 1, 1 });
		R = GetRotationMatrix({ 0,0,0 });
		T = GetPositionMatrix({ pos.x, pos.y, pos.z });

		W = S * R * T;
	}
	return W;
}