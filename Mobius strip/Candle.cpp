#include "Candle.h"
#include "PipePuzzle.h"
#include "Item.h"
#include "StageManager.h"

Candle::Candle()
{
}

void Candle::Init()
{

}

void Candle::Update()
{
    StageObject* objects = StageManager::getIns()->getStageObjects();

    for (int i = 0; i < StageData::MaxObjects; i++)
    {
        switch (RenderFlg())
        {
        case -1: // PipePuzzle::ClearFlg == -1
            if (objects[i].ID == "candle_full.fbx")
            {
                objects[i].isShow = true;
            }
            if (objects[i].ID == "candle_half.fbx")
            {
                objects[i].isShow = false;
            }
            if (objects[i].ID == "candle_lost.fbx")
            {
                objects[i].isShow = false;
            }
            break;

        case 0:  // PipePuzzle::ClearFlg == 0
            if (objects[i].ID == "candle_full.fbx")
            {
                objects[i].isShow = false;
            }
            if (objects[i].ID == "candle_half.fbx")
            {
                objects[i].isShow = true;
            }
            if (objects[i].ID == "candle_lost.fbx")
            {
                objects[i].isShow = false;
            }
            break;

        case 1:  // PipePuzzle::ClearFlg == 1
            if (G_Item->count[0] == true) {  }

            if (objects[i].ID == "candle_full.fbx")
            {
                objects[i].isShow = false;
            }
            if (objects[i].ID == "candle_half.fbx")
            {
                objects[i].isShow = false;
            }
            if (objects[i].ID == "candle_lost.fbx")
            {
                objects[i].isShow = true;
            }
            break;
        }
    }
}

int Candle::RenderFlg()
{
    switch (PipePuzzle::getInstance()->GetClearFlg())
    {
    case -1:
        return -1;
        break;

    case 0:
        return 0;
        break;

    case 1:
        if (G_Item->count[0] == true)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    }
}