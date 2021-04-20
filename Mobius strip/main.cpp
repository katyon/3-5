/********************************************************************/
/*							インクルード							*/
/********************************************************************/
#include "./AliceLib/AliceLib.h"
#include "./AliceLib/Loop.h"
#include <thread>
/********************************************************************/
/*							プロトタイプ宣言						*/
/********************************************************************/

#include "SceneTite.h"
#include "SceneGame.h"
#include "common.h"

/********************************************************************/

void _AllInitializes(bool* isFin)
{
	*isFin = false;
	SceneGame::getInstance();
	SceneTitle::getInstance();
	*isFin = true;
}

void AllInitializes()
{
	bool isFin = false;
	//マルチスレッド開始
	std::thread th(_AllInitializes, &isFin);
	th.detach();
	while (isFin)
	{
		//Todo:: なうろーでぃんぐ的な
	}
}


/*
	※ ここから下は触らないこと!!! ※
*/
INT WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, INT)
{
	//ライブラリの初期化処理
	AliceLib::Entry(L"AliceLib", 1920, 1080, DefaultWindowMode::WM_FULLSCREEN, 60);

	AllInitializes();

	//複数箇所で使うため用意しておいたほうがいい
	int scene = AliceLib::GetNowScene();

	//getInstanceを毎回呼ばなくなるので
	//パフォーマンスが少しだけよくなる
	SceneTitle* scene_title	=	SceneTitle::getInstance();
	SceneGame*	scene_game	=	SceneGame::getInstance();
#if _DEBUG	//デバッグ文字表示用
	debug* _debug			=	Debug;
#endif

	float elapsed_time = 0.0f;

	//ゲームループ
	while (Function::GameLoop())
	{
		//現在のシーンを取得する
		scene = AliceLib::GetNowScene();
		elapsed_time = DeltaTime();

		//前のシーンと現在のシーンが違うとき
		if (AliceLib::InitFlg())
		{
			//初期化処理
			switch (scene)
			{
			case S_TITLE:
				scene_title->Initialize();
				break;
			case S_GAME:
				scene_game->Initialize();
				break;
			}
		}

		//更新処理
		switch (scene)
		{
		case S_TITLE:
			scene_title->Update(elapsed_time);
			break;
		case S_GAME:
			scene_game->Update(elapsed_time);
			break;
		}

		//描画処理
		switch (scene)
		{
		case S_TITLE:
			scene_title->Render();
			break;
		case S_GAME:
			scene_game->Render();
			break;
		}

		//シーンが変更されるとき
		if (AliceLib::EndFlg())
		{
			//終了処理
			switch (scene)
			{
			case S_TITLE:
				scene_title->Uninitialize();
				break;
			case S_GAME:
				scene_game->Uninitialize();
				break;
			}
		}

#if _DEBUG //デバッグ文字表示用
		_debug->display();
#endif

		//バックバッファに送信
		AliceLib::Present(0u, 0u);

	}

	//念のための終了処理
	scene_title->Uninitialize();
	scene_game->Uninitialize();

	//ライブラリの終了処理
	return AliceLib::Exit();
}
