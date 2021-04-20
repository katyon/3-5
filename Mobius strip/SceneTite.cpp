#include "SceneTite.h"

//ゲームの起動時に一度だけ行う処理
//モデル・音などのロードなど
SceneTitle::SceneTitle()
{
	//Todo::ここにソースを記入する
	//player.init();
	//stage.load("Data/Objects/stage.fbx");
	//SpriteLoad(1, L"Data/Sprite/center.png");

	//コンストラクタの最後で念のための初期化を行う
	SceneTitle::Initialize();
}

//シーン変更された瞬間に実行される処理
void SceneTitle::Initialize()
{
	//camera.SetPos(FLOAT3(0, 0, -1));
	//camera.initPos();
	//camera.SetTarget({ 0, 0, 5 });
	//player.init();
}

//シーン全体の更新処理
//経過時間が渡されます
void SceneTitle::Update(float elapsed_time)
{
	/*camera.update(GetWorldMatrix((player.getPos() + FLOAT3(0, 12.5f, 0)), FLOAT3(1,1,1), {0,0,0}), { player.getPos().x, player.getPos().y + 12.5f, player.getPos().z });
	player.update(camera);
	Debug->SetString("カメラ回転中心座標 %f %f %f", player.getPos().x, player.getPos().y + 12.5f, player.getPos().z);
	Debug->SetString("カメラ座標 %f %f %f", camera.GetPos().x, camera.GetPos().y, camera.GetPos().z);
	Debug->SetString("カメラの距離 %f", FLOAT3::distanceFrom({ player.getPos().x, player.getPos().y + 12.5f, player.getPos().z },camera.GetPos()));*/
}

//シーンの描画処理
void SceneTitle::Render()
{
	//player.render(camera);
	//SkinnedMeshRender(stage, camera, GetWorldMatrix({ 0,0,0 }, { 0.1,0.1,0.1 }, { 0,0,0 }), camera.LightFloamCamera());
	//Geometric::Board(GetWorldMatrix({ 0,-1,3 }, { 1,1,1 }, { 0,0,0 }));
	//SpriteRender(1, (GetWindowSize() / 2.0f), { 0.2f, 0.2f }, { 0, 0 }, { 0, 0 }, { 300.0f, 400.0f });
}

//シーンが切り替わるタイミングで呼ばれる処理
void SceneTitle::Uninitialize()
{
}
