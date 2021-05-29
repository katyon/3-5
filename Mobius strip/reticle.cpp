#include "reticle.h"

Reticle::Reticle()
{
	current_type = RETICLE_TYPE::CROSS_HAIR;
	SpriteLoad(spr, L"Data/Sprite/reticle.png");
}

void Reticle::Render()
{
	switch (current_type)
	{
	case RETICLE_TYPE::CROSS_HAIR:
		SpriteRender(spr, (GetWindowSize() / 2.0f), { 0.3f, 0.3f }, { 0, 0 }, { 256.0f, 256.0f }, { 128.0f, 128.0f });
		break;
	case RETICLE_TYPE::LOUPE:
		SpriteRender(spr, (GetWindowSize() / 2.0f), { 0.3f, 0.3f }, { 256, 0 }, { 256.0f, 256.0f }, { 128.0f, 128.0f });
		break;
	case RETICLE_TYPE::EXIT:
		SpriteRender(spr, (GetWindowSize() / 2.0f), { 0.3f, 0.3f }, { 256 * 2, 0 }, { 256.0f, 256.0f }, { 128.0f, 128.0f });
		break;
	}
}

void Reticle::RenderCursor()
{
	POINT now_point;
	GetCursorPos(&now_point);
	FLOAT2 point = { (float)now_point.x, (float)now_point.y };

	(current_type == RETICLE_TYPE::LOUPE) ?
		SpriteRender(spr, point, { 0.3f, 0.3f }, { 256, 0 }, { 256.0f, 256.0f }, { 128.0f, 128.0f }) :
		SpriteRender(spr, point, { 0.3f, 0.3f }, { 256*3, 0 }, { 256.0f, 256.0f }, { 12, 15 });
}