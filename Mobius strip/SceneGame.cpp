#include "SceneGame.h"
#include "ButtonPush.h"

//�Q�[���̋N�����Ɉ�x�����s������
//���f���E���Ȃǂ̃��[�h�Ȃ�
SceneGame::SceneGame()
{
	//Todo::�����Ƀ\�[�X���L������

	// �{�^���v�b�V�� ��������
	//camera.SetPos({ 0,200,-10 });
	//camera.SetTarget({ 0,0,0 });

	//ButtonPush::getInstance()->init();
	// �{�^���v�b�V���@�����܂�

	//�R���X�g���N�^�̍Ō�ŔO�̂��߂̏��������s��
	SceneGame::Initialize();
}

//�V�[���ύX���ꂽ�u�ԂɎ��s����鏈��
void SceneGame::Initialize()
{
	// �{�^���v�b�V�� ����͂���Ȃ�����
	//ButtonPush::getInstance()->init();
}

//�V�[���S�̂̍X�V����
//�o�ߎ��Ԃ��n����܂�
void SceneGame::Update(float elapsed_time)
{
	// �{�^���v�b�V��
	//ButtonPush::getInstance()->update(camera);
}

//�V�[���̕`�揈��
void SceneGame::Render()
{
	// �{�^���v�b�V��
	//ButtonPush::getInstance()->Render(camera);
}

//�V�[�����؂�ւ��^�C�~���O�ŌĂ΂�鏈��
void SceneGame::Uninitialize()
{
}
