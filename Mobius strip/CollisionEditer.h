#pragma once
#include "StageData.h"
#include <list>

using ColBoxs = std::list<ColBox>;
inline void LoadColBoxs(const std::string& file_pass,
	ColBoxs& data)
{
	//�t�@�C����������ΏI��
	if (!checkFileExistence(file_pass))return;
	//�t�@�C���|�C���^���擾
	FILE* fp = fopen(file_pass.c_str(), "r");
	if (fp)
	{
		//�f�[�^����ɂ��Ă���
		data.clear();
		int data_size = 0;
		//�f�[�^�����擾
		fscanf(fp, "%d", &data_size);
		fprintf(fp, "\n");
		//�f�[�^��0�ɖ����Ȃ��ꍇ�I��
		if (data_size <= 0)
		{
			fclose(fp);
			return;
		}
		FLOAT4 _Qu;
		Quaternion Qu;
		//�f�[�^���������R���e�i���쐬����
		data.resize(static_cast<size_t>(data_size));
		//�f�[�^�����[�v����
		for (auto& d : data)
		{
			//���W�f�[�^
			fscanf(fp, "%f,", &d.obb.pos.x);
			fscanf(fp, "%f,", &d.obb.pos.y);
			fscanf(fp, "%f,", &d.obb.pos.z);

			//�X�P�[���l�̃f�[�^
			fscanf(fp, "%f,", &d.obb.len.x);
			fscanf(fp, "%f,", &d.obb.len.y);
			fscanf(fp, "%f,", &d.obb.len.z);

			//�p���f�[�^���擾
			fscanf(fp, "%f,", &_Qu.x);
			fscanf(fp, "%f,", &_Qu.y);
			fscanf(fp, "%f,", &_Qu.z);
			fscanf(fp, "%f,", &_Qu.w);

			Qu.SetQuaternion(_Qu);
			d.obb.setVector(Qu);

			//�I�v�V����(����p�̃I�v�V����)
			fscanf(fp, "%d,", &d.option);

			fprintf(fp, "\n");
		}
		fclose(fp);
	}
}


class CollisionEditer
{
private:
	std::map<std::string, SE_Model>	manager;

	struct CBD
	{
		ColBox		d;
		Quaternion	q;
	};
	std::list<CBD> ColDataList;
	void load_object();
	inline void SaveColBoxs()
	{
		std::string pass = "Data\\ColData\\";
		pass += storage;
		pass += "_CD.csv";
		if (checkFileExistence(pass))
		{
			int result = MessageBoxW(nullptr, L"�㏑�����ĕۑ����܂����H",
				L"�t�@�C�������ɑ��݂��܂�", MB_YESNO);
			if (result != IDYES)return;

		}
		FILE* fp = fopen(pass.c_str(), "w");
		if (fp)
		{
			//�f�[�^����ۑ�
			fprintf(fp, "%d \n", static_cast<int>(ColDataList.size()));
			FLOAT4 q;
			for (const auto& d : ColDataList)
			{
				q = d.q.GetQuaternion();
				fprintf(fp,
					"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d\n",
					d.d.obb.pos.x, d.d.obb.pos.y, d.d.obb.pos.z,
					d.d.obb.len.x, d.d.obb.len.y, d.d.obb.len.z,
					q.x, q.y, q.z, q.w,
					d.d.option);
			}
			fclose(fp);
		}
		MessageBoxW(nullptr, L"�Z�[�u���������܂���", L"Save", MB_OK);
	}
	//�G�f�B�^��p
	inline void LoadColBoxs()
	{
		load_object();
		{
			std::string pass = "Data\\StageData\\";
			pass += storage;
			pass += ".csv";
			if (!checkFileExistence(pass))
			{
				MessageBoxW(nullptr, L"�t�@�C���̃p�X���m�F���Ă�������", L"�t�@�C�������݂��܂���", MB_OK);
				return;
			}
			stage.Load(pass, &manager);
		}
		{

			std::string pass = "Data\\ColData\\";
			pass += storage;
			pass += "_CD.csv";
			//�t�@�C����������ΏI��
			if (!checkFileExistence(pass))return;
			//�t�@�C���|�C���^���擾
			FILE* fp = fopen(pass.c_str(), "r");
			if (fp)
			{
				//�f�[�^����ɂ��Ă���
				ColDataList.clear();
				int data_size = 0;
				//�f�[�^�����擾
				fscanf(fp, "%d", &data_size);
				fprintf(fp, "\n");
				//�f�[�^��0�ɖ����Ȃ��ꍇ�I��
				if (data_size <= 0)
				{
					fclose(fp);
					return;
				}
				FLOAT4 _Qu;
				//�f�[�^���������R���e�i���쐬����
				ColDataList.resize(static_cast<size_t>(data_size));
				//�f�[�^�����[�v����
				for (auto& d : ColDataList)
				{
					//���W�f�[�^
					fscanf(fp, "%f,", &d.d.obb.pos.x);
					fscanf(fp, "%f,", &d.d.obb.pos.y);
					fscanf(fp, "%f,", &d.d.obb.pos.z);

					//�X�P�[���l�̃f�[�^
					fscanf(fp, "%f,", &d.d.obb.len.x);
					fscanf(fp, "%f,", &d.d.obb.len.y);
					fscanf(fp, "%f,", &d.d.obb.len.z);

					//�p���f�[�^���擾
					fscanf(fp, "%f,", &_Qu.x);
					fscanf(fp, "%f,", &_Qu.y);
					fscanf(fp, "%f,", &_Qu.z);
					fscanf(fp, "%f,", &_Qu.w);

					d.q.SetQuaternion(_Qu);
					d.d.obb.setVector(d.q);

					//�I�v�V����(����p�̃I�v�V����)
					fscanf(fp, "%d,", &d.d.option);

					fprintf(fp, "\n");
				}
				fclose(fp);
			}
		}
	}
	char							stage_name[256] = "stage_data";
	static constexpr float n180 = -(180 * OnceInRadians);//-180��
	static constexpr float n90 = -(90 * OnceInRadians);//-90��
	static constexpr float n30 = -(30 * OnceInRadians);//-30��
	static constexpr float n15 = -(15 * OnceInRadians);//-15��

	static constexpr float p180 = 180 * OnceInRadians;//180��
	static constexpr float p90 = 90 * OnceInRadians;//90��
	static constexpr float p30 = 30 * OnceInRadians;//30��
	static constexpr float p15 = 15 * OnceInRadians;//15��

	StageData stage;
	AmbientLight					ambient;
	class qCamera :public Camera
	{
	public:
		void Control(Quaternion& q, float speed, float t_angle)
		{
			static PostureVector vec;
			vec.CreateVector(q);
			if (input::STATE(input::MOUSE_R))
			{
				if (input::STATE('D'))pos += static_cast<FLOAT3>(vec.right * speed);
				if (input::STATE('A'))pos -= static_cast<FLOAT3>(vec.right * speed);
				if (input::STATE('W'))pos += static_cast<FLOAT3>(vec.forward * speed);
				if (input::STATE('S'))pos -= static_cast<FLOAT3>(vec.forward * speed);
				if (input::STATE('E'))pos.y += speed;
				if (input::STATE('Q'))pos.y -= speed;
			}
			if (input::STATE(input::MOUSE_L))
			{
				if (input::STATE('D'))
				{
					q.RotationYaw(t_angle);
					vec.CreateVector(q);
				}
				if (input::STATE('A'))
				{
					q.RotationYaw(-t_angle);
					vec.CreateVector(q);
				}
				if (input::STATE('W'))
				{
					q.RotationPitch(-t_angle);
					vec.CreateVector(q);
				}
				if (input::STATE('S'))
				{
					q.RotationPitch(t_angle);
					vec.CreateVector(q);
				}
			}
			target = pos + static_cast<FLOAT3>(vec.forward);
		}
	};
	qCamera							camera;
	Quaternion						camera_q;
	float							speed = 15.0f;
	void GUI();
	void update();
	void render();
	std::string						storage;
	bool isShow = true;
	CollisionEditer();
	~CollisionEditer();
public:
	static void Run()
	{
		static CollisionEditer ce;
		ImGuiNewFrame();
		ce.update();
		ce.render();
		ImGuiRender();
	}
};

