/********************************************************************/
/*							インクルード							*/
/********************************************************************/
#include "./AliceLib/AliceLib.h"
#include "./AliceLib/loop.h"
/********************************************************************/
/*							プロトタイプ宣言						*/
/********************************************************************/
#include "StageEditor.h"
//#define TEST_OPENAL
#ifdef TEST_OPENAL
#include "AL_Sound.h"
#endif // TEST_OPENAL
void TyDamoPlay();
#include "StageManager.h"
#include "Balance.h"
#include "ScreenRecord.h"
#include "player.h"
/********************************************************************/

INT WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, INT)
{
	
	AliceLib::Entry(L"AliceLib", 1280, 720, DefaultWindowMode::WM_WINDOW, 60);

	//SpriteLoad(1, L"Data/Sprite/center.png");
	//Camera camera;
	//camera.SetPos({ 0, 0, -30 });

	//Player player;
	//player.init();

	while (Function::GameLoop())
	{
		/*player.update();
		camera.SetTarget({ 0.0f,5.0f,0.0f });

		player.render(camera);

		FLOAT2 center = ToClient(GetWindowSize() / 2.0f);
		SetCursorPos(center.x, center.y);

		SpriteRender(1, (GetWindowSize() / 2.0f), { 0.2f, 0.2f }, { 0, 0 }, { 0, 0 }, { 300.0f, 400.0f });*/
		AliceLib::Present(0u, 0u);
	}

	return AliceLib::Exit();
}