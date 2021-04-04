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

	std::string stage_names[] =
	{
		"Data/StageData/stage_data0.csv",
		//"Data/StageData/stage_data1.csv",
	};

	StageManager sm;

	sm.LoadStages(stage_names);

	AmbientLight					ambient;
	Camera							camera;
	ambient->option.x = 0.5f;

	UINT stage_num = 0;

	while (Function::GameLoop())
	{
		//StageEditor::Run();
		//TyDamoPlay();

		camera.Control();
		camera.Active();
		ambient->direction = camera.LightFloamCamera();
		ambient.Active();
		Geometric::Board(camera, {}, ScalarToFloat3(200.0f), {}, { 0,0,0,1.0f }, { 1.0f, 1.0f, 1.0f, 0.3f });
		sm.Render();
		
		if (input::TRG(' '))
		{
			stage_num = (stage_num == 0u) ? 1u : 0u;
			sm.Switching(stage_num);
		}
		
		Debug->SetString("%d,%d",sm.getStageNum(),stage_num);
		Debug->display();

		AliceLib::Present(0u, 0u);
	}

#ifdef TEST_OPENAL
	alc_close_device();
#endif
	return AliceLib::Exit();
}