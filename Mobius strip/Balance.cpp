#include "Balance.h"
#include "StageManager.h"

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

	BalanceResult getTilt(const B_weight& right, const B_weight& left, float* _tile)
	{
		BalanceResult result = {};

		B_weight _result = left - right;

		if (_result == static_cast<B_weight>(0))result = BR_Equal;
		else result = _result > 0 ? BR_Left : BR_Right;

		if (_tile != nullptr)
		{
			//頻度
			static constexpr B_weight	frequency = static_cast<B_weight>(3);
			//頻度当たりの傾き
			static constexpr float		coefficient = 15.0f * OnceInRadians;
			//回転の最大角度
			static constexpr float		max_angle = 75.0f * OnceInRadians;

			//達成値を算出する。
			//達成値  = (左右の差分/傾きの頻度) * １頻度当たりの回転角度
			float angle = (static_cast<float>(_result) / static_cast<float>(frequency)) * coefficient;
			angle = fabsf(angle) >= max_angle ? (angle < 0 ? -max_angle : max_angle) : angle;
			(*_tile) = static_cast<float>((angle / max_angle));
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


	void makeAnAngle(int& frame, const float& rate)
	{
		static constexpr int middle_frame = 149;
		frame = middle_frame - static_cast<int>(middle_frame * rate);
	}



	static bool			flgs[2] = {false};
	static bool			isClear = false;
	static ModelReplica	balance_model;
	static ModelReplica	omori_model;
	static FLOAT3		pos[3];
	static Quaternion	postrue;
	static Camera		eye;
	void Init()
	{
		flgs[0] = flgs[1] = false;
		isClear = false;
		if (!balance_model.IsModel()) 
		{
			Model* model = StageManager::getIns()->getModel("tenbin.fbx");
			if (model)
			{
				balance_model.SetModel(model);
			}
			else
			{
				Model _model;
				ModelLoad(_model,"Data\\Objects\\tenbin.fbx");
				balance_model.SetModel(&_model);
			}
			balance_model.PlayAnimation(1, 1);
		}
		if (!omori_model.IsModel())
		{
			Model* model = StageManager::getIns()->getModel("omori.fbx");
			if (model)
			{
				omori_model.SetModel(model);
			}
			else
			{
				Model _model;
				ModelLoad(_model, "Data\\Objects\\omori.fbx");
				omori_model.SetModel(&_model);
			}
		}
		eye.SetPos({ 0.0f,50.0f, - 150.0f });
		eye.SetTarget({ 0,25.0f,0.0f });
	}

	bool Update()
	{
		if (isClear)return true;

		static int r = 0;
		static constexpr int l = 6;
		r = (static_cast<int>(flgs[0]) + static_cast<int>(flgs[1])) * 3;
		float rate = 0.0f;
		getTilt(r, l, &rate);
		int frame = 150;
		makeAnAngle(frame, rate);
		balance_model.UpdateBlendAnimation(0, frame, 1.0f, 0.0f);
		pos[0].y = 10.5f + static_cast<float>((r - l) * 0.8f);
		pos[0].x = -14.25f + static_cast<float>(fabsf(rate) * 1.75f);
		pos[1].y = 10.5f + static_cast<float>((l - r) * 0.8f);
		pos[1].x = 12.25f - static_cast<float>(fabsf(rate) * 1.75f);
		pos[2].y = 10.5f + static_cast<float>((l - r) * 0.8f);
		pos[2].x = 18.25f - static_cast<float>(fabsf(rate) * 1.75f);
		return isClear;
	}

	bool Set()
	{
		if (!flgs[0])return flgs[0] = true;
		else if (!flgs[1])return flgs[1] = true;
		return false;
	}

	void Render()
	{
		XMMATRIX world = GetWorldMatrix({0,0,0}, ScalarToFloat3(1.0f), postrue);
		DirectX::XMStoreFloat3(&pos[0],
			DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&pos[0]), world));
		DirectX::XMStoreFloat3(&pos[1],
			DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&pos[1]), world));
		DirectX::XMStoreFloat3(&pos[2],
			DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&pos[2]), world));

		static AmbientLight light;
		light->direction = { 0.0f,-1.0f,0.0f,0.0f };
		light->option.x = 0.3f;
		light.Active();
		eye.Active();

		ModelRenderBegin();
		ModelRender(balance_model, world);
		ModelRender(omori_model, pos[0], ScalarToFloat3(0.6f), {});
		if (flgs[0])ModelRender(omori_model, pos[1], ScalarToFloat3(0.45f), {});
		if (flgs[1])ModelRender(omori_model, pos[2], ScalarToFloat3(0.45f), {});
		ModelRenderEnd();
	}











	//邪魔だべ
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