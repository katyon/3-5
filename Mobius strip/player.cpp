#include "player.h"

Player::Player() : pos(0, 0, 0), scale(0.1f, 0.1f, 0.1f)
{
	model.load("Data/actor/chara.fbx");
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
	Dest.back = -Dest.forward;

	Dest.right = VECTOR3D::cross(VECTOR3D(0, 1, 0), Dest.forward);
	Dest.right = Dest.right.normalize();
	Dest.left = -Dest.right;
	Dest.target = { 0,0,0 };
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