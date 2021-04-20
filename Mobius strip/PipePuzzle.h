#pragma once
#include "./AliceLib/AliceLib.h"

class PipePuzzle
{
private:

    SkinnedMesh curve_pipe;
    SkinnedMesh straight_pipe;
    SkinnedMesh start_pipe;
    SkinnedMesh goal_pipe;

    //FLOAT3 pos;
    FLOAT3 scale;
    XMMATRIX world_matrix;

    FLOAT3 OBBscale;

    FLOAT3 rayStart;
    FLOAT3 rayEnd;

    FLOAT3 hitPos;
    Quaternion posture;

    int  timer = 0;
    bool clearFlg = false;

    void Reset();

public:

    int Cursor_pos_x = 0;
    int Cursor_pos_y = 0;

    int Water_pos_x = 0;
    int Water_pos_y = 0;

    // pre => Previous : ’¼‘O
    int pre_Water_pos_x = 0;
    int pre_Water_pos_y = 0;

    PipePuzzle();

    void Init();
    void Update();
    void Render(const Camera& camera);
    void Release();

};