#include "SceneTite.h"

//�Q�[���̋N�����Ɉ�x�����s������
//���f���E���Ȃǂ̃��[�h�Ȃ�
SceneTitle::SceneTitle()
{
	//Todo::�����Ƀ\�[�X���L������
	//player.init();
	//stage.load("Data/Objects/stage.fbx");
	//SpriteLoad(1, L"Data/Sprite/center.png");

	//�R���X�g���N�^�̍Ō�ŔO�̂��߂̏��������s��
	SceneTitle::Initialize();
}

//�V�[���ύX���ꂽ�u�ԂɎ��s����鏈��
void SceneTitle::Initialize()
{
	//camera.SetPos(FLOAT3(0, 0, -1));
	//camera.initPos();
	//camera.SetTarget({ 0, 0, 5 });
	//player.init();
}

//�V�[���S�̂̍X�V����
//�o�ߎ��Ԃ��n����܂�
void SceneTitle::Update(float elapsed_time)
{
	/*camera.update(GetWorldMatrix((player.getPos() + FLOAT3(0, 12.5f, 0)), FLOAT3(1,1,1), {0,0,0}), { player.getPos().x, player.getPos().y + 12.5f, player.getPos().z });
	player.update(camera);
	Debug->SetString("�J������]���S���W %f %f %f", player.getPos().x, player.getPos().y + 12.5f, player.getPos().z);
	Debug->SetString("�J�������W %f %f %f", camera.GetPos().x, camera.GetPos().y, camera.GetPos().z);
	Debug->SetString("�J�����̋��� %f", FLOAT3::distanceFrom({ player.getPos().x, player.getPos().y + 12.5f, player.getPos().z },camera.GetPos()));*/
}

//�V�[���̕`�揈��
void SceneTitle::Render()
{
	//player.render(camera);
	//SkinnedMeshRender(stage, camera, GetWorldMatrix({ 0,0,0 }, { 0.1,0.1,0.1 }, { 0,0,0 }), camera.LightFloamCamera());
	//Geometric::Board(GetWorldMatrix({ 0,-1,3 }, { 1,1,1 }, { 0,0,0 }));
	//SpriteRender(1, (GetWindowSize() / 2.0f), { 0.2f, 0.2f }, { 0, 0 }, { 0, 0 }, { 300.0f, 400.0f });
}

//�V�[�����؂�ւ��^�C�~���O�ŌĂ΂�鏈��
void SceneTitle::Uninitialize()
{
}
