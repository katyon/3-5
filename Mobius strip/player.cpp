#include "player.h"
#include "StageManager.h"

Player::Player() : pos(0, 0, 0), scale(0.1f, 0.1f, 0.1f)
{
	model.load("Data/actor/chara_anime.fbx");
}

void Player::init()
{
	world_matrix = GetWorldMatrix(pos, scale, posture);
}

void Player::update(const Camera& camera)
{
	world_matrix = GetWorldMatrix(pos, scale, posture);
	posture_vec.CreateVector(posture);
	updateDestVec(camera.GetTarget() - camera.GetPos());
	move(camera);
	horizontal_lay_start = pos + FLOAT3(0, 4.5f, 0);
	horizontal_lay_end = horizontal_lay_start + (Dest.target * 30.0f);
	vertical_lay_start = pos + FLOAT3(0, 1.0f, 0);
	vertical_lay_end = vertical_lay_start + FLOAT3(0, 3.0f, 0);
	Debug->SetString("horizontal_lay_start %f %f %f", horizontal_lay_start.x, horizontal_lay_start.y, horizontal_lay_start.z);
	Debug->SetString("horizontal_lay_end %f %f %f", horizontal_lay_end.x, horizontal_lay_end.y, horizontal_lay_end.z);

	colWall();
}

void Player::render(const Camera& camera)
{
	SkinnedMeshRender(model, camera, GetWorldMatrix(pos - (camera.GetTarget() - camera.GetPos()), scale,posture), camera.LightFloamCamera());
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

	for (auto& obb : StageManager::getIns()->GetObbs())
	{
		Debug->SetString("OBBpos %f %f %f", obb.pos.x, obb.pos.y, obb.pos.z);
		Debug->SetString("OBBscale %f %f %f", obb.len.x, obb.len.y, obb.len.z);
		Debug->SetString("OBBpos forward:%f right:%f up:%f", obb.direct.forward, obb.direct.right, obb.direct.up);
		if (ColLineOBB(horizontal_lay_start, horizontal_lay_end,
			obb, hitPos[SAVE]))
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
		VECTOR3D vec = horizontal_lay_start - hitPos[MINIMUM];
		vec = vec.normalize();

		// 押し戻し処理
		pos = hitPos[MINIMUM] + vec*5.0f;
		pos.y = 0;
	}
}

void Player::colFloor()
{
	FLOAT3 hit_pos;
	for (auto& obb : StageManager::getIns()->GetObbs())
	{
		if (ColLineOBB(vertical_lay_start, vertical_lay_end,
			obb, hit_pos))
		{

		}
	}
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