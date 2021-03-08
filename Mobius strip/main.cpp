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
/********************************************************************/

INT WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, INT)
{
	
	AliceLib::Entry(L"AliceLib", 1280, 720, DefaultWindowMode::WM_WINDOW, 60);	

#ifdef TEST_OPENAL
	alc_open_device();
	std::unique_ptr<sound_buffer> sound_buffers;
	volume_effect d;
	sound_buffers = std::make_unique<sound_buffer>("009.ogg");
	sound_buffers->volume(0.5);
	sound_buffers->loop();
	sound_buffers->play(&d);
#endif

	while (Function::GameLoop())
	{
		StageEditor::Run();

		AliceLib::Present(0u, 0u);
	}

#ifdef TEST_OPENAL
	alc_close_device();
#endif
	return AliceLib::Exit();
}