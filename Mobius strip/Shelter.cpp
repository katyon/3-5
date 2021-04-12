#include "Shelter.h"

bool ColLineOBB(const FLOAT3& start, const FLOAT3& end, const OBB& obb, FLOAT3& hitPoint)
{
	static AABB box;

	DirectX::XMFLOAT4X4 r_matrix = 
	{
		obb.direct.right.x,		obb.direct.right.y,		obb.direct.right.z,		0.0f,
		obb.direct.up.x,		obb.direct.up.y,		obb.direct.up.z,		0.0f,
		obb.direct.forward.x,	obb.direct.forward.y,	obb.direct.forward.z,	0.0f,
		0.0f,					0.0f,					0.0f,					1.0f
	};

	box.Max =  (obb.len / 2.0f);
	box.Min = -(obb.len / 2.0f);


	static DirectX::XMMATRIX wolrd, i_wolrd;

	wolrd = DirectX::XMLoadFloat4x4(&r_matrix) * ArithmeticLib::GetPositionMatrix(obb.pos);
	
	i_wolrd = DirectX::XMMatrixInverse(nullptr, wolrd);

	static FLOAT3 s, e;
	
	DirectX::XMStoreFloat3(&s, 
		DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&start), i_wolrd));
	
	DirectX::XMStoreFloat3(&e, 
		DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&end), i_wolrd));

	bool result = AliceLib::Collision::ColLineAABB(s, e, box, hitPoint);

	DirectX::XMStoreFloat3(&hitPoint, 
		DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&hitPoint), wolrd));

	return result;
}


FLOAT3 screen_to_world(const Camera& eye,
	const FLOAT3& screen_pos)
{
	static D3D11_VIEWPORT viewport;
	GetViewPort(viewport, 1u);
	DirectX::XMVECTOR vector = DirectX::XMVector3Unproject
	(
		DirectX::XMVectorSet(screen_pos.x, screen_pos.y, screen_pos.z, 0),
		viewport.TopLeftX, viewport.TopLeftY, viewport.Width, viewport.Height, viewport.MinDepth, viewport.MaxDepth,
		eye.GetProjectionMatrix(),
		eye.GetViewMatrix(),
		DirectX::XMMatrixIdentity()
	);
	static FLOAT3 pos;
	DirectX::XMStoreFloat3(&pos, vector);
	return pos;
}

PostureVector getPostureVector(const VECTOR3D& forward,const VECTOR3D& up)
{
	PostureVector result;

	result.forward = forward.normalize();

	result.right = VECTOR3D::cross(up.normalize(), result.forward).normalize();

	result.up = VECTOR3D::cross(result.forward, result.right).normalize();

	return result;
}



void ColDemoPlay()
{
	static Camera eye;
	static AmbientLight light;

	struct Box
	{
		Box(FLOAT3& p) :pos(p), flg(false), postrue({0.0f,0.0f,0.0f}) {}
		FLOAT3	pos;
		bool	flg;
		Quaternion postrue;
		void render()
		{
			Geometric::Cube(pos, ScalarToFloat3(1.0f), postrue,
				flg ? COLOR(DCOLOR_WHITE) : COLOR(DCOLOR_RED));
		}
	};

	static Box objs[2] = { FLOAT3(5.0f,0.5f,0.0f),FLOAT3(-5.0f,0.5f,0.0f) };

	eye.Control();
	eye.Active();
	light->option.x = 0.5f;
	light->direction = eye.LightFloamCamera();
	light.Active();

	static FLOAT3 s, e = {5.0f,0.0f,0.0f};
	static FLOAT3 hitPos[2];
	
	static FLOAT2 mouse_pos;

	Debug->SetString("ƒNƒŠƒbƒN‚³‚ê‚½Box‚Í”’‚­‚È‚è‚Ü‚·");

	static bool isTrg = false;
	if (input::STATE(input::MOUSE_L))
	{
		mouse_pos = input::GetMousePos();
		s = ::screen_to_world(eye, { mouse_pos,0.0f });
		e = ::screen_to_world(eye, { mouse_pos,1.0f });
		if (!isTrg)
		{
			isTrg = true;
			objs[0].flg = ColLineOBB(s, e,
				{ objs[0].pos, ScalarToFloat3(1.0f), objs[0].postrue },
				hitPos[0]);
			objs[1].flg = ColLineOBB(s, e,
				{ objs[1].pos, ScalarToFloat3(1.0f), objs[1].postrue },
				hitPos[1]);
		}

		FLOAT2 drg = input::GetDragged();
		Debug->SetString("x::%f,y::%f", drg.x, drg.y);

		PostureVector vector;

		vector = getPostureVector(s.FindTheVector3D(e), VECTOR3D(0.0f, 1.0f, 0.0f));

		FLOAT3 move_pos;
		if (ColLineOBB(s, e, { {}, {20.0f,0.0f,20.0f}, {} },move_pos))
		{

			if (objs[0].flg)
			{
				objs[0].pos = move_pos;
				objs[0].pos.y = 0.5f;
				//if (fabsf(drg.x) > 64.0f)
				//{
				//	objs[0].pos += vector.right * ((drg.x) / 512.0f);
				//}
				//if (fabsf(drg.y) > 64.0f)
				//{
				//	objs[0].pos += vector.up * (-(drg.y) / 512.0f);
				//}
			}
			if (objs[1].flg)
			{
				objs[1].pos = move_pos;
				objs[1].pos.y = 0.5f;
				//if (fabsf(drg.x) > 64.0f)
				//{
				//	objs[1].pos += vector.right * ((drg.x) / 512.0f);
				//}
				//if (fabsf(drg.y) > 64.0f)
				//{
				//	objs[1].pos += vector.up * (-(drg.y) / 512.0f);
				//}
			}
		}
		primitive::circle(mouse_pos, 64.0f, {DCOLOR_YELLOW});
		primitive::line(mouse_pos, input::GetMousePos(), { DCOLOR_GREEN });

		auto area_check = [](FLOAT3& pos)
		{
			if (pos.x > 9.5f)
			{
				pos.x = 9.5f;
			}
			else if (pos.x < -9.5f)
			{
				pos.x = -9.5f;
			}
			if (pos.z > 9.5f)
			{
				pos.z = 9.5f;
			}
			else if (pos.z < -9.5f)
			{
				pos.z = -9.5f;
			}
			pos.y = 0.5f;
		};
		area_check(objs[0].pos);
		area_check(objs[1].pos);
	}
	else 
	{ 
		isTrg = false; 
		objs[0].flg = false;
		objs[1].flg = false;
	}

	Geometric::Begin();
	Geometric::Board({}, { 20.0f,0.0f,20.0f }, {});
	objs[0].render();
	objs[1].render();
	Geometric::End();

	Debug->display();

}

bool Shelter::isClick(const Camera& eye, int& num)
{
	bool result = false;
	num = -1;
	float dis = 0.0f;
	FLOAT3 hitPos[2] = {};
	static FLOAT3 s, e;
	s = ::screen_to_world(eye, { mouse_pos_o,0.0f });
	e = ::screen_to_world(eye, { mouse_pos_o,1.0f });
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (ColLineOBB(s, e, {blocks[i].pos,blocks[i].size,blocks[i].angles},hitPos[0]))
		{
			if (!result)
			{
				hitPos[1] = hitPos[0];
				dis = s.distanceFrom(hitPos[1]);
				num = i;
				result = true;
			}
			else
			{
				float s_h = s.distanceFrom(hitPos[0]);
				if (s_h < dis)
				{
					num = i;
					hitPos[1] = hitPos[0];
					dis = s.distanceFrom(hitPos[1]);
				}
			}
		}
	}
	return result;
}

void Shelter::update()
{
	switch (state)
	{
	case Shelter::SS_CHOICE:
		if (input::TRG(input::MOUSE_L))
		{
			state++;
			mouse_pos_o = input::GetMousePos();
		}
		break;
	case Shelter::SS_CALCULATION:
		if (input::STATE(input::MOUSE_L))
		{

		}
		else { state = Shelter::SS_CHOICE; }
		break;
	case Shelter::SS_MOVE:
		
		break;
	case Shelter::SS_REJUDGMENT:
		
		break;
	default:
		break;
	}



}
