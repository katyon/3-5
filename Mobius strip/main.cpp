/********************************************************************/
/*							インクルード							*/
/********************************************************************/
#include "./AliceLib/AliceLib.h"
#include "./AliceLib/loop.h"
/********************************************************************/
/*							プロトタイプ宣言						*/
/********************************************************************/
#include "StageEditor.h"
//#define TEST_OPENAL
#ifdef TEST_OPENAL
#include "AL_Sound.h"
#endif // TEST_OPENAL
void TyDamoPlay();
#include "StageManager.h"
#include "Balance.h"
#include "ScreenRecord.h"
#include "menu.h"
#include "Item.h"
Menu menu;
ItemArr itemArr;
/********************************************************************/

INT WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, INT)
{
    //ライブラリの初期化処理
    AliceLib::Entry(L"AliceLib", 1920, 1080, DefaultWindowMode::WM_FULLSCREEN, 60);

    //複数箇所で使うため用意しておいたほうがいい
    int scene = AliceLib::GetNowScene();

    //ゲームループ
    while (Function::GameLoop())
    {
        //現在のシーンを取得する
        scene = AliceLib::GetNowScene();

        //前のシーンと現在のシーンが違うとき
        if (AliceLib::InitFlg())
        {
            //初期化処理
            switch (scene)
            {
            default:
                break;
            case 0:
                menu.init();
                //itemlist.init();
                break;
            }
        }

        //更新処理
        switch (scene)
        {
        default:
            break;
        case 0:
           menu.update();
           //itemlist.update();
            break;
        }

        //描画処理
        switch (scene)
        {
        default:
            break;
        case 0:
            menu.draw();
            //itemlist.draw(&menu);
            break;
        }

        //シーンが変更されるとき
        if (AliceLib::EndFlg())
        {
            //終了処理
            switch (scene)
            {
            default:
                break;
            case 0:
                break;
            }
        }

        //バックバッファに送信
        AliceLib::Present(0u, 0u);

    }

    //ライブラリの終了処理
    return AliceLib::Exit();
}