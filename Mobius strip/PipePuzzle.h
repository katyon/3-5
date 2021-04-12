#pragma once
#include "./AliceLib/AliceLib.h"

class PipePuzzle
{
private:

    //int Pipes[5][5];

    Sprite curve_pipe;
    Sprite straight_pipe;
    Sprite start_pipe;
    Sprite goal_pipe;
    Sprite cursor;
    Sprite water;
    Sprite water_block;

    int timer = 0;

    void Reset();

public:

    int Cursor_pos_x = 0;
    int Cursor_pos_y = 0;

    int Water_pos_x = 0;
    int Water_pos_y = 0;

    // pre => Previous : ’¼‘O
    int pre_Water_pos_x = 0;
    int pre_Water_pos_y = 0;

    void run()
    {
        //Init();
        Update();
        Render();
        //Release();
    }

    void Init();
    void Update();
    void Render();
    void Release();

};