#include "PipePuzzle.h"
#include "Shelter.h"

void getMouseRay(const Camera& eye, FLOAT3& start, FLOAT3& end);

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

#define GOAL_POS_X 4
#define GOAL_POS_Y 4

int first_pipes[5][5] =
{
    9, 1, 5, 1, 2,
    5, 2, 6, 2, 6,
    2, 1, 3, 6, 4,
    4, 3, 4, 6, 1,
    1, 5, 2, 3, 10
};

int Pipes[5][5] =
{
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0
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

PipePuzzle::PipePuzzle()
{
    curve_pipe.load("Data\\Objects\\CurvePipe.fbx");
    straight_pipe.load("Data\\Objects\\StrightPipe.fbx");
    start_pipe.load("Data\\Objects\\StartPipe.fbx");
    goal_pipe.load("Data\\Objects\\GoalPipe.fbx");

    Audio::load(2, L"Data/BGM/pipe.wav");
}

void PipePuzzle::Init()
{
    //scale = ScalarToFloat3(0.165f);
    scale = ScalarToFloat3(0.3f);
    OBBscale = ScalarToFloat3(4.8f);

    clearFlg = false;

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            Pipes[y][x] = first_pipes[y][x];
        }
    }
}

void PipePuzzle::Update()
{
    timer++;

    if (input::TRG(0))
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


    if (input::TRG(input::MOUSE_L))
    {
        switch (Pipes[Cursor_pos_y][Cursor_pos_x])
        {
        case CURVE0:
            Pipes[Cursor_pos_y][Cursor_pos_x] = CURVE1;
            Audio::play(2);
            break;

        case CURVE1:
            Pipes[Cursor_pos_y][Cursor_pos_x] = CURVE2;
            Audio::play(2);
            break;

        case CURVE2:
            Pipes[Cursor_pos_y][Cursor_pos_x] = CURVE3;
            Audio::play(2);
            break;

        case CURVE3:
            Pipes[Cursor_pos_y][Cursor_pos_x] = CURVE0;
            Audio::play(2);
            break;
            
        case STRAIGHT0:
            Pipes[Cursor_pos_y][Cursor_pos_x] = STRAIGHT1;
            Audio::play(2);
            break;

        case STRAIGHT1:
            Pipes[Cursor_pos_y][Cursor_pos_x] = STRAIGHT0;
            Audio::play(2);
            break;
        }

        if (Cursor_pos_x == Water_pos_x && Cursor_pos_y == Water_pos_y)
        {
            Reset();
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
                if (Pipes[Water_pos_y + 1][Water_pos_x] == CURVE0 || Pipes[Water_pos_y + 1][Water_pos_x] == CURVE3 || Pipes[Water_pos_y + 1][Water_pos_x] == STRAIGHT1 || Pipes[Water_pos_y + 1][Water_pos_x] == GOAL)
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
                if (Pipes[Water_pos_y + 1][Water_pos_x] == CURVE0 || Pipes[Water_pos_y + 1][Water_pos_x] == CURVE3 || Pipes[Water_pos_y + 1][Water_pos_x] == STRAIGHT1 || Pipes[Water_pos_y + 1][Water_pos_x] == GOAL)
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
            clearFlg = true;
            Reset();
            break;

        default:
            Reset();
            break;
        }
    }

}

void PipePuzzle::Render(const Camera& camera)
{
    getMouseRay(camera, rayStart, rayEnd);

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            pos = { x * 5.5f + 22, 0 - y * 5.5f + 27, 50 };
            posture.reset();

            COLOR color; 
            if (Cursor_pos_x == x && Cursor_pos_y == y)
            {
                color = { 1.0f, 0.2f, 0.3f, 1.0f };
            }
            else
            {
                if (wateres[y][x] > 0)
                {
                    color = { 0.3f, 0.3f, 0.7f, 1.0f };
                }
                else
                {
                    color = { 1.0f, 1.0f, 1.0f, 1.0f };
                }
            }
            if (Cursor_pos_y == y && Cursor_pos_x == x)
            {
                if (!ColLineOBB(rayStart, rayEnd, CreateOBB(pos, OBBscale, posture), hitPos))
                {
                    Cursor_pos_x = 0;
                    Cursor_pos_y = 0;
                }

            }

            if (Pipes[y][x] == CURVE0)  
            {
                posture.RotationPitch(PI / 2);
                if (ColLineOBB(rayStart, rayEnd, CreateOBB(pos, OBBscale, posture), hitPos))
                {
                    Cursor_pos_x = x;
                    Cursor_pos_y = y;
                }
                SkinnedMeshRender(curve_pipe, camera, pos, scale, posture, camera.LightFloamCamera(), color);
            }
            if (Pipes[y][x] == CURVE1)
            {
                posture.RotationPitch(PI / 2);
                posture.RotationYaw(-PI / 2);
                if (ColLineOBB(rayStart, rayEnd, CreateOBB(pos, OBBscale, posture), hitPos))
                {
                    Cursor_pos_x = x;
                    Cursor_pos_y = y;
                }
                SkinnedMeshRender(curve_pipe, camera, pos, scale, posture, camera.LightFloamCamera(), color);
            }
            if (Pipes[y][x] == CURVE2)
            {
                posture.RotationPitch(PI / 2);
                posture.RotationYaw(PI);
                if (ColLineOBB(rayStart, rayEnd, CreateOBB(pos, OBBscale, posture), hitPos))
                {
                    Cursor_pos_x = x;
                    Cursor_pos_y = y;
                }
                SkinnedMeshRender(curve_pipe, camera, pos, scale, posture, camera.LightFloamCamera(), color);

            }
            if (Pipes[y][x] == CURVE3)
            {
                posture.RotationPitch(PI / 2);
                posture.RotationYaw(PI / 2);
                if (ColLineOBB(rayStart, rayEnd, CreateOBB(pos, OBBscale, posture), hitPos))
                {
                    Cursor_pos_x = x;
                    Cursor_pos_y = y;
                }
                SkinnedMeshRender(curve_pipe, camera, pos, scale, posture, camera.LightFloamCamera(), color);
            }
            if (Pipes[y][x] == STRAIGHT0)
            {
                posture.RotationPitch(PI / 2);
                posture.RotationYaw(PI / 2);
                if (ColLineOBB(rayStart, rayEnd, CreateOBB(pos, OBBscale, posture), hitPos))
                {
                    Cursor_pos_x = x;
                    Cursor_pos_y = y;
                }
                SkinnedMeshRender(straight_pipe, camera, pos, scale, posture, camera.LightFloamCamera(), color);
            }
            if (Pipes[y][x] == STRAIGHT1)
            {
                posture.RotationPitch(PI / 2);
                if (ColLineOBB(rayStart, rayEnd, CreateOBB(pos, OBBscale, posture), hitPos))
                {
                    Cursor_pos_x = x;
                    Cursor_pos_y = y;
                }
                SkinnedMeshRender(straight_pipe, camera, pos, scale, posture, camera.LightFloamCamera(), color);
            }
            if (Pipes[y][x] == START)
            {
                posture.RotationPitch(-PI / 2);

                SkinnedMeshRender(start_pipe, camera, pos, scale, posture, camera.LightFloamCamera(), { 1.0f, 1.0f, 1.0f, 1.0f });
            }
            if (Pipes[y][x] == GOAL)
            {
                posture.RotationPitch(-PI / 2);

                SkinnedMeshRender(goal_pipe, camera, pos, scale, posture, camera.LightFloamCamera(), { 1.0f, 1.0f, 1.0f, 1.0f });
            }
            
        }
    }

    if (clearFlg == true)
    {
        font::OutPut(L"Clear!", 900.0f, 0.0f);
    }
}

void PipePuzzle::Release()
{

}