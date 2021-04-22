#include "SceneGame.h"
#include "ButtonPush.h"
#include "menu.h"
#include "Item.h"
Menu menu;
//�Q�[���̋N�����Ɉ�x�����s������
//���f���E���Ȃǂ̃��[�h�Ȃ�
SceneGame::SceneGame() /*: pipe_puzzle()*/
{
    //Todo::�����Ƀ\�[�X���L������
    player.init();
    stage.load("Data/Objects/stage.fbx");
    SpriteLoad(1, L"Data/Sprite/center.png");
    itemObj->init();
    // �{�^���v�b�V�� ��������
    //camera.SetPos({ 0,200,-10 });
    //camera.SetTarget({ 0,0,0 });

    ButtonPush::getInstance()->init();
    // �{�^���v�b�V���@�����܂�
    camera.SetPos({ 0, 0, -30 });

    game_mode = normal;
    //�R���X�g���N�^�̍Ō�ŔO�̂��߂̏��������s��
    SceneGame::Initialize();
}

//�V�[���ύX���ꂽ�u�ԂɎ��s����鏈��
void SceneGame::Initialize()
{
    // �{�^���v�b�V�� ����͂���Ȃ�����
    //ButtonPush::getInstance()->init();
    //pipe_puzzle.Init();
    menu.init();
    M_Item->init();
    camera.SetPos(FLOAT3(0, 0, -1));
    camera.initPos();
    camera.SetTarget({ 0, 0, 5 });
    player.init();
    itemObj->init();

}

//�V�[���S�̂̍X�V����
//�o�ߎ��Ԃ��n����܂�
void SceneGame::Update(float elapsed_time)
{
    switch (game_mode)
    {
    case normal:
        // �{�^���v�b�V��
        //ButtonPush::getInstance()->update(camera);
        //pipe_puzzle.Update();
        if (input::TRG('P'))
        {
            for (int i = 0; i < screenR->max_racord; i++)
            {
                if (!screenR->records[i])
                {
                    screenR->save(i);
                    break;
                }
            }
        }

        camera.update(GetWorldMatrix((player.getPos() + FLOAT3(0, 12.5f, 0)), FLOAT3(1, 1, 1), { 0,0,0 }), { player.getPos().x, player.getPos().y + 12.5f, player.getPos().z });
        if (input::TRG(VK_TAB))
        {
            menu.isPause = true;
            menu.tab = MenuTab::Item;
            game_mode = menue;
        }
        break;

    case menue:
        if (input::TRG(VK_TAB))
        {
            game_mode = normal;
        }
        if (menu.isPause)
        {
            menu.update();
            M_Item->update();
        }
        break;
    case balance:

        break;
    }

    player.update(camera);
    itemObj->update(camera);
    Debug->SetString("�J������]���S���W %f %f %f", player.getPos().x, player.getPos().y + 12.5f, player.getPos().z);
    Debug->SetString("�J�������W %f %f %f", camera.GetPos().x, camera.GetPos().y, camera.GetPos().z);
    Debug->SetString("�J�����̋��� %f", FLOAT3::distanceFrom({ player.getPos().x, player.getPos().y + 12.5f, player.getPos().z }, camera.GetPos()));
}

//�V�[���̕`�揈��
void SceneGame::Render()
{
    switch (game_mode)
    {
    case normal:
        screenR->begin();
        player.render(camera);
        SkinnedMeshRender(stage, camera, GetWorldMatrix({ 0,0,0 }, { 0.1,0.1,0.1 }, { 0,0,0 }), camera.LightFloamCamera()); 
        SpriteRender(1, (GetWindowSize() / 2.0f), { 0.2f, 0.2f }, { 0, 0 }, { 0, 0 }, { 300.0f, 400.0f });
         screenR->end();

        break;

    case menue:
        //screenR->begin();
        if (menu.isPause)
        {
            menu.draw();
        }
        //screenR->end();
        break;
    case balance:

        break;
    }
    // �{�^���v�b�V��
    //ButtonPush::getInstance()->Render(camera);
    itemObj->render(camera);

    pipe_puzzle.Render(camera);


}


//�V�[�����؂�ւ��^�C�~���O�ŌĂ΂�鏈��
void SceneGame::Uninitialize()
{
    //pipe_puzzle.Release();
}
