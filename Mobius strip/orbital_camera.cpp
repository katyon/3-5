#include "orbital_camera.h"
//#define NO_USE_UNDER_HORIZON

VECTOR2D OrbitalCamera::getCursorMoveAmount()
{
	POINT now_point;
	GetCursorPos(&now_point);
	Cursor.current_pos = { (float)now_point.x,(float)now_point.y };

	FLOAT2 center = AliceLib::ToClient(GetWindowSize() / 2.0f);
	SetCursorPos(center.x, center.y);
	Cursor.preview_pos = { center.x, center.y };

	return (center - Cursor.current_pos);
}

OrbitalCamera::OrbitalCamera()
{
	relative_pos = { 0,0,-7 };
}

void OrbitalCamera::update(XMMATRIX player_world_matrix)
{
	// マウスの入力量を取得
	FLOAT2 cursor_amount = getCursorMoveAmount();

	float inclination = VECTOR3D::dot({ 0,1,0 }, getForward());
	if (inclination * -180.0f > 175.0f && cursor_amount.y < 0) return;
	if (inclination * -180.0f < -175.0f && cursor_amount.y > 0) return;

	// カメラの注視点から仮想姿勢ベクトルを作成
	VECTOR3D camera_Z = VECTOR3D::normalize(GetTarget() - GetPos());
	VECTOR3D camera_X = VECTOR3D::normalize(VECTOR3D::cross(VECTOR3D(0, 1, 0), camera_Z));
	VECTOR3D camera_Y = VECTOR3D::normalize(VECTOR3D::cross(camera_X, camera_Z));

	XMVECTOR cam_Zaxis = XMLoadFloat3(&XMFLOAT3(camera_Z.x, camera_Z.y, camera_Z.z));

	// カメラの姿勢軸を基準に、マウスの入力量から進行方向ベクトルを取得
	VECTOR3D dist = (camera_X * cursor_amount.x + camera_Y * cursor_amount.y);
	// 入力がない場合にベクトルの値がすべて0にならないように対策
	if (dist.x == 0 && dist.y == 0 && dist.z == 0) { dist.x = 1, dist.y = 1, dist.z = 1; }

	XMVECTOR dist_vector = XMLoadFloat3(&XMFLOAT3(dist.x, dist.y, dist.z));
	dist_vector = XMVector3Normalize(dist_vector);

	// カメラのZ軸(注視点へのベクトル)と進行方向ベクトルの外積で、このフレームでの回転軸を算出
	XMVECTOR rot_axis;
	rot_axis = XMVector3Cross(dist_vector, cam_Zaxis);
	rot_axis = XMVector3Normalize(rot_axis);

	// 回転軸を基にカーソル入力量を使って、回転クォータニオンを作成
	XMVECTOR quaternion;
	quaternion = XMQuaternionRotationAxis(rot_axis, toRadian(fabsf(cursor_amount.x + cursor_amount.y)*0.1f));

	// 回転クォータニオンから回転行列を作成
	XMMATRIX rotate_matrix;
	rotate_matrix = XMMatrixRotationQuaternion(quaternion);

	// 原点基点のカメラ座標を回転
	XMVECTOR camera_pos = XMLoadFloat3(&XMFLOAT3(relative_pos.x, relative_pos.y, relative_pos.z));
	camera_pos = XMVector3Transform(camera_pos, rotate_matrix);

	// 原点基点のカメラ座標を保存
	XMFLOAT3 store_relative;
	XMStoreFloat3(&store_relative, camera_pos);
	relative_pos = { store_relative.x,store_relative.y,store_relative.z };

	// カメラ座標をプレイヤー空間に変換
	camera_pos = XMVector3Transform(camera_pos, player_world_matrix);

	// カメラ座標を更新
	XMFLOAT3 p_camera_pos;
	XMStoreFloat3(&p_camera_pos, camera_pos);
	FLOAT3 P_camera_pos = FLOAT3(p_camera_pos.x, p_camera_pos.y, p_camera_pos.z);

#ifdef NO_USE_UNDER_HORIZON
	if (P_camera_pos.y < 0.5f) { P_camera_pos.y = 0.5f; }
#endif

	SetPos(P_camera_pos);
}