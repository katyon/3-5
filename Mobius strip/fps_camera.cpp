#include "fps_camera.h"

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
	
	return (center - Cursor.current_pos) * (1 + (correct_sensitivity - 5) * 0.18f);
}

int FPSCamera::correct_sensitivity = 5;
FPSCamera::FPSCamera()
{
	relative_pos = { 0, 0, CAMERA_DISTANCE };
	SetTarget({0, 0, FOCUS_RANGE});
	SetPerspectiveMatrix(0.5f, 1000.0f);
}

void FPSCamera::initPos()
{
	relative_pos = { 0, 0, CAMERA_DISTANCE };
}

void FPSCamera::update(XMMATRIX player_world_matrix, FLOAT3 center)
{
	if (auto_focus) { focusCompulsion(player_world_matrix, center); }
	else { control(player_world_matrix, center); }

	VECTOR3D current_vector = this->GetTarget() - pos;
	VECTOR3D target_vector = focus_target - pos;
	current_vector = current_vector.normalize();
	target_vector = target_vector.normalize();
	float angle = VECTOR3D::dot(current_vector, target_vector);
	//if (angle < 0) { angle += 1.0f; }
	Debug->SetString("��]�p %f", angle);

	if (input::TRG('G'))
	{
		setAutoFocus({ -53, 12.5f, 0 }, 0.1f);
	}
}

void FPSCamera::control(XMMATRIX player_world_matrix, FLOAT3 center)
{
	// �}�E�X�̓��͗ʂ��擾
	FLOAT2 cursor_amount = getCursorMoveAmount();
	cursor_amount.y *= -0.9;

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

	// ���݂̃J�����̐����p�x
	float angle;
	angle = camera_Z.dot(VECTOR3D::normalize({ camera_Z.x, 0, camera_Z.z }));

	Debug->SetString("angle %f, radian %f", toAngle(angle), angle);
	Debug->SetString("���Z��:%f", toRadian(VECTOR2D::distanceFrom(cursor_amount, VECTOR2D(0, 0)) * 0.1));
	Debug->SetString("relative_pos x:%f y:%f z:%f", relative_pos.x, relative_pos.y, relative_pos.z);

	// ��]������ɃJ�[�\�����͗ʂ��g���āA��]�N�H�[�^�j�I�����쐬
	XMVECTOR quaternion;
	quaternion = DirectX::XMQuaternionRotationAxis(rot_axis, toRadian(VECTOR2D::distanceFrom(cursor_amount, VECTOR2D(0, 0)) * 0.1));

	// ��]�N�H�[�^�j�I�������]�s����쐬
	XMMATRIX rotate_matrix;
	rotate_matrix = XMMatrixRotationQuaternion(quaternion);

	// ���_��_�̃J�������W����]
	XMVECTOR camera_pos = XMLoadFloat3(&XMFLOAT3(relative_pos.x, relative_pos.y, relative_pos.z));
	camera_pos = XMVector3Transform(camera_pos, rotate_matrix);

	// ���_��_�̃J�������W��ۑ�
	XMFLOAT3 store_relative;
	DirectX::XMStoreFloat3(&store_relative, camera_pos);
	relative_pos = { store_relative.x, store_relative.y, store_relative.z };

	// �J�������W���v���C���[��Ԃɕϊ�
	camera_pos = XMVector3Transform(camera_pos, player_world_matrix);

	// �J�������W���X�V
	XMFLOAT3 p_camera_pos;
	DirectX::XMStoreFloat3(&p_camera_pos, camera_pos);
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

	DirectX::XMStoreFloat3(&targetVec3, targetVec);
	targetPos = FLOAT3(center.x, center.y, center.z) + FLOAT3(targetVec3.x, targetVec3.y, targetVec3.z) * 10.0f;
	SetTarget(targetPos);
	zoom();

//#ifdef DEBUG_SENSITIVITY_SETTING
//	if (input::TRG('N'))
//	{
//		if (FPSCamera::correct_sensitivity > 0) FPSCamera::correct_sensitivity--;
//	}
//	if (input::TRG('M'))
//	{
//		if (FPSCamera::correct_sensitivity < 10) FPSCamera::correct_sensitivity++;
//	}
//#endif
}

void FPSCamera::zoom()
{
	if (input::STATE(input::MOUSE_C))
	{
		if (magnification > 30) { magnification -= 2; }
	}
	else
	{
		if (magnification < 60) { magnification += 2; }
	}
	SetFov(toRadian(magnification));
}

void FPSCamera::setAutoFocus(FLOAT3 focus_point, float complement)
{
	if (complement < 0) return;

	auto_focus = true;
	focus_target = focus_point;
	this->complement = complement;
}

void FPSCamera::autoFin(XMMATRIX player_world_matrix, FLOAT3 center)
{
	// ���_��_�̃J�������W����]
	XMVECTOR camera_pos = XMLoadFloat3(&FLOAT3(0, 0, -1));

	// ���_��_�̃J�������W��ۑ�
	XMFLOAT3 store_relative;
	DirectX::XMStoreFloat3(&store_relative, camera_pos);
	relative_pos = { store_relative.x, store_relative.y, store_relative.z };

	// �J�������W���v���C���[��Ԃɕϊ�
	camera_pos = XMVector3Transform(camera_pos, player_world_matrix);

	// �J�������W���X�V
	XMFLOAT3 p_camera_pos;
	DirectX::XMStoreFloat3(&p_camera_pos, camera_pos);
	FLOAT3 P_camera_pos = FLOAT3(p_camera_pos.x, p_camera_pos.y, p_camera_pos.z);

	FLOAT3 R_camera_pos = P_camera_pos;

	SetPos(P_camera_pos);

	FLOAT3 targetPos;
	XMFLOAT3 targetVec3;
	XMVECTOR targetVec;

	targetVec3 = { R_camera_pos.x - center.x, R_camera_pos.y - center.y, R_camera_pos.z - center.z };
	targetVec = XMLoadFloat3(&targetVec3);

	DirectX::XMStoreFloat3(&targetVec3, targetVec);
	targetPos = FLOAT3(center.x, center.y, center.z) + FLOAT3(targetVec3.x, targetVec3.y, targetVec3.z) * 10.0f;
	SetTarget(targetPos);

	auto_focus = false;
}

void FPSCamera::focusCompulsion(XMMATRIX player_world_matrix, FLOAT3 center)
{
	VECTOR3D current_vector = this->GetTarget() - pos;
	VECTOR3D target_vector = focus_target - pos;
	current_vector = current_vector.normalize();
	target_vector = target_vector.normalize();

	// ���t��Ԏ��̏C������
	if (current_vector.isParallel(target_vector)) 
	{
		// ���_��_�̃J�������W����]
		XMVECTOR camera_pos = XMLoadFloat3(&FLOAT3(-1, 0, 0));

		// ���_��_�̃J�������W��ۑ�
		XMFLOAT3 store_relative;
		DirectX::XMStoreFloat3(&store_relative, camera_pos);
		relative_pos = { store_relative.x, store_relative.y, store_relative.z };

		// �J�������W���v���C���[��Ԃɕϊ�
		camera_pos = XMVector3Transform(camera_pos, player_world_matrix);

		// �J�������W���X�V
		XMFLOAT3 p_camera_pos;
		DirectX::XMStoreFloat3(&p_camera_pos, camera_pos);
		FLOAT3 P_camera_pos = FLOAT3(p_camera_pos.x, p_camera_pos.y, p_camera_pos.z);

		FLOAT3 R_camera_pos = P_camera_pos;

		SetPos(P_camera_pos);

		FLOAT3 targetPos;
		XMFLOAT3 targetVec3;
		XMVECTOR targetVec;

		targetVec3 = { R_camera_pos.x - center.x, R_camera_pos.y - center.y, R_camera_pos.z - center.z };
		targetVec = XMLoadFloat3(&targetVec3);

		DirectX::XMStoreFloat3(&targetVec3, targetVec);
		targetPos = FLOAT3(center.x, center.y, center.z) + FLOAT3(targetVec3.x, targetVec3.y, targetVec3.z) * 10.0f;
		SetTarget(targetPos);
		return;
	}

	VECTOR3D camera_Z = VECTOR3D::normalize(center - pos);
	VECTOR3D camera_X = VECTOR3D::normalize(VECTOR3D::cross(VECTOR3D(0, 1, 0), camera_Z));
	VECTOR3D camera_Y = VECTOR3D::normalize(VECTOR3D::cross(camera_X, camera_Z));

	forward = camera_Z;

	// ��]��
	VECTOR3D rotate_rot = VECTOR3D::cross(current_vector, target_vector);
	XMVECTOR rot_vector = XMLoadFloat3(&XMFLOAT3(rotate_rot));
	rot_vector = XMVector3Normalize(rot_vector);

	// ��]�p
	float angle = acosf(VECTOR3D::dot(current_vector, target_vector));
	if (angle < 0) { angle += 1.0f; }
	Debug->SetString("��]�p %f", angle);

	// ���`���
	angle *= complement;

	// ��]�N�H�[�^�j�I�����쐻
	XMVECTOR quaternion;
	quaternion = DirectX::XMQuaternionRotationAxis(rot_vector, angle);

	// ��]�N�H�[�^�j�I�������]�s����쐬
	XMMATRIX rotate_matrix;
	rotate_matrix = XMMatrixRotationQuaternion(quaternion);

	// ���_��_�̃J�������W����]
	XMVECTOR camera_pos = XMLoadFloat3(&XMFLOAT3(relative_pos.x, relative_pos.y, relative_pos.z));
	camera_pos = XMVector3Transform(camera_pos, rotate_matrix);

	// ���_��_�̃J�������W��ۑ�
	XMFLOAT3 store_relative;
	DirectX::XMStoreFloat3(&store_relative, camera_pos);
	relative_pos = { store_relative.x, store_relative.y, store_relative.z };

	// �J�������W���v���C���[��Ԃɕϊ�
	camera_pos = XMVector3Transform(camera_pos, player_world_matrix);

	// �J�������W���X�V
	XMFLOAT3 p_camera_pos;
	DirectX::XMStoreFloat3(&p_camera_pos, camera_pos);
	FLOAT3 P_camera_pos = FLOAT3(p_camera_pos.x, p_camera_pos.y, p_camera_pos.z);

	FLOAT3 R_camera_pos = P_camera_pos;

	SetPos(P_camera_pos);

	FLOAT3 targetPos;
	XMFLOAT3 targetVec3;
	XMVECTOR targetVec;

	targetVec3 = { R_camera_pos.x - center.x, R_camera_pos.y - center.y, R_camera_pos.z - center.z };
	targetVec = XMLoadFloat3(&targetVec3);

	DirectX::XMStoreFloat3(&targetVec3, targetVec);
	targetPos = FLOAT3(center.x, center.y, center.z) + FLOAT3(targetVec3.x, targetVec3.y, targetVec3.z) * 10.0f;
	SetTarget(targetPos);
}