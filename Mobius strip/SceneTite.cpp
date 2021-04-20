#include "SceneTite.h"

//ゲームの起動時に一度だけ行う処理
//モデル・音などのロードなど
SceneTitle::SceneTitle()
{
	//Todo::ここにソースを記入する

	//コンストラクタの最後で念のための初期化を行う
	SceneTitle::Initialize();
}

//シーン変更された瞬間に実行される処理
void SceneTitle::Initialize()
{
}

//シーン全体の更新処理
//経過時間が渡されます
void SceneTitle::Update(float elapsed_time)
{
}

//シーンの描画処理
void SceneTitle::Render()
{
}

//シーンが切り替わるタイミングで呼ばれる処理
void SceneTitle::Uninitialize()
{
}
