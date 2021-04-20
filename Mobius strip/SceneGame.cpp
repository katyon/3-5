#include "SceneGame.h"



//�Q�[���̋N�����Ɉ�x�����s������
//���f���E���Ȃǂ̃��[�h�Ȃ�
SceneGame::SceneGame() /*: pipe_puzzle()*/
{
	//Todo::�����Ƀ\�[�X���L������
	camera.SetPos({ 0, 0, -30 });

	//�R���X�g���N�^�̍Ō�ŔO�̂��߂̏��������s��
	SceneGame::Initialize();
}

//�V�[���ύX���ꂽ�u�ԂɎ��s����鏈��
void SceneGame::Initialize()
{
	pipe_puzzle.Init();
}

//�V�[���S�̂̍X�V����
//�o�ߎ��Ԃ��n����܂�
void SceneGame::Update(float elapsed_time)
{
	pipe_puzzle.Update();
}

//�V�[���̕`�揈��
void SceneGame::Render()
{
	pipe_puzzle.Render(camera);
}

//�V�[�����؂�ւ��^�C�~���O�ŌĂ΂�鏈��
void SceneGame::Uninitialize()
{
	pipe_puzzle.Release();
}
