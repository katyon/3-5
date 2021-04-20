#include "SceneGame.h"



//ゲームの起動時に一度だけ行う処理
//モデル・音などのロードなど
SceneGame::SceneGame() /*: pipe_puzzle()*/
{
	//Todo::ここにソースを記入する
	camera.SetPos({ 0, 0, -30 });

	//コンストラクタの最後で念のための初期化を行う
	SceneGame::Initialize();
}

//シーン変更された瞬間に実行される処理
void SceneGame::Initialize()
{
	pipe_puzzle.Init();
}

//シーン全体の更新処理
//経過時間が渡されます
void SceneGame::Update(float elapsed_time)
{
	pipe_puzzle.Update();
}

//シーンの描画処理
void SceneGame::Render()
{
	pipe_puzzle.Render(camera);
}

//シーンが切り替わるタイミングで呼ばれる処理
void SceneGame::Uninitialize()
{
	pipe_puzzle.Release();
}
