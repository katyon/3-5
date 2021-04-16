#include "SceneGame.h"


//ゲームの起動時に一度だけ行う処理
//モデル・音などのロードなど
SceneGame::SceneGame()
{
	//Todo::ここにソースを記入する




	//コンストラクタの最後で念のための初期化を行う
	SceneGame::Initialize();
}

//シーン変更された瞬間に実行される処理
void SceneGame::Initialize()
{
}

//シーン全体の更新処理
//経過時間が渡されます
void SceneGame::Update(float elapsed_time)
{
}

//シーンの描画処理
void SceneGame::Render()
{
}

//シーンが切り替わるタイミングで呼ばれる処理
void SceneGame::Uninitialize()
{
}
