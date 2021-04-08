#include "transition_y.h"
#include <fstream>

static Sprite cTex;

void Transition_y::normal()
{
	ArithmeticLib::NormalizeRadian(s);
	ArithmeticLib::NormalizeRadian(m);
	ArithmeticLib::NormalizeRadian(h);
}

void Transition_y::init()
{
	if (!cTex && Transition_y::file_pass)
		cTex.load(Transition_y::file_pass);

	// Todo :: 


}

bool Transition_y::fade_out()
{
	if (alpha >= 1.0f) { alpha = 1.0f; return true; }
	alpha += delta_time / timer_coeff;
	return false;
}

bool Transition_y::fade_in()
{
	if (alpha <= 0.0f) { alpha = 0.0f; return true; }
	alpha -= delta_time / timer_coeff;
	return false;
}

void Transition_y::Rotation_r()
{
	if (alpha <= 0.0f) return;
	s += delta_time * amout_s * speed_coeff;
	m += delta_time * amout_m * speed_coeff;
	h += delta_time * amout_h * speed_coeff;
	Transition_y::normal();
}

void Transition_y::Rotation_l()
{
	if (alpha <= 0.0f) return;
	s -= delta_time * amout_s * speed_coeff;
	m -= delta_time * amout_m * speed_coeff;
	h -= delta_time * amout_h * speed_coeff;
	Transition_y::normal();
}

void Transition_y::Render()
{

	if (alpha <= 0.0f) return;

	static const FLOAT2 ScreenSize = AliceLib::GetWindowSize();
	primitive::rect({}, ScreenSize, {}, 0.0f, {0.0f,0.0f,0.0f,alpha});

	//時計の針の中心
	static const FLOAT2 ClockCentral = ScreenSize / 2.0f;
	
	if (isFileExist)
	{
		//表示スケール
		static const FLOAT2 Scales = ArithmeticLib::ScalarToFloat2(1.0f);

		static const FLOAT2 texpos_d = {};
		static const FLOAT2 texsize_d = { 1050.0f,1080.0f };
		static const FLOAT2 texcenter_d = texsize_d / 2.0f;

		//土台の描画
		SpriteRender(cTex, ClockCentral, Scales, texpos_d, texsize_d, texcenter_d, 0.0f, { 1.0f,1.0f,1.0f,alpha });

		/*
			テクスチャの切り取り位置、幅、基準点の宣言
			基準点は時計の針の根本にすること
			土台　1050,1080
			針(左) 100,400
			針(真ん中) 125,300
			針(右) 75,250
		*/

		// h
		static const FLOAT2 texpos_h	= { 1275.0f,0.0f };
		static const FLOAT2 texsize_h	= { 75.0f,250.0f };
		static const FLOAT2 texcenter_h	= { 37.5f,220.0f };
		// m
		static const FLOAT2 texpos_m	= { 1150.0f,0.0f  };
		static const FLOAT2 texsize_m	= { 125.0f,300.0f };
		static const FLOAT2 texcenter_m	= { 62.5f,280.0f  };
		// s
		static const FLOAT2 texpos_s	= { 1050.0f,0.0f  };
		static const FLOAT2 texsize_s	= { 100.0f,400.0f };
		static const FLOAT2 texcenter_s	= { 50.0f,390.0f  };
		
		// h
		SpriteRender(cTex, ClockCentral, Scales, texpos_h, texsize_h, texcenter_h, h, { 1.0f,1.0f,1.0f,alpha });
		// m
		SpriteRender(cTex, ClockCentral, Scales, texpos_m, texsize_m, texcenter_m, m, { 1.0f,1.0f,1.0f,alpha });
		// s
		SpriteRender(cTex, ClockCentral, Scales, texpos_s, texsize_s, texcenter_s, s, { 1.0f,1.0f,1.0f,alpha });

		primitive::circle(ClockCentral, 4.0f, { 0.0f,0.0f,0.0f,alpha });
	}
	else
	{
		primitive::circle(ClockCentral, 512.0f, { 1.0f,0.5f,0.0f,alpha },128);

		// h
		static const FLOAT2 size_h = { 48.0f,256.0f };
		static const FLOAT2 center_h = { 24.0f,(256.0f / 5.0f) * 4.0f };
		// m
		static const FLOAT2 size_m = { 32.0f,512.0f };
		static const FLOAT2 center_m = { 16.0f,(512.0f / 5.0f) * 4.0f };
		// s
		static const FLOAT2 size_s = { 16.0f,512.0f };
		static const FLOAT2 center_s = { 8.0f,(512.0f / 5.0f) * 4.0f };
		// h
		primitive::rect(ClockCentral, size_h, center_h, h, { 0.0f,1.0f,0.0f,alpha });
		// m
		primitive::rect(ClockCentral, size_m, center_m, m, { 1.0f,0.0f,0.0f,alpha });
		// s
		primitive::rect(ClockCentral, size_s, center_s, s, { 1.0f,1.0f,1.0f,alpha });

		primitive::circle(ClockCentral, 4.0f, { 1.0f,0.5f,0.0f,alpha });
	}
	if (input::STATE(input::F1))
	{
		Debug->SetString("h::%.2f", toAngle(h));
		Debug->SetString("m::%.2f", toAngle(m));
		Debug->SetString("s::%.2f", toAngle(s));
	}
	Debug->display();
}

void TyDamoPlay()
{
	static Transition_y ty_s;
	ty_s.init();
	static bool swich_r = true;
	static bool swich_f = true;
	static bool isFade = false;
	
	ty_s.delta_time = DeltaTime();

	if (input::TRG(' '))swich_r = !swich_r;
	if (input::TRG(input::F2))swich_f = !swich_f;

	isFade = swich_f ? ty_s.fade_out(): ty_s.fade_in();
	if (ty_s.getAlpha() > 0.0f)
	{
		if (swich_r)
		{
			ty_s.Rotation_r();
			Debug->SetString("順転");
		}
		else
		{
			ty_s.Rotation_l();
			Debug->SetString("反転");
		}
	}
	else Debug->SetString("停止");
	if(!isFade) Debug->SetString("フェード中");

	ty_s.Render();
}