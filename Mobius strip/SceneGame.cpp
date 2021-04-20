#include "SceneGame.h"
#include "ButtonPush.h"

//#include "menu.h"
//#include "Item.h"
//Menu menu;
//ゲームの起動時に一度だけ行う処理
//モデル・音などのロードなど
SceneGame::SceneGame() /*: pipe_puzzle()*/
{
	//Todo::ここにソースを記入する

	// ボタンプッシュ ここから
	//camera.SetPos({ 0,200,-10 });
	//camera.SetTarget({ 0,0,0 });

	//ButtonPush::getInstance()->init();
	// ボタンプッシュ　ここまで
	camera.SetPos({ 0, 0, -30 });

	//コンストラクタの最後で念のための初期化を行う
	SceneGame::Initialize();
}

//シーン変更された瞬間に実行される処理
void SceneGame::Initialize()
{
	// ボタンプッシュ これはいらないかも
	//ButtonPush::getInstance()->init();
	pipe_puzzle.Init();
    //menu.init();
    //ItemMenu::getInstance()->init();
}

//シーン全体の更新処理
//経過時間が渡されます
void SceneGame::Update(float elapsed_time)
{
	// ボタンプッシュ
	//ButtonPush::getInstance()->update(camera);
	pipe_puzzle.Update();
   // if (input::TRG('P'))
   // {
   //     for (int i = 0; i < screenR->max_racord; i++)
   //     {
   //         if (!screenR->records[i])
   //         {
   //             screenR->save(i);
   //         }
   //     }
   // }
   // if (input::TRG(VK_TAB))
   // {
   //     menu.isPause = true;
   // }
   // if (menu.isPause)
   // {
   //     menu.update();
   //     ItemMenu::getInstance()->update();
   //}
}

//シーンの描画処理
void SceneGame::Render()
{
	// ボタンプッシュ
	//ButtonPush::getInstance()->Render(camera);
	pipe_puzzle.Render(camera);
   // screenR->begin();
   // Debug->SetString("マウスカーソル.x::%f", input::GetMousePos().x);
   // Debug->SetString("マウスカーソル.y::%f", input::GetMousePos().y);
   // if (menu.isPause)
   // {
   //     menu.draw();
   // }
   // screenR->end();
}


//シーンが切り替わるタイミングで呼ばれる処理
void SceneGame::Uninitialize()
{
	pipe_puzzle.Release();
}
