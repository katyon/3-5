#include "SceneGame.h"
#include "ButtonPush.h"

//#include "menu.h"
//#include "Item.h"
//Menu menu;
//�Q�[���̋N�����Ɉ�x�����s������
//���f���E���Ȃǂ̃��[�h�Ȃ�
SceneGame::SceneGame() /*: pipe_puzzle()*/
{
	//Todo::�����Ƀ\�[�X���L������

	// �{�^���v�b�V�� ��������
	//camera.SetPos({ 0,200,-10 });
	//camera.SetTarget({ 0,0,0 });

	//ButtonPush::getInstance()->init();
	// �{�^���v�b�V���@�����܂�
	camera.SetPos({ 0, 0, -30 });

	//�R���X�g���N�^�̍Ō�ŔO�̂��߂̏��������s��
	SceneGame::Initialize();
}

//�V�[���ύX���ꂽ�u�ԂɎ��s����鏈��
void SceneGame::Initialize()
{
	// �{�^���v�b�V�� ����͂���Ȃ�����
	//ButtonPush::getInstance()->init();
	pipe_puzzle.Init();
    //menu.init();
    //ItemMenu::getInstance()->init();
}

//�V�[���S�̂̍X�V����
//�o�ߎ��Ԃ��n����܂�
void SceneGame::Update(float elapsed_time)
{
	// �{�^���v�b�V��
	//ButtonPush::getInstance()->update(camera);
	pipe_puzzle.Update();
   // if (input::TRG('P'))
   // {
   //     for (int i = 0; i < screenR->max_racord; i++)
   //     {
   //         if (!screenR->records[i])
   //         {
   //             screenR->save(i);
   //         }
   //     }
   // }
   // if (input::TRG(VK_TAB))
   // {
   //     menu.isPause = true;
   // }
   // if (menu.isPause)
   // {
   //     menu.update();
   //     ItemMenu::getInstance()->update();
   //}
}

//�V�[���̕`�揈��
void SceneGame::Render()
{
	// �{�^���v�b�V��
	//ButtonPush::getInstance()->Render(camera);
	pipe_puzzle.Render(camera);
   // screenR->begin();
   // Debug->SetString("�}�E�X�J�[�\��.x::%f", input::GetMousePos().x);
   // Debug->SetString("�}�E�X�J�[�\��.y::%f", input::GetMousePos().y);
   // if (menu.isPause)
   // {
   //     menu.draw();
   // }
   // screenR->end();
}


//�V�[�����؂�ւ��^�C�~���O�ŌĂ΂�鏈��
void SceneGame::Uninitialize()
{
	pipe_puzzle.Release();
}
