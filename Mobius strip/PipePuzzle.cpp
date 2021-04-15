#include "PipePuzzle.h"

enum MapChipName
{
    NONE,
    CURVE0,
    CURVE1,
    CURVE2,
    CURVE3,
    STRAIGHT0,
    STRAIGHT1,
    START = 9,
    GOAL = 10
};

int Pipes[5][5] =
{
    9, 1, 6, 1, 2,
    6, 2, 6, 2, 6,
    2, 1, 3, 6, 4,
    4, 3, 4, 5, 1,
    1, 5, 2, 3, 10
};

int wateres[5][5] =
{
    1, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0
};

void PipePuzzle::Reset()
{
    Water_pos_x = 0;
    Water_pos_y = 0;
   for (int y = 0; y < 5; y++)
   {
       for (int x = 0; x < 5; x++)
       {
            wateres[y][x] -= 1;
       }
   }
}

void PipePuzzle::Init()
{
    SpriteLoad(curve_pipe, L"CurvePipe.png");
    SpriteLoad(straight_pipe, L"StraightPipe.png");
    SpriteLoad(start_pipe, L"StartPipe.png");
    SpriteLoad(goal_pipe, L"GoalPipe.png");
    SpriteLoad(cursor, L"cursor.png");
    SpriteLoad(water, L"cursor.png");
    SpriteLoad(water_block, L"Water.png");
}

void PipePuzzle::Update()
{
    timer++;

    if (input::TRG(VK_SPACE))
    {
        Pipes[Cursor_pos_y][Cursor_pos_x] = 5;     
    }
    if (input::TRG(VK_BACK))
    {
        Pipes[Cursor_pos_y][Cursor_pos_x] = 0;
    }

    if (input::TRG(VK_UP))      { Cursor_pos_y -= 1; }
    if (input::TRG(VK_DOWN))    { Cursor_pos_y += 1; }
    if (input::TRG(VK_LEFT))    { Cursor_pos_x -= 1; }
    if (input::TRG(VK_RIGHT))   { Cursor_pos_x += 1; }

    if (Cursor_pos_x > 4) { Cursor_pos_x = 4; }
    if (Cursor_pos_x < 0) { Cursor_pos_x = 0; }
    if (Cursor_pos_y > 4) { Cursor_pos_y = 4; }
    if (Cursor_pos_y < 0) { Cursor_pos_y = 0; }

    if (Water_pos_x > 4) { Water_pos_x = 4; }
    if (Water_pos_x < 0) { Water_pos_x = 0; }
    if (Water_pos_y > 4) { Water_pos_y = 4; }
    if (Water_pos_y < 0) { Water_pos_y = 0; }

    if (input::TRG(KEY::VK_R))
    {
        switch (Pipes[Cursor_pos_y][Cursor_pos_x])
        {
        case CURVE0:
            Pipes[Cursor_pos_y][Cursor_pos_x] = CURVE1;
            break;

        case CURVE1:
            Pipes[Cursor_pos_y][Cursor_pos_x] = CURVE2;
            break;

        case CURVE2:
            Pipes[Cursor_pos_y][Cursor_pos_x] = CURVE3;
            break;

        case CURVE3:
            Pipes[Cursor_pos_y][Cursor_pos_x] = CURVE0;
            break;
            
        case STRAIGHT0:
            Pipes[Cursor_pos_y][Cursor_pos_x] = STRAIGHT1;
            break;

        case STRAIGHT1:
            Pipes[Cursor_pos_y][Cursor_pos_x] = STRAIGHT0;
            break;
        }
    }

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            if (wateres[y][x] < 0)
            {
                wateres[y][x] = 0;
            }   

            if (wateres[y][x] > 2)
            {
                wateres[y][x] = 2;
            }
        }
    }

    
    if (timer % 2 == 0 )
    {
        switch (Pipes[Water_pos_y][Water_pos_x])
        {
        case CURVE0:
            if (pre_Water_pos_y < Water_pos_y)
            {
                if (Pipes[Water_pos_y][Water_pos_x + 1] == CURVE2 || Pipes[Water_pos_y][Water_pos_x + 1] == CURVE3 || Pipes[Water_pos_y][Water_pos_x + 1] == STRAIGHT0)
                {
                    pre_Water_pos_x = Water_pos_x;
                    pre_Water_pos_y = Water_pos_y;
                    Water_pos_x += 1;
                    wateres[Water_pos_y][Water_pos_x] += 2;
                }
                else
                {
                    Reset();                   
                }
            }
            else if (pre_Water_pos_x > Water_pos_x)
            {
                if (Pipes[Water_pos_y - 1][Water_pos_x] == CURVE1 || Pipes[Water_pos_y - 1][Water_pos_x] == CURVE2 || Pipes[Water_pos_y - 1][Water_pos_x] == STRAIGHT1)
                {
                    pre_Water_pos_x = Water_pos_x;
                    pre_Water_pos_y = Water_pos_y;
                    Water_pos_y -= 1;
                    wateres[Water_pos_y][Water_pos_x] += 2;
                }
                else
                {
                    Reset();
                }
            }
            break;

        case CURVE1:
            if (pre_Water_pos_y > Water_pos_y)
            {
                if (Pipes[Water_pos_y][Water_pos_x + 1] == CURVE2 || Pipes[Water_pos_y][Water_pos_x + 1] == CURVE3 || Pipes[Water_pos_y][Water_pos_x + 1] == STRAIGHT0)
                {
                    pre_Water_pos_x = Water_pos_x;
                    pre_Water_pos_y = Water_pos_y;
                    Water_pos_x += 1;
                    wateres[Water_pos_y][Water_pos_x] += 2;
                }
                else
                {
                    Reset();
                }
            }
            else if (pre_Water_pos_x > Water_pos_x)
            {
                if (Pipes[Water_pos_y + 1][Water_pos_x] == CURVE0 || Pipes[Water_pos_y + 1][Water_pos_x] == CURVE3 || Pipes[Water_pos_y + 1][Water_pos_x] == STRAIGHT1)
                {
                    pre_Water_pos_x = Water_pos_x;
                    pre_Water_pos_y = Water_pos_y;
                    Water_pos_y += 1;
                    wateres[Water_pos_y][Water_pos_x] += 2;
                }
                else
                {
                    Reset();
                }
            }
            break;

        case CURVE2:
            if (pre_Water_pos_y > Water_pos_y)
            {
                if (Pipes[Water_pos_y][Water_pos_x - 1] == CURVE0 || Pipes[Water_pos_y][Water_pos_x - 1] == CURVE1 || Pipes[Water_pos_y][Water_pos_x - 1] == STRAIGHT0)
                {
                    pre_Water_pos_x = Water_pos_x;
                    pre_Water_pos_y = Water_pos_y;
                    Water_pos_x -= 1;
                    wateres[Water_pos_y][Water_pos_x] += 2;
                }
                else
                {
                    Reset();
                }
            }
            else if (pre_Water_pos_x < Water_pos_x)
            {
                if (Pipes[Water_pos_y + 1][Water_pos_x] == CURVE0 || Pipes[Water_pos_y + 1][Water_pos_x] == CURVE3 || Pipes[Water_pos_y + 1][Water_pos_x] == STRAIGHT1)
                {
                    pre_Water_pos_x = Water_pos_x;
                    pre_Water_pos_y = Water_pos_y;
                    Water_pos_y += 1;
                    wateres[Water_pos_y][Water_pos_x] += 2;
                }
                else
                {
                    Reset();
                }
            }
            break;

        case CURVE3:
            if (pre_Water_pos_y < Water_pos_y)
            {
                if (Pipes[Water_pos_y][Water_pos_x - 1] == CURVE0 || Pipes[Water_pos_y][Water_pos_x - 1] == CURVE1 || Pipes[Water_pos_y][Water_pos_x - 1] == STRAIGHT0)
                {
                    pre_Water_pos_x = Water_pos_x;
                    pre_Water_pos_y = Water_pos_y;
                    Water_pos_x -= 1;
                    wateres[Water_pos_y][Water_pos_x] += 2;
                }
                else
                {
                    Reset();
                }
            }
            else if (pre_Water_pos_x < Water_pos_x)
            {
                if (Pipes[Water_pos_y - 1][Water_pos_x] == CURVE1 || Pipes[Water_pos_y - 1][Water_pos_x] == CURVE2 || Pipes[Water_pos_y - 1][Water_pos_x] == STRAIGHT1)
                {
                    pre_Water_pos_x = Water_pos_x;
                    pre_Water_pos_y = Water_pos_y;
                    Water_pos_y -= 1;
                    wateres[Water_pos_y][Water_pos_x] += 2;
                }
                else
                {
                    Reset();
                }
            }
            break;

        case STRAIGHT0:
            if (pre_Water_pos_x < Water_pos_x)
            {
                if (Pipes[Water_pos_y][Water_pos_x + 1] == CURVE2 || Pipes[Water_pos_y][Water_pos_x + 1] == CURVE3 || Pipes[Water_pos_y][Water_pos_x + 1] == STRAIGHT0)
                {
                    pre_Water_pos_x = Water_pos_x;
                    pre_Water_pos_y = Water_pos_y;
                    Water_pos_x += 1;
                    wateres[Water_pos_y][Water_pos_x] += 2;
                }
                else
                {
                    Reset();
                }
            }
            else if (pre_Water_pos_x > Water_pos_x)
            {
                if (Pipes[Water_pos_y][Water_pos_x - 1] == CURVE0 || Pipes[Water_pos_y][Water_pos_x - 1] == CURVE1 || Pipes[Water_pos_y][Water_pos_x - 1] == STRAIGHT0)
                {
                    pre_Water_pos_x = Water_pos_x;
                    pre_Water_pos_y = Water_pos_y;
                    Water_pos_x -= 1;
                    wateres[Water_pos_y][Water_pos_x] += 2;
                }
                else
                {
                    Reset();
                }
            }
            break;

        case STRAIGHT1:
            if (pre_Water_pos_y < Water_pos_y)
            {
                if (Pipes[Water_pos_y + 1][Water_pos_x] == CURVE0 || Pipes[Water_pos_y + 1][Water_pos_x] == CURVE3 || Pipes[Water_pos_y + 1][Water_pos_x] == STRAIGHT1)
                {
                    pre_Water_pos_x = Water_pos_x;
                    pre_Water_pos_y = Water_pos_y;
                    Water_pos_y += 1;
                    wateres[Water_pos_y][Water_pos_x] += 2;
                }
                else
                {
                    Reset();
                }
            }
            else if (pre_Water_pos_y > Water_pos_y)
            {
                if (Pipes[Water_pos_y - 1][Water_pos_x] == CURVE1 || Pipes[Water_pos_y - 1][Water_pos_x] == CURVE2 || Pipes[Water_pos_y - 1][Water_pos_x] == STRAIGHT1)
                {
                    pre_Water_pos_x = Water_pos_x;
                    pre_Water_pos_y = Water_pos_y;
                    Water_pos_y -= 1;
                    wateres[Water_pos_y][Water_pos_x] += 2;
                }
                else
                {
                    Reset();
                }
            }
            break;

        case START:
            if (Pipes[Water_pos_y + 1][Water_pos_x] == CURVE0 || Pipes[Water_pos_y + 1][Water_pos_x] == CURVE3 || Pipes[Water_pos_y + 1][Water_pos_x] == STRAIGHT1)
            {
                pre_Water_pos_x = Water_pos_x;
                pre_Water_pos_y = Water_pos_y;
                Water_pos_y += 1;
                wateres[Water_pos_y][Water_pos_x] += 2;
            }
            else
            {
                Reset();
            }
            break;

        case GOAL:
            break;

        default:
            break;
        }
    }

}

void PipePuzzle::Render()
{
    FLOAT2 SCALE = { 0.5, 0.5 };
    //FLOAT2 POSITION = { 0, 0 };


    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            if (Pipes[y][x] == CURVE0)
            {
                SpriteRender(curve_pipe, { x * 150.0f + 150.0f / 2, y * 150.0f + 150.0f / 2 }, SCALE, {}, {}, { 150.0f, 150.0f }, 0);
            }
            if (Pipes[y][x] == CURVE1)
            {
                SpriteRender(curve_pipe, { x * 150.0f + 150.0f / 2, y * 150.0f + 150.0f / 2 }, SCALE, {}, {}, { 150.0f, 150.0f }, PI/2);
            }
            if (Pipes[y][x] == CURVE2)
            {
                SpriteRender(curve_pipe, { x * 150.0f + 150.0f / 2, y * 150.0f + 150.0f / 2 }, SCALE, {}, {}, { 150.0f, 150.0f }, PI);
            }
            if (Pipes[y][x] == CURVE3)
            {
                SpriteRender(curve_pipe, { x * 150.0f + 150.0f / 2, y * 150.0f + 150.0f / 2 }, SCALE, {}, {}, { 150.0f, 150.0f }, -PI/2);
            }
            if (Pipes[y][x] == STRAIGHT0)
            {
                SpriteRender(straight_pipe, { x * 150.0f + 150.0f / 2, y * 150.0f + 150.0f / 2 }, SCALE, {}, {}, { 150.0f, 150.0f }, 0);
            }
            if (Pipes[y][x] == STRAIGHT1)
            {
                SpriteRender(straight_pipe, { x * 150.0f + 150.0f / 2, y * 150.0f + 150.0f / 2 }, SCALE, {}, {}, { 150.0f, 150.0f }, PI/2);
            }
            if (Pipes[y][x] == START)
            {
                SpriteRender(start_pipe, { x * 150.0f + 150.0f / 2, y * 150.0f + 150.0f / 2 }, SCALE, {}, {}, { 150.0f, 150.0f }, 0);
            }
            if (Pipes[y][x] == GOAL)
            {
                SpriteRender(goal_pipe, { x * 150.0f + 150.0f / 2, y * 150.0f + 150.0f / 2 }, SCALE, {}, {}, { 150.0f, 150.0f }, PI);
            }

            //if (wateres[y][x] > 0)
            if (wateres[y][x] == 1 || wateres[y][x] == 2)
            {
                SpriteRender(water_block, { x * 150.0f + 150.0f / 2, y * 150.0f + 150.0f / 2 }, SCALE, {}, {}, { 150.0f, 150.0f }, 0, { 1.0f, 1.0f, 1.0f, 0.3f });
            }
        }
    }

    SpriteRender(cursor, { Cursor_pos_x * 150.0f, Cursor_pos_y * 150.0f }, { 5.0f, 5.0f });
    //SpriteRender(water, { Water_pos_x * 150.0f, Water_pos_y * 150.0f }, { 5.0f, 5.0f }, {}, {}, {}, {}, { 0.3, 0.7, 0.7, 1.0 } );

}

void PipePuzzle::Release()
{
    SpritesUninitialize();
}