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
	AliceLib::GetViewPort(viewport, 1u);
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

/*マウスからのレイを取得*/
void getMouseRay(const Camera& eye,FLOAT3& start,FLOAT3& end)
{
	FLOAT2 mouse_pos = input::GetMousePos();
	start	= ::screen_to_world(eye, { mouse_pos,0.0f });
	end		= ::screen_to_world(eye, { mouse_pos,1.0f });
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

	Debug->SetString("クリックされたBoxは白くなります");

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

bool Shelter::isClick()
{
	bool result = false;
	operation = -1;
	float dis = 0.0f;
	FLOAT3 hitPos[2] = {};
	static FLOAT3 s, e;
	s = ::screen_to_world(*eye, { mouse_pos_o,0.0f });
	e = ::screen_to_world(*eye, { mouse_pos_o,1.0f });
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (ColLineOBB(s, e, {blocks[i].pos,blocks[i].size,blocks[i].angles},hitPos[0]))
		{
			if (!result)
			{
				hitPos[1] = hitPos[0];
				dis = s.distanceFrom(hitPos[1]);
				operation = i;
				result = true;
			}
			else
			{
				float s_h = s.distanceFrom(hitPos[0]);
				if (s_h < dis)
				{
					operation = i;
					hitPos[1] = hitPos[0];
					dis = s.distanceFrom(hitPos[1]);
				}
			}
		}
	}
	return result;
}

void Shelter::getVector()
{
	static VECTOR2 f = { 0.0f,-1.0f };
	VECTOR2 v = mouse_pos_o.FindTheVector2D(mouse_pos).normalize();
	float rad = f.dot(v);

	if (fabsf(rad) >= static_cast<float>(1.0f / 3.0f))
	{
		vector_move = rad > 0 ? MV_F : MV_B;
	}
	else
	{
		vector_move = f.x * v.y - f.y * v.x > 0 ? MV_R : MV_L;
	}
}

bool Shelter::isMove(BLOCK& block)
{
	auto equal = [](DirectX::XMINT2 a, DirectX::XMINT2 b)
	{
		return (a.x == b.x) && (a.y == b.y);
	};
	switch (vector_move)
	{
	case Shelter::MV_F:
		if (block.trout.y > 0
			&& map[block.trout.y - 1][block.trout.x] != 1)
		{
			return true;
		}
		else if (block.isPair() 
			&& equal({ block.trout.x ,block.trout.y - 1 },blocks[block.pair].trout))
		{
			return true;
		}
		else return false;
		break;
	case Shelter::MV_B:
		if (block.trout.y < 5
			&& map[block.trout.y + 1][block.trout.x] != 1)
		{
			return true;
		}
		else if (block.isPair()
			&& equal({ block.trout.x ,block.trout.y + 1 }, blocks[block.pair].trout))
		{
			return true;
		}
		else return false;
		break;
	case Shelter::MV_L:
		if (block.trout.x > 0
			&& map[block.trout.y][block.trout.x - 1] != 1)
		{
			return true;
		}
		else if (block.isPair()
			&& equal({ block.trout.x - 1 ,block.trout.y }, blocks[block.pair].trout))
		{
			return true;
		}
		else return false;
		break;
	case Shelter::MV_R:
		if (block.trout.x < 4
			&& map[block.trout.y][block.trout.x + 1] != 1)
		{
			return true;
		}
		else if (block.isPair()
			&& equal({ block.trout.x + 1 ,block.trout.y }, blocks[block.pair].trout))
		{
			return true;
		}
		else return false;
		break;
	default:
		break;
	}
	return false;
}

bool Shelter::Move(BLOCK& block,float delta_time)
{
	//pos.x = static_cast<float>((trout.x - 2) *  1.0f);
	//pos.z = static_cast<float>((trout.y - 2) * -1.0f);
	
	switch (vector_move)
	{
	case Shelter::MV_F:
		block.pos.z += SPEED * delta_time;
		if (static_cast<float>((block.trout.y - 3) * -1.0f)
			<= block.pos.z)
		{
			block.pos.z = static_cast<float>((block.trout.y - 3) * -1.0f);
			block.trout.y -= 1;
			return true;
		}
		break;
	case Shelter::MV_B:
		block.pos.z -= SPEED * delta_time;
		if (static_cast<float>((block.trout.y - 1) * -1.0f)
			>= block.pos.z)
		{
			block.pos.z = static_cast<float>((block.trout.y - 1) * -1.0f);
			block.trout.y += 1;
			return true;
		}
		break;
	case Shelter::MV_L:
		block.pos.x -= SPEED * delta_time;
		if (static_cast<float>((block.trout.x - 3) * 1.0f)
			>= block.pos.x)
		{
			block.pos.x = static_cast<float>((block.trout.x - 3) * 1.0f);
			block.trout.x -= 1;
			return true;
		}
		break;
	case Shelter::MV_R:
		block.pos.x += SPEED * delta_time;
		if (static_cast<float>((block.trout.x - 1) * 1.0f)
			<= block.pos.x)
		{
			block.pos.x = static_cast<float>((block.trout.x - 1) * 1.0f);
			block.trout.x += 1;
			return true;
		}
		break;
	}
	return false;
}

void Shelter::Maping()
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			map[y][x] = 0;
		}
	}
	for (auto block : blocks)
	{
		map[block.trout.y][block.trout.x] = 1;
		if (block.trout.y == 5 && block.trout.x == 2&&block.type==1)
		{
			isClear = true;
		}
	}
}

void Shelter::update(float delta_time)
{
	Shelter::Maping();
	switch (state)
	{
	case Shelter::SS_CHOICE:
		if (input::TRG(input::MOUSE_L))
		{
			mouse_pos_o = input::GetMousePos();
			if (isClick())
			{
				state++;
			}
		}
		break;
	case Shelter::SS_CALCULATION:
		if (input::STATE(input::MOUSE_L))
		{
			mouse_pos = input::GetMousePos();
			if (mouse_pos.distanceFrom(mouse_pos_o) > 128.0f)
			{
				getVector();
				if (isMove(blocks[operation]))
				{
					if (blocks[operation].isPair())
					{
						if (isMove(blocks[blocks[operation].pair]))
						{
							state++;
						}
						else state = Shelter::SS_CHOICE;
					}
					else state++;
				}
				else
				{
					state = Shelter::SS_CHOICE;
				}
			}
		}
		else { state = Shelter::SS_CHOICE; }
		break;
	case Shelter::SS_MOVE:
	{
		bool flg1 = Move(blocks[operation], delta_time);
		bool flg2 = blocks[operation].isPair()?
			Move(blocks[blocks[operation].pair], delta_time) : true;
		if (flg1 && flg2)
		{
			state++;
		}
		break;
	}
	case Shelter::SS_REJUDGMENT:
		if (input::STATE(input::MOUSE_L))
		{
			mouse_pos_o = input::GetMousePos();
			state = SS_CALCULATION;
		}
		else
		{
			state = SS_CHOICE;
		}
		break;
	default:
		break;
	}



}

void Shelter::render()
{
	eye->Active();
	
	Geometric::Begin();
	Geometric::Board({}, { 5.0f,0.0f,5.0f }, {});
	for (auto block : blocks)
	{
		switch (block.type)
		{
		case 1:
			Geometric::Cube(block.pos, block.size, block.angles, { DCOLOR_BLUE });
			break;
		default:
			Geometric::Cube(block.pos, block.size, block.angles, { DCOLOR_RED });
			break;
		}
	}
	Geometric::Board({ 0,0,static_cast<float>(3 - 6 * 1.0f) }, { 1.0f,0.0f,1.0f }, {}, {DCOLOR_GREEN});
	Geometric::End();
}

void Shelter::Ui()
{
	switch (state)
	{
	case Shelter::SS_CHOICE:
		//何も描画しない
		break;
	case Shelter::SS_MOVE:
	{
		switch (vector_move)
		{
		case Shelter::MV_F:
			SpriteRender(cursor, mouse_pos_o,
				ScalarToFloat2(.3f),
				{},
				{ 384.0f,128.0f },
				{ 192.0f,256.0f }
			);
			break;
		case Shelter::MV_B:
			SpriteRender(cursor, mouse_pos_o,
				ScalarToFloat2(.3f),
				{},
				{ 384.0f,128.0f },
				{ 192.0f,256.0f },
				toRadian(180.0f)
			);
			break;
		case Shelter::MV_L:
			SpriteRender(cursor, mouse_pos_o,
				ScalarToFloat2(.3f),
				{},
				{ 384.0f,128.0f },
				{ 192.0f,256.0f },
				toRadian(270.0f)
			);
			break;
		case Shelter::MV_R:
			SpriteRender(cursor, mouse_pos_o,
				ScalarToFloat2(.3f),
				{},
				{ 384.0f,128.0f },
				{ 192.0f,256.0f },
				toRadian(90.0f)
			);
			break;
		default:
			break;
		}
	}
		break;
	default:
	{
		SpriteRender(cursor, mouse_pos_o,
			ScalarToFloat2(.3f),
			{},
			{ 384.0f,128.0f },
			{ 192.0f,256.0f }
		);
		SpriteRender(cursor, mouse_pos_o,
			ScalarToFloat2(.3f),
			{},
			{ 384.0f,128.0f },
			{ 192.0f,256.0f },
			toRadian(90.0f)
		);
		SpriteRender(cursor, mouse_pos_o,
			ScalarToFloat2(.3f),
			{},
			{ 384.0f,128.0f },
			{ 192.0f,256.0f },
			toRadian(180.0f)
		);
		SpriteRender(cursor, mouse_pos_o,
			ScalarToFloat2(.3f),
			{},
			{ 384.0f,128.0f },
			{ 192.0f,256.0f },
			toRadian(270.0f)
		);
	}
		break;
	}
}


void ShDemoPlay()
{
	static Camera eye;
	static AmbientLight l;
	l->option.x = 0.5f;
	l->direction = eye.LightFloamCamera();
	l.Active();
	//eye.Control();
	static Shelter s;
	static bool f = true;
	if (f)
	{
		f = false;
		eye.SetPos({0.0f,15.0f,-0.5f});
		s.init(&eye);
	}
	s.update(DeltaTime());
	s.render();
	s.Ui();
	if (s.isClear)
	{
		font::OutPut(L"クリア", 0, 0);
	}
}



