#include "SceneTite.h"
#include "common.h"
//�Q�[���̋N�����Ɉ�x�����s������
//���f���E���Ȃǂ̃��[�h�Ȃ�
SceneTitle::SceneTitle()
{
	//Todo::�����Ƀ\�[�X���L������
	Audio::load(0, L"./Data/BGM/BGM.wav");
	//�R���X�g���N�^�̍Ō�ŔO�̂��߂̏��������s��
	//SceneTitle::Initialize();
}

//�V�[���ύX���ꂽ�u�ԂɎ��s����鏈��
void SceneTitle::Initialize()
{
	Audio::stop(1);

	//Audio::SetVolume(0, 0.5f);
	Audio::play(0, true);
}

//�V�[���S�̂̍X�V����
//�o�ߎ��Ԃ��n����܂�
void SceneTitle::Update(float elapsed_time)
{
	if (input::TRG(input::MOUSE_L))
	{
		ChangeScene(S_GAME);
	}

}

//�V�[���̕`�揈��
void SceneTitle::Render()
{
}


//�V�[�����؂�ւ��^�C�~���O�ŌĂ΂�鏈��
void SceneTitle::Uninitialize()
{
	Audio::stop(0);
	//Audio::unload(0);
}
