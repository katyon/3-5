#pragma once
#define	_CRT_SECURE_NO_WARNINGS
#include <iosfwd>
#include "AliceLib/AliceLib.h"


/*
	�X�e�[�W���ɂ���I�u�W�F�N�g�̃f�[�^�\����
*/
struct StageObject
{
	//���f���̃t�@�C���A�h���X������
	//����ID���g�����f�����擾����
	std::string		ID;
	//���f����ݒu������W
	FLOAT3			position;
	//���f���̃X�P�[��
	FLOAT3			scales;
	//���f���p��
	Quaternion		posture;
	//�`�悷�邩�̃t���O
	bool			isShow = true;
	//���f���̕����i
	ModelReplica	body;
	//�I�v�V�����@�A�C�e���Ŏg��
	//�f�t�H���g�l -1
	int				option = -1;

	void	Load(Model* body_data, const StageObject& data)
	{
		ID = data.ID;
		position = data.position;
		scales = data.scales;
		posture = data.posture;
		isShow = data.isShow;
		body.SetModel(body_data);
		option = data.option;
	}

	void	Render() { isShow ? ModelRender(body, position, scales, posture) : 0; }


	void	Clear()
	{
		ID = "";
		position = {};
		scales = { 1.0f,1.0f,1.0f };
		posture.reset();
		body.ReSet();
	}
};

struct ColBox
{
	int option;
	OBB obb;
	ColBox() {};
	ColBox(const FLOAT3& pos,
		const FLOAT3& len,
		const Quaternion& angle,
		int o)
		:obb(pos, len, angle), option(o) {}
	ColBox(const OBB& b,
		int o) :obb(b), option(o) {}
};

/*
	�X�e�[�W���ɐݒu���郂�f��
	���J�v�Z�������N���X
*/
typedef struct cStageModel final
{
	Model m;
	cStageModel(std::string file_pass)
	{
		//�S�Ẵ��f����Maya�ō���Ă���Ă��Őݒ�
		ModelLoad(m, file_pass.c_str(), MAYA);
	}
}SE_Model;


/*
	�t�@�C�������݂��邩�e�X�g����֐�
*/
inline bool checkFileExistence(const std::string& str)
{
	std::ifstream ifs(str);
	return ifs.is_open();
}


/*
	�t�@�C������X�e�[�W�f�[�^���擾����֐�
*/
template<size_t arr_size>
inline void load_stage_from_file(const std::string& file_pass,
	StageObject(&objects)[arr_size], std::map<std::string, cStageModel>* manager)
{
	//�t�@�C�����Ȃ��Ȃ烍�[�h���Ȃ�
	if (!checkFileExistence(file_pass))
	{
		return;
	}
	FILE* fp = fopen(file_pass.c_str(), "r");
	static	FLOAT4 q;
	if (fp)
	{
		int   isbody, isshow;
		for (StageObject& object : objects)
		{
			object.Clear();

			char filename[256] = {};
			//�g�p���Ă��邩�̃t���O
			fscanf(fp, "%d,", &isbody);
			//�\�����Ă��邩�̃t���O
			fscanf(fp, "%d,", &isshow);
			//���W�f�[�^
			fscanf(fp, "%f,", &object.position.x);
			fscanf(fp, "%f,", &object.position.y);
			fscanf(fp, "%f,", &object.position.z);
			//�X�P�[���l�̃f�[�^
			fscanf(fp, "%f,", &object.scales.x);
			fscanf(fp, "%f,", &object.scales.y);
			fscanf(fp, "%f,", &object.scales.z);
			//�N�I�[�^�j�I���̐����f�[�^
			fscanf(fp, "%f,", &q.x);
			fscanf(fp, "%f,", &q.y);
			fscanf(fp, "%f,", &q.z);
			fscanf(fp, "%f,", &q.w);
			//�I�v�V����
			fscanf(fp, "%d,", &object.option);
			//ID
			fscanf(fp, "%s", filename);
			fprintf(fp, "\n");
			object.posture.SetQuaternion(q);
			if (isbody == 1)
			{
				object.isShow = (isshow != 0);
				auto it = manager->find(filename);
				if (it != manager->end())
				{
					object.ID = filename;
					object.body.SetModel(&it->second.m);
				}
			}
		}
		fclose(fp);
	}
}


/*
	�t�@�C������X�e�[�W�f�[�^���擾����֐�
*/
template<size_t arr_size>
inline void load_stage_from_file_ex(const std::string& file_pass,
	StageObject(&objects)[arr_size],
	std::vector<ColBox>& ColBoxs,
	std::map<std::string, cStageModel>* manager)
{
	//�t�@�C�����Ȃ��Ȃ烍�[�h���Ȃ�
	if (!checkFileExistence(file_pass))
	{
		return;
	}
	FILE* fp = fopen(file_pass.c_str(), "r");
	static	FLOAT4 q;
	if (fp)
	{
		int   isbody, isshow;
		for (StageObject& object : objects)
		{
			char filename[256] = {};
			//�g�p���Ă��邩�̃t���O
			fscanf(fp, "%d,", &isbody);
			//�\�����Ă��邩�̃t���O
			fscanf(fp, "%d,", &isshow);
			//���W�f�[�^
			fscanf(fp, "%f,", &object.position.x);
			fscanf(fp, "%f,", &object.position.y);
			fscanf(fp, "%f,", &object.position.z);
			//�X�P�[���l�̃f�[�^
			fscanf(fp, "%f,", &object.scales.x);
			fscanf(fp, "%f,", &object.scales.y);
			fscanf(fp, "%f,", &object.scales.z);
			//�N�I�[�^�j�I���̐����f�[�^
			fscanf(fp, "%f,", &q.x);
			fscanf(fp, "%f,", &q.y);
			fscanf(fp, "%f,", &q.z);
			fscanf(fp, "%f,", &q.w);
			//�I�v�V����
			fscanf(fp, "%d,", &object.option);
			//ID
			fscanf(fp, "%s", filename);
			fprintf(fp, "\n");
			object.posture.SetQuaternion(q);
			if (isbody == 1)
			{
				object.isShow = (isshow != 0);
				auto it = manager->find(filename);
				if (it != manager->end())
				{
					object.ID = filename;
					if (object.ID != "ColBox.fbx")
					{
						object.body.SetModel(&it->second.m);
					}
					if (object.ID == "ColBox.fbx")
					{
						switch (object.option)
						{
						case -1:
							ColBoxs.push_back(OBB(object.position, object.scales, object.posture));
							break;
						default:
							ItemBoxs.push_back({ object.position, object.scales,object.posture ,object.option });
							break;
						}
					}
				}
			}
		}
		fclose(fp);
	}
}

using ColBoxs = std::vector<ColBox>;
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


/*
	�X�e�[�W�̃f�[�^
*/
class StageData
{
public:
	static constexpr UINT MaxObjects = 128u;
protected:
	//�X�e�[�W���ɐݒu����I�u�W�F�N�g
	StageObject	objects[StageData::MaxObjects];
	ColBoxs		colBoxs;
	std::string	name;
public:
	StageData() {}
	StageData(const StageData&) {}
	void Load(std::string file_name, std::map<std::string, cStageModel>* manager)
	{
		name = file_name;
		{
			std::string file_pass = "Data\\StageData\\";
			file_pass += file_name;
			file_pass += ".csv";
			load_stage_from_file(file_pass, objects, manager);
		}
		{
			std::string file_pass = "Data\\ColData\\";
			file_pass += file_name;
			file_pass += "_CD.csv";
			LoadColBoxs(file_pass, colBoxs);
		}
	}
	void Load(std::map<std::string, cStageModel>* manager)
	{
		{
			std::string file_pass = "Data\\StageData\\";
			file_pass += name;
			file_pass += ".csv";
			load_stage_from_file(file_pass, objects, manager);
		}
		{
			std::string file_pass = "Data\\ColData\\";
			file_pass += name;
			file_pass += "_CD.csv";
			LoadColBoxs(file_pass, colBoxs);
		}
	}
	StageObject* getObdects()
	{
		return objects;
	}
	const ColBoxs& getColBoxs()const
	{
		return colBoxs;
	}
	void Render()
	{
		ModelRenderBegin();
		for (auto& object : objects)
		{
			object.Render();
		}
		ModelRenderEnd();
	}
};