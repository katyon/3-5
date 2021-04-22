#include "SceneGame.h"
#include "ButtonPush.h"
#include "menu.h"
#include "Item.h"
Menu menu;
//ゲームの起動時に一度だけ行う処理
//モデル・音などのロードなど
SceneGame::SceneGame() /*: pipe_puzzle()*/
{
    //Todo::ここにソースを記入する
    player.init();
    stage.load("Data/Objects/stage.fbx");
    SpriteLoad(1, L"Data/Sprite/center.png");
    itemObj->init();
    // ボタンプッシュ ここから
    camera.SetPos({ 0,200,-10 });
    camera.SetTarget({ 0,0,0 });

    ButtonPush::getInstance()->init();
    // ボタンプッシュ　ここまで
    camera.SetPos({ 0, 0, -30 });

    game_mode = normal;
    //コンストラクタの最後で念のための初期化を行う
    SceneGame::Initialize();
}

//シーン変更された瞬間に実行される処理
void SceneGame::Initialize()
{
    // ボタンプッシュ これはいらないかも
    ButtonPush::getInstance()->init();
    pipe_puzzle.Init();
    itemObj->init();
    M_Item->init();
    menu.init();
    camera.SetPos(FLOAT3(0, 0, -1));
    camera.initPos();
    camera.SetTarget({ 0, 0, 5 });
    player.init();

}

//シーン全体の更新処理
//経過時間が渡されます
void SceneGame::Update(float elapsed_time)
{
    switch (game_mode)
    {
    case normal:
        // ボタンプッシュ
        ButtonPush::getInstance()->update(camera);
        pipe_puzzle.Update();
        itemObj->update(camera);
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
        }
        break;
    case balance:

        break;
    }

    player.update(camera);
    Debug->SetString("カメラ回転中心座標 %f %f %f", player.getPos().x, player.getPos().y + 12.5f, player.getPos().z);
    Debug->SetString("カメラ座標 %f %f %f", camera.GetPos().x, camera.GetPos().y, camera.GetPos().z);
    Debug->SetString("カメラの距離 %f", FLOAT3::distanceFrom({ player.getPos().x, player.getPos().y + 12.5f, player.getPos().z }, camera.GetPos()));
}

//シーンの描画処理
void SceneGame::Render()
{
    switch (game_mode)
    {
    case normal:
        screenR->begin();
        player.render(camera);
        SkinnedMeshRender(stage, camera, GetWorldMatrix({ 0,0,0 }, { 0.1,0.1,0.1 }, { 0,0,0 }), camera.LightFloamCamera());

        // ボタンプッシュ
        ButtonPush::getInstance()->Render(camera);
        itemObj->render(camera);

        pipe_puzzle.Render(camera);

        screenR->end();

        SpriteRender(1, (GetWindowSize() / 2.0f), { 0.2f, 0.2f }, { 0, 0 }, { 0, 0 }, { 300.0f, 400.0f });
        break;

    case menue:
        Debug->SetString("ｘ座標：%f", input::GetMousePos().x);
        Debug->SetString("y座標：%f", input::GetMousePos().y);
        if (menu.isPause)
        {
            menu.draw();
        }
        break;
    case balance:

        break;
    }
}


//シーンが切り替わるタイミングで呼ばれる処理
void SceneGame::Uninitialize()
{
    pipe_puzzle.Release();
}
