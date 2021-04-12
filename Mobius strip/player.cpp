#include "player.h"

Player::Player() : pos(0, 0, 0), scale(0.1f, 0.1f, 0.1f)
{
	model.load("Data/actor/chara.fbx");
}

void Player::init()
{
	world_matrix = GetWorldMatrix(pos, scale, posture);
}

void Player::update()
{
	posture_vec.CreateVector(posture);
}

void Player::render(const Camera& camera)
{
	SkinnedMeshRender(model, camera, world_matrix, camera.LightFloamCamera());
}