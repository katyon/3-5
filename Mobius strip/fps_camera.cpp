#include "fps_camera.h"

//VECTOR2D FPSCamera::getCursorMoveAmount()
//{
//	POINT now_point;
//	GetCursorPos(&now_point);
//	Cursor.current_pos = { (float)now_point.x,(float)now_point.y };
//
//	FLOAT2 center = ToWindow(GetScreenSize() / 2.0f);
//	SetCursorPos(center.x, center.y);
//	Cursor.preview_pos = { center.x, center.y };
//
//	return (center - Cursor.current_pos) * (1 + (correct_sensitivity - 5) * 0.18f);
//}