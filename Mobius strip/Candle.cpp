#include "Candle.h"
#include "PipePuzzle.h"
#include "Item.h"

Candle::Candle()
{
    Candle_full.load("Data\\Candle\\candle_full.fbx");
    Candle_half.load("Data\\Candle\\candle_half.fbx");
    Candle_lost.load("Data\\Candle\\candle_lost.fbx");
    posture.reset();
}

void Candle::Init()
{
    position = { -15, 12, 50 };
    scale = { 0.7, 0.7, 0.7 };
    posture.RotationYaw(-PI / 2);
}

void Candle::Update()
{

}

void Candle::Render(const Camera& camera)
{
    FLOAT4 light_dir = { 0, 0, 0, 1 };

    switch (PipePuzzle::getInstance()->GetClearFlg())
    {
    case 0:
        SkinnedMeshRender(Candle_half, camera, position, scale, posture, light_dir);
        break;

    case 1:
        if (G_Item->count[0] == true)
        {
            SkinnedMeshRender(Candle_lost, camera, position, scale, posture, light_dir);
            break;
        }
        SkinnedMeshRender(Candle_half, camera, position, scale, posture, light_dir);
        break;

    case -1:
        SkinnedMeshRender(Candle_full, camera, position, scale, posture, light_dir);
        break;
    }
}

void Candle::Release()
{

}