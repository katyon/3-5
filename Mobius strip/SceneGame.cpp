#include "SceneGame.h"
//#include "menu.h"
//#include "Item.h"
//Menu menu;
//�Q�[���̋N�����Ɉ�x�����s������
//���f���E���Ȃǂ̃��[�h�Ȃ�
SceneGame::SceneGame()
{
	//Todo::�����Ƀ\�[�X���L������


	//�R���X�g���N�^�̍Ō�ŔO�̂��߂̏��������s��
	SceneGame::Initialize();
}

//�V�[���ύX���ꂽ�u�ԂɎ��s����鏈��
void SceneGame::Initialize()
{
    //menu.init();
    //ItemMenu::getInstance()->init();
}

//�V�[���S�̂̍X�V����
//�o�ߎ��Ԃ��n����܂�
void SceneGame::Update(float elapsed_time)
{
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
}
