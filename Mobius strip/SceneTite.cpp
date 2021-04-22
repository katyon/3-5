#include "SceneTite.h"
#include "common.h"
//ゲームの起動時に一度だけ行う処理
//モデル・音などのロードなど
SceneTitle::SceneTitle()
{
	//Todo::ここにソースを記入する
	Audio::load(0, L"./Data/BGM/BGM.wav");
	//コンストラクタの最後で念のための初期化を行う
	//SceneTitle::Initialize();
}

//シーン変更された瞬間に実行される処理
void SceneTitle::Initialize()
{
	Audio::stop(1);

	//Audio::SetVolume(0, 0.5f);
	Audio::play(0, true);
}

//シーン全体の更新処理
//経過時間が渡されます
void SceneTitle::Update(float elapsed_time)
{
	if (input::TRG(input::MOUSE_L))
	{
		ChangeScene(S_GAME);
	}

}

//シーンの描画処理
void SceneTitle::Render()
{
}


//シーンが切り替わるタイミングで呼ばれる処理
void SceneTitle::Uninitialize()
{
	Audio::stop(0);
	//Audio::unload(0);
}
