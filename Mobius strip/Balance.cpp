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

			//�p�x
			static constexpr B_weight	frequency	=	static_cast<B_weight>(3);
			//�p�x������̌X��
			static constexpr float		coefficient	=	15.0f * OnceInRadians;
			//��]�̍ő�p�x
			static constexpr float		max_angle	=	75.0f * OnceInRadians;

			//�B���l���Z�o����B
			//�B���l  = (���E�̍���/�X���̕p�x) * �P�p�x������̉�]�p�x
			float angle = (static_cast<float>(_result) / static_cast<float>(frequency)) * coefficient;

			//�B���l��ۑ�
			_tile->RotationRoll(fabsf(angle) >= max_angle ? (angle < 0 ? -max_angle : max_angle) : angle);

		}
		return result;
	}

	void makeAnAngle(Quaternion& posture, const Quaternion& tile, float complementary)
	{
		DirectX::XMVECTOR q0 = DirectX::XMLoadFloat4(&posture.GetQuaternion());
		DirectX::XMVECTOR q1 = DirectX::XMLoadFloat4(&tile.GetQuaternion());
		//���݂̎p������B���l�̊p�x�܂ł�⊮����
		DirectX::XMVECTOR v = DirectX::XMQuaternionSlerp(q0, q1, complementary);
		static FLOAT4 _quaternion;
		DirectX::XMStoreFloat4(&_quaternion, DirectX::XMQuaternionNormalize(v));
		posture.SetQuaternion(_quaternion);
	}





	void demoPlay()
	{
		//���݂̎p��
		static Quaternion	postrue;
		
		//�B���l�擾�p�̃R���e�i
		Quaternion			result;

		//���E�̏d����ۑ��R���e�i
		//������int�^
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

		//���E�̏d������B���l���Z�o
		getTilt(r, l, &result);

		//�X���Ă���
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