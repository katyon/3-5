#include "fps_camera.h"

//FPSCamera::FPSCamera()
//{
//	Cursor.preview_pos = { 0,0 };
//	Cursor.current_pos = { 0,0 };
//
//	pos = { 0,0,0 };
//	focus_point = { 0, 0, 10 };
//	relative_focus_point = { 0,0,10 };
//	rotate_to_target = XMMatrixIdentity();
//}
//
//VECTOR2D FPSCamera::getCursorMoveAmount()
//{
//	POINT now_point;
//	GetCursorPos(&now_point);
//	Cursor.current_pos = { (float)now_point.x,(float)now_point.y };
//
//	FLOAT2 center = ToClient(GetWindowSize() / 2.0f);
//	center.x = floorf(center.x);
//	center.y = floorf(center.y);
//	SetCursorPos(center.x, center.y);
//	Cursor.preview_pos = { center.x, center.y };
//
//	Debug->SetString("center %f %f  cursor %f %f", center.x, center.y, Cursor.current_pos.x, Cursor.current_pos.y);
//
//	return (center - Cursor.current_pos) * 0.18f;
//}
//
//void FPSCamera::init()
//{
//
//}
//
//void FPSCamera::update(FLOAT3 player_pos)
//{
//	// �}�E�X�̓��͗ʂ��擾
//	FLOAT2 cursor_amount = getCursorMoveAmount();
//
//	//pos = player_pos;
//	//Debug->SetString("getCursor %f %f", getCursorMoveAmount().x, getCursorMoveAmount().y);
//	
//	// �J�����̒����_���璍���_�̉��z�p���x�N�g�����쐬
//	VECTOR3D focus_Z = VECTOR3D::normalize(pos - focus_point);	// �J�������璍���_�ւ̃x�N�g��
//	VECTOR3D focus_X = VECTOR3D::normalize(VECTOR3D::cross(VECTOR3D(0, 1, 0), focus_Z)); // Z���Ɛ����Ȑ��������x�N�g��
//	VECTOR3D focus_Y = VECTOR3D::normalize(VECTOR3D::cross(focus_X, focus_Z)); // Z����X���̊O�ς��琬��������x�N�g��
//	
//	forward = focus_Z;
//	
//	float inclination = VECTOR3D::dot({ 0,1,0 }, getForward());
//	if (inclination * -180.0f > 175.0f && cursor_amount.y < 0) return;
//	if (inclination * -180.0f < -175.0f && cursor_amount.y > 0) return;
//	
//	XMVECTOR focus_Zaxis = XMLoadFloat3(&XMFLOAT3(focus_Z.x, focus_Z.y, focus_Z.z));
//	
//	// �����_�̎p��������ɁA�}�E�X�̓��͗ʂ���i�s�����x�N�g�����擾
//	VECTOR3D dist = (focus_X * cursor_amount.x + focus_Y * cursor_amount.y);
//	// ���͂��Ȃ��ꍇ�Ƀx�N�g���̒l�����ׂ�0�ɂȂ�Ȃ��悤�ɑ΍�
//	if (dist.x == 0 && dist.y == 0 && dist.z == 0) { dist.x = 1, dist.y = 1, dist.z = 1; }
//
//	Debug->SetString("dist %f %f %f", dist.x, dist.y, dist.z);
//	
//	XMVECTOR dist_vector = XMLoadFloat3(&XMFLOAT3(dist.x, dist.y, dist.z));
//	dist_vector = XMVector3Normalize(dist_vector);
//	
//	// �����_��Z��(�����_�ւ̃x�N�g��)�Ɛi�s�����x�N�g���̊O�ςŁA���̃t���[���ł̉�]�����Z�o
//	XMVECTOR rot_axis;
//	rot_axis = XMVector3Cross(dist_vector, focus_Zaxis);
//	rot_axis = XMVector3Normalize(rot_axis);
//	
//	// ��]������ɃJ�[�\�����͗ʂ��g���āA��]�N�H�[�^�j�I�����쐬
//	XMVECTOR quaternion;
//	quaternion = XMQuaternionRotationAxis(rot_axis, toRadian(fabsf(cursor_amount.x + cursor_amount.y) * 0.1f));
//
//	Debug->SetString("cursor %f %f", cursor_amount.x, cursor_amount.y);
//	
//	// ��]�N�H�[�^�j�I�������]�s����쐬
//	XMMATRIX rotate_matrix;
//	rotate_matrix = XMMatrixRotationQuaternion(quaternion);
//	
//	// ���_��_�̒����_���W����]
//	XMVECTOR focus_pos = XMLoadFloat3(&XMFLOAT3(relative_focus_point.x, relative_focus_point.y, relative_focus_point.z));
//	focus_pos = XMVector3Transform(focus_pos, rotate_matrix);
//	
//	// ���_��_�̒����_���W��ۑ�
//	XMFLOAT3 store_relative;
//	XMStoreFloat3(&store_relative, focus_pos);
//	relative_focus_point = { store_relative.x,store_relative.y,store_relative.z };
//
//	Debug->SetString("relative focus %f %f %f", relative_focus_point.x, relative_focus_point.y, relative_focus_point.z);
//	
//	// �v���C���[���W����
//	XMMATRIX camera_matrix;
//	camera_matrix = GetWorldMatrix(player_pos, { 1,1,1 }, { 1,1,1 });
//
//	// �����_���W���v���C���[��Ԃɕϊ�
//	focus_pos = XMVector3Transform(focus_pos, camera_matrix);
//	
//	// �����_���W���X�V
//	XMFLOAT3 p_focus_pos;
//	XMStoreFloat3(&p_focus_pos, focus_pos);
//	FLOAT3 P_focus_pos = FLOAT3(p_focus_pos.x, p_focus_pos.y, p_focus_pos.z);
//	
//	//FLOAT3 R_focus_pos = P_focus_pos;
//	focus_point = P_focus_pos;
//
//	Debug->SetString("R_focus_pos %f %f %f", focus_point.x, focus_point.y, focus_point.z);
//	
//#ifdef NO_USE_UNDER_HORIZON
//	if (P_camera_pos.y < 0.5f) { P_camera_pos.y = 0.5f; }
//#endif
//	
//	SetPos(player_pos);
//	
//	FLOAT3 targetPos;
//	XMFLOAT3 targetVec3;
//	XMVECTOR targetVec;
//	
//	targetVec3 = { pos.x + focus_point.x, pos.y + focus_point.y, pos.z + focus_point.z };
//	Debug->SetString("�����_���W %f %f %f", focus_point.x, focus_point.y, focus_point.z);
//	Debug->SetString("�J�������W %f %f %f", pos.x, pos.y, pos.z);
//	targetVec = XMLoadFloat3(&targetVec3);
//	targetVec = XMVector3Transform(targetVec, rotate_to_target);
//	
//	XMStoreFloat3(&targetVec3, targetVec);
//	targetPos = FLOAT3(pos.x, pos.y + 1, pos.z) + FLOAT3(targetVec3.x, targetVec3.y, targetVec3.z) * 10.0f;
//	SetTarget(targetPos);
//
//	Geometric::Sphere(GetWorldMatrix(targetPos, { 1,1,1 }, { 1,1,1 }));
//	// zoom();
//}

//XMMATRIX calculateAngleToTarget(float angle)
//{
//	float x = toRadian(angle);
//
//	XMVECTOR quaternion;
//	quaternion = XMQuaternionRotationAxis({ 0,1,0 }, x);
//
//	XMMATRIX rotate_matrix = XMMatrixRotationQuaternion(quaternion);
//
//	return rotate_matrix;
//}

VECTOR2D FPSCamera::getCursorMoveAmount()
{
	POINT now_point;
	GetCursorPos(&now_point);
	Cursor.current_pos = { (float)now_point.x,(float)now_point.y };
	
	FLOAT2 center = ToClient(GetWindowSize() / 2.0f);
	center.x = floorf(center.x);
	center.y = floorf(center.y);
	SetCursorPos(center.x, center.y);
	Cursor.preview_pos = { center.x, center.y };
	
	Debug->SetString("center %f %f  cursor %f %f", center.x, center.y, Cursor.current_pos.x, Cursor.current_pos.y);
	
	return (center - Cursor.current_pos) * 1;
}

int FPSCamera::correct_sensitivity = 5;
FPSCamera::FPSCamera()
{
	relative_pos = { 0, 0,1 };
	SetTarget({0, 0, 5});
	//rotate_to_target = calculateAngleToTarget(10);
}

void FPSCamera::initPos()
{
	relative_pos = { 0, 0,1 };
}

void FPSCamera::update(XMMATRIX player_world_matrix, FLOAT3 center)
{
	// �}�E�X�̓��͗ʂ��擾
	FLOAT2 cursor_amount = getCursorMoveAmount();
	cursor_amount.y *= -1;

	// �J�����̒����_���牼�z�p���x�N�g�����쐬
	VECTOR3D camera_Z = VECTOR3D::normalize(center - pos);
	VECTOR3D camera_X = VECTOR3D::normalize(VECTOR3D::cross(VECTOR3D(0, 1, 0), camera_Z));
	VECTOR3D camera_Y = VECTOR3D::normalize(VECTOR3D::cross(camera_X, camera_Z));

	forward = camera_Z;

	float inclination = VECTOR3D::dot({ 0,1,0 }, getForward());
	if (inclination * -180.0f > 175.0f && cursor_amount.y < 0) return;
	if (inclination * -180.0f < -175.0f && cursor_amount.y > 0) return;

	XMVECTOR cam_Zaxis = XMLoadFloat3(&XMFLOAT3(camera_Z.x, camera_Z.y, camera_Z.z));

	// �J�����̎p��������ɁA�}�E�X�̓��͗ʂ���i�s�����x�N�g�����擾
	VECTOR3D dist = (camera_X * cursor_amount.x + camera_Y * cursor_amount.y);
	// ���͂��Ȃ��ꍇ�Ƀx�N�g���̒l�����ׂ�0�ɂȂ�Ȃ��悤�ɑ΍�
	if (dist.x == 0 && dist.y == 0 && dist.z == 0) { dist.x = 1, dist.y = 1, dist.z = 1; }

	XMVECTOR dist_vector = XMLoadFloat3(&XMFLOAT3(dist.x, dist.y, dist.z));
	dist_vector = XMVector3Normalize(dist_vector);

	// �J������Z��(�����_�ւ̃x�N�g��)�Ɛi�s�����x�N�g���̊O�ςŁA���̃t���[���ł̉�]�����Z�o
	XMVECTOR rot_axis;
	rot_axis = XMVector3Cross(dist_vector, cam_Zaxis);
	rot_axis = XMVector3Normalize(rot_axis);

	// ��]������ɃJ�[�\�����͗ʂ��g���āA��]�N�H�[�^�j�I�����쐬
	XMVECTOR quaternion;
	quaternion = XMQuaternionRotationAxis(rot_axis, toRadian(fabsf(cursor_amount.x + cursor_amount.y) * 0.1f));

	// ��]�N�H�[�^�j�I�������]�s����쐬
	XMMATRIX rotate_matrix;
	rotate_matrix = XMMatrixRotationQuaternion(quaternion);

	// ���_��_�̃J�������W����]
	XMVECTOR camera_pos = XMLoadFloat3(&XMFLOAT3(relative_pos.x, relative_pos.y, relative_pos.z));
	camera_pos = XMVector3Transform(camera_pos, rotate_matrix);

	Debug->SetString("relative_pos %f %f %f", relative_pos.x, relative_pos.y, relative_pos.z);

	// ���_��_�̃J�������W��ۑ�
	XMFLOAT3 store_relative;
	XMStoreFloat3(&store_relative, camera_pos);
	relative_pos = { store_relative.x, store_relative.y, store_relative.z };

	// �J�������W���v���C���[��Ԃɕϊ�
	camera_pos = XMVector3Transform(camera_pos, player_world_matrix);

	// �J�������W���X�V
	XMFLOAT3 p_camera_pos;
	XMStoreFloat3(&p_camera_pos, camera_pos);
	FLOAT3 P_camera_pos = FLOAT3(p_camera_pos.x, p_camera_pos.y, p_camera_pos.z);

	FLOAT3 R_camera_pos = P_camera_pos;

#ifdef NO_USE_UNDER_HORIZON
	if (P_camera_pos.y < 0.5f) { P_camera_pos.y = 0.5f; }
#endif
	//P_camera_pos.y = 12.5f;
	SetPos(P_camera_pos);

	FLOAT3 targetPos;
	XMFLOAT3 targetVec3;
	XMVECTOR targetVec;

	targetVec3 = { R_camera_pos.x - center.x, R_camera_pos.y - center.y, R_camera_pos.z - center.z };
	Debug->SetString("�����_�x�N�g�� %f %f %f", targetVec3.x, targetVec3.y, targetVec3.z);
	targetVec = XMLoadFloat3(&targetVec3);
	//targetVec = XMVector3Transform(targetVec, rotate_to_target);

	XMStoreFloat3(&targetVec3, targetVec);
	targetPos = FLOAT3(center.x, center.y, center.z) + FLOAT3(targetVec3.x, targetVec3.y, targetVec3.z) * 10.0f;
	Geometric::Sphere(GetWorldMatrix(targetPos, { 1,1,1 }, { 0,0,0 }));
	SetTarget(targetPos);
	zoom();
}

void FPSCamera::zoom()
{
	if (input::STATE(input::MOUSE_R))
	{
		if (magnification > 15) { magnification -= 2; }
		useADS = true;
	}
	else
	{
		if (magnification < 30) { magnification += 2; }
		useADS = false;
	}
	SetFov(toRadian(magnification));
}