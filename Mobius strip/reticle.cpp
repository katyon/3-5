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