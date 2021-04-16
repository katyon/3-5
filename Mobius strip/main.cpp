﻿/********************************************************************/
/*							インクルード							*/
/********************************************************************/
#include "./AliceLib/AliceLib.h"
#include "./AliceLib/Loop.h"
/********************************************************************/
/*							プロトタイプ宣言						*/
/********************************************************************/

void ShDemoPlay();
#include "StageEditor.h"
//#define TEST_OPENAL
#ifdef TEST_OPENAL
#include "AL_Sound.h"
#endif // TEST_OPENAL
void TyDamoPlay();
#include "StageManager.h"
#include "Balance.h"
#include "ScreenRecord.h"
#include "PipePuzzle.h"
#include "player.h"
#include "menu.h"
#include "Item.h"
Menu menu;
<<<<<<< HEAD
ItemArr itemArr;
=======
//PipePuzzle pp; 
>>>>>>> 3aa77a5163f9ffafb6f01e1c3798edf9a94b17b4
/********************************************************************/

INT WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, INT)
{
<<<<<<< HEAD
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
=======
	//ライブラリの初期化処理
	AliceLib::Entry(L"AliceLib", 1280, 720, DefaultWindowMode::WM_WINDOW, 60);

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
				break;
			}
		}

		//更新処理
		switch (scene)
		{
		default:
			break;
		case 0:
			break;
		}

		//描画処理
		switch (scene)
		{
		default:
			break;
		case 0:
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
	//pp.Init();
		while (Function::GameLoop())
		{
			//pp.run();
			AliceLib::Present(0u, 0u);

		}

		//ライブラリの終了処理
		return AliceLib::Exit();
	}
}


// ---kiira_develop---
// 
//SpriteLoad(1, L"Data/Sprite/center.png");
//Camera camera;
//camera.SetPos({ 0, 0, -30 });

//Player player;
//player.init();


//player.update();
//camera.SetTarget({ 0.0f,5.0f,0.0f });
//
//player.render(camera);
//
//FLOAT2 center = ToClient(GetWindowSize() / 2.0f);
//SetCursorPos(center.x, center.y);
//
//SpriteRender(1, (GetWindowSize() / 2.0f), { 0.2f, 0.2f }, { 0, 0 }, { 0, 0 }, { 300.0f, 400.0f });
//--------------------------
>>>>>>> 3aa77a5163f9ffafb6f01e1c3798edf9a94b17b4
