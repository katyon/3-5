#include "CollisionEditer.h"

bool getFileNames(std::string folderPath, std::vector<std::string>& file_names);

void CollisionEditer::load_object()
{
	std::vector<std::string> load_files;
	//	Data\\Objects�t�H���_���ɂ���S�Ẵt�@�C�����擾
	if (getFileNames("Data\\Objects", load_files))
	{
		for (auto& file_pass : load_files)
		{
			static std::vector<std::string> fo;
			fo.clear();
			fo = Split(file_pass, '.');
			std::string f = fo.at(fo.size() - 1u);
			std::transform(f.begin(), f.end(), f.begin(), tolower);
			//���f���t�@�C���ȊO�͖���
			if (f != "obj" && f != "fbx")continue;
			//���d���[�h�΍�
			auto it = manager.find(file_pass.substr(strlen("Data\\Objects\\")));
			if (it == manager.end())
			{
				manager.insert(std::make_pair(file_pass.substr(strlen("Data\\Objects\\")), file_pass));
			}
		}
	}
}






CollisionEditer::CollisionEditer()
{
	load_object();
	ambient->option.x = 0.5f;
	{
		std::string pass = "Data\\ColData\\When_finished.csv";
		stage.Load(pass, &manager);

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
			fscanf(fp, "%d,", &data_size);
			char filename[256] = {};
			fscanf(fp, "%s,", filename);
			if (filename[0] != '\0')
			{
				storage = filename;
				std::string pass = "Data\\StageData\\";
				pass += storage;
				pass += ".csv";
				stage.Load(pass, &manager);
			}
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


CollisionEditer::~CollisionEditer()
{
	std::string pass = "Data\\ColData\\When_finished.csv";
	//�t�@�C���|�C���^���擾
	FILE* fp = fopen(pass.c_str(), "w");
	if (fp)
	{
		//�f�[�^����ۑ�
		fprintf(fp, "%d,%s\n",
			static_cast<int>(ColDataList.size()),
			storage.empty() ? "empty" : storage.c_str());
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
}


void CollisionEditer::GUI()
{
	if (isShow)
	{
		ImGui::Begin(u8"������@", &isShow);
		ImGui::TextColored({ 1,0,0,1 }, u8"���J�����̑�����@");
		ImGui::Text(u8"�E�N���b�N������ԂŁyW�z�yA�z�yS�z�yD�z�yE�z�yQ�z�ňړ��B");
		ImGui::Text(u8"���N���b�N������ԂŁyW�z�yA�z�yS�z�yD�z�Ŏ����ړ��B");
		ImGui::TextColored({ 0,1,0,1 }, u8"���G�f�B�^�[�̑�����@");
		ImGui::Text(u8"��ɃX�e�[�W�G�f�B�^�[�ō쐬�����X�e�[�W�f�[�^���f�[�^�t�H���_��StageData�t�H���_�ɓ���Ă���,");
		ImGui::Text(u8"�u�f�[�^�����[�h����v�{�^���������A�X�e�[�W�f�[�^�ƃR���W�����f�[�^�̃��[�h���s���B");
		ImGui::Text(u8"�p�����[�^��ImGui�ŕύX�ł���B");
		ImGui::Text(u8"�u�f�[�^���Z�[�u����v�{�^����������CTRL+S�ŕۑ��ł���B");
		ImGui::End();
	}
	ImGui::Begin(u8"�Ȃ񂩂��낢��");
	ImGui::Spacing();
	ImGui::InputText(u8"�X�e�[�W�̖��O", stage_name, 256);

	if (ImGui::Button(u8"�f�[�^�����[�h����"))
	{
		this->storage = stage_name;
		LoadColBoxs();
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"�f�[�^���Z�[�u����"))
	{
		if (storage.empty())return;
		SaveColBoxs();
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"�f�[�^���N���A����")) { ColDataList.clear(); }

	if (ImGui::Button(u8"OBB��ǉ�����"))
	{
		CBD box;
		box.d.obb.pos = {};
		box.d.obb.len = ScalarToFloat3(1.0f);
		box.d.obb.setVector(Quaternion());
		box.d.option = -1;
		box.q = Quaternion();
		ColDataList.emplace_back(box);
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"�J���������Z�b�g"))
	{
		camera.SetPos({ 0.0f, 5.0f, -25.0f });
		camera.SetTarget({});
		camera_q.reset();
	}
	ImGui::SameLine();
	if (ImGui::Button(isShow ? u8"������@���\��" : u8"������@��\��"))
	{
		isShow = !isShow;
	}
	storage.empty() ? ImGui::NewLine() :
		ImGui::Text(u8"%s��ҏW��", storage.c_str());
	ImGui::InputFloat(u8"�J�����̈ړ����x", &speed, 1.0f, -1.0f);

	ImGui::End();

	ImGui::Begin(u8"�p�����[�^");
	int index = 0;
	for (auto& it = ColDataList.begin(); it != ColDataList.end(); index++)
	{
		std::string label = "OBB[" + std::to_string(index) + "]";
		if (ImGui::TreeNode(label.c_str()))//TreeNode
		{
			if (ImGui::Button(u8"�폜"))
			{
				it = ColDataList.erase(it);
				ImGui::TreePop();
				continue;
			}

			ImGui::InputInt(u8"�I�v�V����", &it->d.option, 1, -1);


			ImGui::Text(u8"���W");
			ImGui::InputFloat(u8"���W::X", &it->d.obb.pos.x, 0.5f, -0.5f);
			ImGui::InputFloat(u8"���W::Y", &it->d.obb.pos.y, 0.5f, -0.5f);
			ImGui::InputFloat(u8"���W::Z", &it->d.obb.pos.z, 0.5f, -0.5f);

			ImGui::Text(u8"�ӂ̒���");
			ImGui::InputFloat(u8"�ӂ̒���::X", &it->d.obb.len.x, 0.01f, -0.01f);
			ImGui::InputFloat(u8"�ӂ̒���::Y", &it->d.obb.len.y, 0.01f, -0.01f);
			ImGui::InputFloat(u8"�ӂ̒���::Z", &it->d.obb.len.z, 0.01f, -0.01f);

			ImGui::Text(u8"�p��");
			{
				if (ImGui::Button("X - 30��")) { it->q.RotationPitch(n30); }
				ImGui::SameLine();
				if (ImGui::Button("X - 15��")) { it->q.RotationPitch(n15); }
				ImGui::SameLine();
				if (ImGui::Button("X - 1��")) { it->q.RotationPitch(-OnceInRadians); }
				ImGui::SameLine();
				if (ImGui::Button("X + 1��")) { it->q.RotationPitch(OnceInRadians); }
				ImGui::SameLine();
				if (ImGui::Button("X + 15��")) { it->q.RotationPitch(p15); }
				ImGui::SameLine();
				if (ImGui::Button("X + 30��")) { it->q.RotationPitch(p30); }
			}
			{
				if (ImGui::Button("Y - 30��")) { it->q.RotationYaw(n30); }
				ImGui::SameLine();
				if (ImGui::Button("Y - 15��")) { it->q.RotationYaw(n15); }
				ImGui::SameLine();
				if (ImGui::Button("Y - 1��")) { it->q.RotationYaw(-OnceInRadians); }
				ImGui::SameLine();
				if (ImGui::Button("Y + 1��")) { it->q.RotationYaw(OnceInRadians); }
				ImGui::SameLine();
				if (ImGui::Button("Y + 15��")) { it->q.RotationYaw(p15); }
				ImGui::SameLine();
				if (ImGui::Button("Y + 30��")) { it->q.RotationYaw(p30); }
			}
			{
				if (ImGui::Button("Z - 30��")) { it->q.RotationRoll(n30); }
				ImGui::SameLine();
				if (ImGui::Button("Z - 15��")) { it->q.RotationRoll(n15); }
				ImGui::SameLine();
				if (ImGui::Button("Z - 1��")) { it->q.RotationRoll(-OnceInRadians); }
				ImGui::SameLine();
				if (ImGui::Button("Z + 1��")) { it->q.RotationRoll(OnceInRadians); }
				ImGui::SameLine();
				if (ImGui::Button("Z + 15��")) { it->q.RotationRoll(p15); }
				ImGui::SameLine();
				if (ImGui::Button("Z + 30��")) { it->q.RotationRoll(p30); }
			}

			ImGui::TreePop();
		}
		++it;
	}
	ImGui::End();
}

void CollisionEditer::update()
{
	GUI();
	camera.Control(camera_q, speed * DeltaTime(), OnceInRadians * 0.5f);
	if ((input::TRG('S') && input::STATE(input::CTRL)) ||
		(input::STATE('S') && input::TRG(input::CTRL)))
	{
		if (storage.empty())return;
		SaveColBoxs();
	}
}

void CollisionEditer::render()
{
	camera.Active();
	ambient.Active();
	stage.Render();
	DirectX::XMMATRIX w;
	Geometric::Begin();
	for (const auto& d : ColDataList)
	{
		w = GetWorldMatrix(d.d.obb.pos, d.d.obb.len, d.q);
		Geometric::Cube(w, { DCOLOR_YELLOW }, true);
	}
	Geometric::End();
}
