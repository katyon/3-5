#include "SceneGame.h"
#include "ButtonPush.h"
#include "menu.h"
#include "Item.h"
#include "StageManager.h"
#include "OBBs.h"
#include "Balance.h"
//Menu menu;

//ゲームの起動時に一度だけ行う処理
//モデル・音などのロードなど
SceneGame::SceneGame()
{
    //Todo::ここにソースを記入する
    player.init();
    //stage.load("Data/Objects/stage.fbx");
    SpriteLoad(1, L"Data/Sprite/reticle.png");
    SpriteLoad(2, L"Data/Sprite/TAB.png");
    SpriteLoad(sprClear, L"Data/Sprite/CLEAR.png");

    Audio::load(1, L"Data/BGM/Waltz.wav");
    Audio::SetVolume(1, 0.4f);
    Audio::load(5, L"Data/BGM/menu.wav");
    Audio::SetVolume(5, 0.7f);
    itemObj->init();
    // ボタンプッシュ ここから
    camera.SetPos({ 0,200,-10 });
    camera.SetTarget({ 0,0,0 });

    ButtonPush::getInstance()->init();
    // ボタンプッシュ　ここまで
    camera.SetPos({ 0, 0, -30 });

    game_mode = normal;

    std::string fill_name[] =
    {
        "stage_data",
    };

    StageManager::getIns()->LoadStages(fill_name);
    //コンストラクタの最後で念のための初期化を行う
    //SceneGame::Initialize();
}

//シーン変更された瞬間に実行される処理
void SceneGame::Initialize()
{
    // ボタンプッシュ これはいらないかも
    ButtonPush::getInstance()->init();
    PipePuzzle::getInstance()->Init();
    Candle::getInstance()->Init();
    itemObj->init();
    M_Item->init();
    G_Item->init();
    //Libra::getInstance()->Init();
    //Balance::Init();

    menu->init();
    camera.SetPos(FLOAT3(0, 0, -1));
    camera.initPos();
    camera.SetTarget({ 0, 0, 5 });
    player.init();

    Audio::stop(0);
    Audio::play(1, true);
    ClearButoon = false;
    ClearGame = false;
    fix_cursor = false;
}

//シーン全体の更新処理
//経過時間が渡されます
void SceneGame::Update(float elapsed_time)
{
    if (ClearGame)
    {
        if (input::TRG(input::MOUSE_L))
        {
            ChangeScene(S_TITLE);
        }
        return;
    }
    //ClearGame = true;

    switch (game_mode)
    {
    case normal:
        // ボタンプッシュ
        ButtonPush::getInstance()->update(camera);
        PipePuzzle::getInstance()->Update();
        Candle::getInstance()->Update();
        itemObj->update(camera);
        G_Item->update();
        //Libra::getInstance()->Update();
        //Balance::Update();

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
        if (input::TRG(input::MOUSE_R))
        {
            fix_cursor = !fix_cursor;
            SetShowCursor(fix_cursor);
            FLOAT2 center = ToClient(GetWindowSize() / 2.0f);
            center.x = floorf(center.x);
            center.y = floorf(center.y);
            SetCursorPos(center.x, center.y);
        }
        if (input::TRG(input::MOUSE_R))
        {
            fix_cursor = !fix_cursor;
            SetShowCursor(fix_cursor);
            FLOAT2 center = ToClient(GetWindowSize() / 2.0f);
            center.x = floorf(center.x);
            center.y = floorf(center.y);
            SetCursorPos(center.x, center.y);
        }
        if (input::TRG(input::MOUSE_R))
        {
            fix_cursor = !fix_cursor;
            SetShowCursor(fix_cursor);
            FLOAT2 center = ToClient(GetWindowSize() / 2.0f);
            center.x = floorf(center.x);
            center.y = floorf(center.y);
            SetCursorPos(center.x, center.y);
        }

        if (!fix_cursor)
        {
            camera.update(GetWorldMatrix((player.getPos() + FLOAT3(0, 12.5f, 0)), FLOAT3(1, 1, 1), { 0,0,0 }), { player.getPos().x, player.getPos().y + 12.5f, player.getPos().z });
        }
        if (input::TRG(VK_TAB))
        {
            menu->tab = MenuTab::Item;
            game_mode = menue;
        }
        break;

    case menue:
        if (input::TRG(VK_TAB))
        {
            FLOAT2 center = ToClient(GetWindowSize() / 2.0f);
            center.x = floorf(center.x);
            center.y = floorf(center.y);
            SetCursorPos(center.x, center.y);
            game_mode = normal;
            Audio::play(5);
        }
        menu->update();
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
        //SkinnedMeshRender(stage, camera, GetWorldMatrix({ 0,0,0 }, { 0.1,0.1,0.1 }, { 0,0,0 }), camera.LightFloamCamera());

        camera.Active();
        //ambient->direction = camera.LightFloamCamera();
       // ambient->option.x = 0.5f;
        ambient.Active();
        StageManager::getIns()->Render();

        // ボタンプッシュ
        ButtonPush::getInstance()->Render(camera);
        itemObj->render(camera);

        PipePuzzle::getInstance()->Render(camera);
        Candle::getInstance()->Render(camera);
        //Libra::getInstance()->Render(camera);
        //Balance::Render();
        G_Item->draw();
        //cOBB(camera);
        screenR->end();

        if (ClearGame)
        {
            Animation(sprClear, 12, nowdata, 2, 2, { 0,0 }, { 1,1 }, { 0,0 }, { 1920,1080 });
        }
        else
        {
            SpriteRender(1, (GetWindowSize() / 2.0f), { 0.3f, 0.3f }, { 0, 0 }, { 256.0f, 256.0f }, { 128.0f, 128.0f });
            SpriteRender(2, { 0,0 }, { 1, 1 }, { 0, 0 }, { 1920.0f, 1080.0f });
        }
        break;

    case menue:
        Debug->SetString("ｘ座標：%f", input::GetMousePos().x);
        Debug->SetString("y座標：%f", input::GetMousePos().y);
        menu->draw();
        break;
    case balance:

        break;
    }
}


//シーンが切り替わるタイミングで呼ばれる処理
void SceneGame::Uninitialize()
{
    PipePuzzle::getInstance()->Release();
}
