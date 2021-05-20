#include "tps_camera.h"
#define NO_USE_UNDER_HORIZON

XMMATRIX calculateAngleToTarget(float angle)
{
	float x = toRadian(angle);

	XMVECTOR quaternion;
	quaternion = XMQuaternionRotationAxis({ 0,1,0 }, x);

	XMMATRIX rotate_matrix = XMMatrixRotationQuaternion(quaternion);

	return rotate_matrix;
}

VECTOR2D TPSCamera::getCursorMoveAmount()
{
	POINT now_point;
	GetCursorPos(&now_point);
	Cursor.current_pos = { (float)now_point.x,(float)now_point.y };

	FLOAT2 center = AliceLib::ToClient(GetWindowSize() / 2.0f);
	SetCursorPos(center.x, center.y);
	Cursor.preview_pos = { center.x, center.y };

	return (center - Cursor.current_pos) * (1 + (correct_sensitivity-5)*0.18f);
}

int TPSCamera::correct_sensitivity = 5;
TPSCamera::TPSCamera()
{
	relative_pos = { 0,0,-7 };
	rotate_to_target = calculateAngleToTarget(10);
}

void TPSCamera::initPos()
{
	relative_pos = { 0,0,-7 };
}

void TPSCamera::update(XMMATRIX player_world_matrix, FLOAT3 center)
{
	// �}�E�X�̓��͗ʂ��擾
	FLOAT2 cursor_amount = getCursorMoveAmount();

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
	if (dist.x == 0 && dist.y == 0) { dist.x = 1, dist.y = 1; }

	XMVECTOR dist_vector = XMLoadFloat3(&XMFLOAT3(dist.x, dist.y, dist.z));
	dist_vector = XMVector3Normalize(dist_vector);

	// �J������Z��(�����_�ւ̃x�N�g��)�Ɛi�s�����x�N�g���̊O�ςŁA���̃t���[���ł̉�]�����Z�o
	XMVECTOR rot_axis;
	rot_axis = XMVector3Cross(dist_vector, cam_Zaxis);
	rot_axis = XMVector3Normalize(rot_axis);

	// ��]������ɃJ�[�\�����͗ʂ��g���āA��]�N�H�[�^�j�I�����쐬
	XMVECTOR quaternion;
	quaternion = XMQuaternionRotationAxis(rot_axis, toRadian((fabs(cursor_amount.x) + fabs(cursor_amount.y)) * 0.1f));

	// ��]�N�H�[�^�j�I�������]�s����쐬
	XMMATRIX rotate_matrix;
	rotate_matrix = XMMatrixRotationQuaternion(quaternion);

	// ���_��_�̃J�������W����]
	XMVECTOR camera_pos = XMLoadFloat3(&XMFLOAT3(relative_pos.x, relative_pos.y, relative_pos.z));
	camera_pos = XMVector3Transform(camera_pos, rotate_matrix);

	// ���_��_�̃J�������W��ۑ�
	XMFLOAT3 store_relative;
	XMStoreFloat3(&store_relative, camera_pos);
	relative_pos = { store_relative.x,store_relative.y,store_relative.z };

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

	SetPos(P_camera_pos);

	FLOAT3 targetPos;
	XMFLOAT3 targetVec3;
	XMVECTOR targetVec;

	targetVec3 = { center.x - R_camera_pos.x, center.y - R_camera_pos.y, center.z - R_camera_pos.z };
	Debug->SetString("�����_�x�N�g�� %f %f %f", targetVec3.x, targetVec3.y, targetVec3.z);
	targetVec = XMLoadFloat3(&targetVec3);
	targetVec = XMVector3Transform(targetVec, rotate_to_target);

	XMStoreFloat3(&targetVec3, targetVec);
	targetPos = FLOAT3(center.x, center.y + 1, center.z) + FLOAT3(targetVec3.x, targetVec3.y, targetVec3.z) * 10.0f;
	SetTarget(targetPos);
	zoom();
}

void TPSCamera::zoom()
{
	if (input::STATE(input::MOUSE_R))
	{
		if (magnification > 15) { magnification-=2; }
		useADS = true;
	}
	else
	{
		if (magnification < 30) { magnification+=2; }
		useADS = false;
	}
	SetFov(toRadian(magnification));
}