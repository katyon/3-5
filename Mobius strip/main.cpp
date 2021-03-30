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
/********************************************************************/

INT WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, INT)
{
	
	AliceLib::Entry(L"AliceLib", 1280, 720, DefaultWindowMode::WM_WINDOW, 60);	

#ifdef TEST_OPENAL
	alc_open_device();
	AL_SoundBuffet testBGM = nullptr;
	testBGM = LoadALSound_s("009.ogg");
	testBGM->volume(0.5);
	testBGM->loop();
	testBGM->play();
#endif

	while (Function::GameLoop())
	{
		//StageEditor::Run();
		TyDamoPlay();
		AliceLib::Present(0u, 0u);
	}

#ifdef TEST_OPENAL
	alc_close_device();
#endif
	return AliceLib::Exit();
}