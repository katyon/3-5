#include "SceneTite.h"
#include "common.h"
//ゲームの起動時に一度だけ行う処理
//モデル・音などのロードなど
SceneTitle::SceneTitle()
{
	//Todo::ここにソースを記入する
	title.load("Data/Objects/title.fbx");
	Audio::load(0, L"./Data/BGM/BGM.wav");
	//コンストラクタの最後で念のための初期化を行う
	//SceneTitle::Initialize();
}

//シーン変更された瞬間に実行される処理
void SceneTitle::Initialize()
{
	cPos = { 35.5,14,13.5 };
	cTarget = { -141.5,-5.5,7 };
	title_pos = { 0,0,0 };
	//ChangeScene(1);
	Audio::stop(1);

	//Audio::SetVolume(0, 0.5f);
	Audio::play(0, true);
}

//シーン全体の更新処理
//経過時間が渡されます
void SceneTitle::Update(float elapsed_time)
{	
	//if (input::STATE('A'))
	//{
	//	cPos.x += 0.5f;
	//}
	//if (input::STATE('D'))
	//{
	//	cPos.x -= 0.5f;
	//}
	//if (input::STATE('W'))
	//{
	//	cPos.y += 0.5f;
	//}
	//if (input::STATE('S'))
	//{
	//	cPos.y -= 0.5f;
	//}	
	//if (input::STATE('Q'))
	//{
	//	cPos.z += 0.5f;
	//}
	//if (input::STATE('E'))
	//{		
	//	cPos.z -= 0.5f;
	//}

	//if (input::STATE('J'))
	//{
	//	cTarget.x += 0.5f;
	//}
	//if (input::STATE('L'))
	//{
	//	cTarget.x -= 0.5f;
	//}
	//if (input::STATE('I'))
	//{
	//	cTarget.y += 0.5f;
	//}
	//if (input::STATE('K'))
	//{
	//	cTarget.y -= 0.5f;
	//}
	//if (input::STATE('U'))
	//{
	//	cTarget.z += 0.5f;
	//}
	//if (input::STATE('O'))
	//{
	//	cTarget.z -= 0.5f;
	//}

	camera.SetPos(cPos);
	camera.SetTarget(cTarget);

	if (input::TRG(input::MOUSE_L))
	{
		ChangeScene(S_GAME);
	}

}

//シーンの描画処理
void SceneTitle::Render()
{
	Debug->SetString("X:%f\nY:%f\nZ:%fTarget\nX:%f\nY:%f\nZ:%f", cPos.x, cPos.y, cPos.z, cTarget.x, cTarget.y, cTarget.z);

	SkinnedMeshRender(title, camera, title_pos, FLOAT3(0.1, 0.1, 0.1), title_posture, camera.LightFloamCamera());
}


//シーンが切り替わるタイミングで呼ばれる処理
void SceneTitle::Uninitialize()
{
	Audio::stop(0);
	//Audio::unload(0);
}
