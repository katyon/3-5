#include "SceneTite.h"
#include "common.h"
//�Q�[���̋N�����Ɉ�x�����s������
//���f���E���Ȃǂ̃��[�h�Ȃ�
SceneTitle::SceneTitle()
{
	//Todo::�����Ƀ\�[�X���L������
	title.load("Data/Objects/title.fbx");
	Audio::load(0, L"./Data/BGM/BGM.wav");
	//�R���X�g���N�^�̍Ō�ŔO�̂��߂̏��������s��
	//SceneTitle::Initialize();
}

//�V�[���ύX���ꂽ�u�ԂɎ��s����鏈��
void SceneTitle::Initialize()
{
	cPos = { 35.5,14,13.5 };
	cTarget = { -141.5,-5.5,7 };
	title_pos = { 0,0,0 };
	//ChangeScene(1);
	Audio::stop(1);

	//Audio::SetVolume(0, 0.5f);
	Audio::play(0, true);
}

//�V�[���S�̂̍X�V����
//�o�ߎ��Ԃ��n����܂�
void SceneTitle::Update(float elapsed_time)
{	
	//if (input::STATE('A'))
	//{
	//	cPos.x += 0.5f;
	//}
	//if (input::STATE('D'))
	//{
	//	cPos.x -= 0.5f;
	//}
	//if (input::STATE('W'))
	//{
	//	cPos.y += 0.5f;
	//}
	//if (input::STATE('S'))
	//{
	//	cPos.y -= 0.5f;
	//}	
	//if (input::STATE('Q'))
	//{
	//	cPos.z += 0.5f;
	//}
	//if (input::STATE('E'))
	//{		
	//	cPos.z -= 0.5f;
	//}

	//if (input::STATE('J'))
	//{
	//	cTarget.x += 0.5f;
	//}
	//if (input::STATE('L'))
	//{
	//	cTarget.x -= 0.5f;
	//}
	//if (input::STATE('I'))
	//{
	//	cTarget.y += 0.5f;
	//}
	//if (input::STATE('K'))
	//{
	//	cTarget.y -= 0.5f;
	//}
	//if (input::STATE('U'))
	//{
	//	cTarget.z += 0.5f;
	//}
	//if (input::STATE('O'))
	//{
	//	cTarget.z -= 0.5f;
	//}

	camera.SetPos(cPos);
	camera.SetTarget(cTarget);

	if (input::TRG(input::MOUSE_L))
	{
		ChangeScene(S_GAME);
	}

}

//�V�[���̕`�揈��
void SceneTitle::Render()
{
	Debug->SetString("X:%f\nY:%f\nZ:%fTarget\nX:%f\nY:%f\nZ:%f", cPos.x, cPos.y, cPos.z, cTarget.x, cTarget.y, cTarget.z);

	SkinnedMeshRender(title, camera, title_pos, FLOAT3(0.1, 0.1, 0.1), title_posture, camera.LightFloamCamera());
}


//�V�[�����؂�ւ��^�C�~���O�ŌĂ΂�鏈��
void SceneTitle::Uninitialize()
{
	Audio::stop(0);
	//Audio::unload(0);
}
