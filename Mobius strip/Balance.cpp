#include "Balance.h"

namespace Balance
{
	BalanceResult getTilt(const B_weight& right, const B_weight& left, Quaternion* _tile)
	{
		
		BalanceResult result = {};
		
		B_weight _result = left - right;
		
		if (_result == static_cast<B_weight>(0))result = BR_Equal;
		else result = _result > 0 ? BR_Left : BR_Right;
	
		if (_tile != nullptr)
		{
			_tile->reset();

			//頻度
			static constexpr B_weight	frequency	=	static_cast<B_weight>(3);
			//頻度当たりの傾き
			static constexpr float		coefficient	=	15.0f * OnceInRadians;
			//回転の最大角度
			static constexpr float		max_angle	=	75.0f * OnceInRadians;

			//達成値を算出する。
			//達成値  = (左右の差分/傾きの頻度) * １頻度当たりの回転角度
			float angle = (static_cast<float>(_result) / static_cast<float>(frequency)) * coefficient;

			//達成値を保存
			_tile->RotationRoll(fabsf(angle) >= max_angle ? (angle < 0 ? -max_angle : max_angle) : angle);

		}
		return result;
	}

	void makeAnAngle(Quaternion& posture, const Quaternion& tile, float complementary)
	{
		DirectX::XMVECTOR q0 = DirectX::XMLoadFloat4(&posture.GetQuaternion());
		DirectX::XMVECTOR q1 = DirectX::XMLoadFloat4(&tile.GetQuaternion());
		//現在の姿勢から達成値の角度までを補完する
		DirectX::XMVECTOR v = DirectX::XMQuaternionSlerp(q0, q1, complementary);
		static FLOAT4 _quaternion;
		DirectX::XMStoreFloat4(&_quaternion, DirectX::XMQuaternionNormalize(v));
		posture.SetQuaternion(_quaternion);
	}





	void demoPlay()
	{
		//現在の姿勢
		static Quaternion	postrue;
		
		//達成値取得用のコンテナ
		Quaternion			result;

		//左右の重さを保存コンテナ
		//ただのint型
		static B_weight r = 0, l = 0;

		ImGuiNewFrame();

		ImGui::Begin("BalanceDemoPlay");

		if (ImGui::Button("Reset"))
		{
			r = l = 0;
		}

		auto Clamp = [](int& n)->void {if (n < 0)n = 0; };

		if (ImGui::InputInt("right", &r, 1, -1))
		{
			Clamp(r);
		}
		if (ImGui::InputInt("left", &l, 1, -1))
		{
			Clamp(l);
		}

		ImGui::End();

		//左右の重さから達成値を算出
		getTilt(r, l, &result);

		//傾けていく
		makeAnAngle(postrue, result);



		//ToDo

		static Camera eye;
		static AmbientLight light;

		eye.Active();
		light.Active();

		Geometric::Begin();
		Geometric::Cube({}, { 10.0f,1.0f,1.0f }, postrue);
		Geometric::End();

		ImGuiRender();

	}



}