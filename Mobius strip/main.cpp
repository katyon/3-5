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
	//*isFin = false;
	SceneGame::getInstance();
	SceneTitle::getInstance();
	*isFin = true;
}

void AllInitializes()
{
	bool isFin = false;
	Shaders flame;
	flame.LoadPixelShader("Data/shader/flame_ps.cso");
	struct cBuffer
	{
		FLOAT3	size;
		float	time;
	};
	ConstantBuffer<cBuffer> flame_constant;
	flame_constant->size = FLOAT3(GetWindowSize(), 0.0f);
	flame_constant->time = 0.0f;
	//マルチスレッド開始
	std::thread th(_AllInitializes, &isFin);
	th.detach();
	while (Function::GameLoop())
	{
		if (isFin) return;
		//Todo:: なうろーでぃんぐ的な
		flame_constant->time += DeltaTime();
		flame_constant.Active(0, 0, 1);
		flame.SetPSSharders();
		FullScreenQuadBlit();
		font::OutPut(L"なうろーでぃんぐ(仮)",0,0);

		AliceLib::Present(1, 0);
	}
}


/*
    ※ ここから下は触らないこと!!! ※
*/
INT WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, INT)
{
	//ライブラリの初期化処理
	AliceLib::Entry(L"AliceLib", 1280, 720, DefaultWindowMode::WM_WINDOW, 60);

    AllInitializes();

    //複数箇所で使うため用意しておいたほうがいい
    int scene = AliceLib::GetNowScene();

    //getInstanceを毎回呼ばなくなるので
    //パフォーマンスが少しだけよくなる
    SceneTitle* scene_title = SceneTitle::getInstance();
    SceneGame* scene_game = SceneGame::getInstance();
#if _DEBUG	//デバッグ文字表示用
    debug* _debug = Debug;
#endif


	float elapsed_time = 0.0f;

	//ゲームループ
	while (Function::GameLoop())
	{
		//現在のシーンを取得する
		scene = AliceLib::GetNowScene();
		elapsed_time = DeltaTime();
#if _DEBUG
		ImGuiNewFrame();
		{
			static bool isOpen = false;
			if (input::SWICH(input::F1, isOpen))
			{
				ImGui::Begin("SceneChanger", &isOpen);
				switch (scene)
				{
				case S_TITLE:
					ImGui::Text("Current Scene :: Title");
					break;
				case S_GAME:
					ImGui::Text("Current Scene :: Game");
					break;
				}
				if (ImGui::Button("Title"))
				{
					ChangeScene(S_TITLE);
				}
				ImGui::SameLine();
				if (ImGui::Button("Game"))
				{
					ChangeScene(S_GAME);
				}
				ImGui::End();
			}
		}
#endif
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
		ImGuiRender();
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
