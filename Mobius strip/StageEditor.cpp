#define	_CRT_SECURE_NO_WARNINGS

#include "StageEditor.h"
//#include "AliceLib/AddOn.h"
#include <stdlib.h>
#include <fstream>
#include <filesystem>

bool getFileNames(std::string folderPath, std::vector<std::string> &file_names)
{
	using namespace std::filesystem;
	directory_iterator iter(folderPath), end;
	std::error_code err;

	for (; iter != end && !err; iter.increment(err)) 
	{
		const directory_entry entry = *iter;
		file_names.push_back(entry.path().string());
	}

	if (err) 
	{	
		return false;
	}
	return true;
}

void StageEditor::load_object()
{
#if false
	std::wstring	output_pilepass;
	if (Function::OpenExplorerToGetTheFilePass(output_pilepass, nullptr, nullptr,
		L"Modelファイル(*.OBJ *.FBX)\0*.OBJ;*.FBX\0"))
	{
		std::string file_pass;
		ToString(output_pilepass, file_pass);
		auto it = manager.find(file_pass);
		if (it == manager.end()) { manager.insert(std::make_pair(file_pass, file_pass)); }
	}
#else
	std::vector<std::string> load_files;
	//	Data\\Objectsフォルダ内にある全てのファイルを取得
	if (getFileNames("Data\\Objects",load_files))
	{
		for (auto& file_pass : load_files)
		{
			static std::vector<std::string> fo;
			fo.clear();
			fo = Split(file_pass, '.');
			std::string f = fo.at(fo.size() - 1u);
			std::transform(f.begin(), f.end(), f.begin(), tolower);
			//モデルファイル以外は無視
			if (f != "obj"&& f != "fbx")continue;
			//多重ロード対策
			auto it = manager.find(file_pass.substr(strlen("Data\\Objects\\")));
			if (it == manager.end()) 
			{
				manager.insert(std::make_pair(file_pass.substr(strlen("Data\\Objects\\")), file_pass)); 
			}
		}
	}
#endif // false
}

void StageEditor::load_stage()
{
	std::string pass = "Data\\StageData\\";
	pass += stage_name;
	pass += ".csv";
	//ファイルがないならロードしない
	if (!checkFileExistence(pass))
	{
		int result = MessageBoxW(nullptr, L"ファイルのパスを確認してください", L"ファイルが存在しません", MB_OK);
		return;
	}
	load_object();
	clear_stage();
	load_stage_from_file(pass, objects,&manager);
	MessageBoxW(nullptr, L"ロードが完了しました", L"Load", MB_OK);
}

void StageEditor::clear_stage()
{
	for (auto& object : objects) { object.Clear(); }
}

void StageEditor::save()
{
	if (std::string("When_finished") == stage_name)
	{
		MessageBoxW(nullptr, L"別の名前で保存してください", L"この名前は使用できません", MB_OK);
		return;
	}
	std::string pass = "Data\\StageData\\"; 
	pass += stage_name;
	pass += ".csv";
	if (checkFileExistence(pass))
	{
		int result = MessageBoxW(nullptr, L"上書きして保存しますか？", L"ファイルが既に存在します", MB_YESNO);
		if (result != IDYES)return;
		
	}
	FILE* fp = fopen(pass.c_str(), "w");
	static	FLOAT4 q;
	if(fp)
	{
		//軽く整列する
		for (auto& object : objects)
		{
			if (!object.body)continue;
			q = object.posture.GetQuaternion();
			fprintf(fp, "%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%s \n",
				object.body ? 1 : 0,
				object.isShow ? 1 : 0,
				object.position.x, object.position.y, object.position.z,
				object.scales.x, object.scales.y, object.scales.z,
				q.x, q.y, q.z, q.w,
				object.option,
				object.ID.c_str());
		}
		for (auto& object : objects)
		{
			if (object.body)continue;

			fprintf(fp, "%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%s \n",
				0,
				1,
				0.0f, 0.0f, 0.0f,
				1.0f, 1.0f, 1.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
				-1,
				"empty");
		}
		fclose(fp);
		MessageBoxW(nullptr, L"セーブが完了しました", L"Save", MB_OK);
	}
}

void StageEditor::Update()
{
	int index = 0;
	ImGui::Begin("EditorControl");
	if (ImGui::Button("Import Objects"))	{ StageEditor::load_object(); }
	ImGui::SameLine();
	{
		if (ImGui::Button("Camera Reset"))
		{
			camera.SetPos({ 0.0f, 5.0f, -25.0f });
			camera.SetTarget({ 0.0f, 0.0f, 0.0f });
		}
	}
	ImGui::SameLine();
	ImGui::Checkbox("Show Vectors",&showV);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::InputText("Name to Stage", stage_name, 256);

	if (ImGui::Button("Load Stage"))	{ StageEditor::load_stage(); }
	ImGui::SameLine();
	if (ImGui::Button("Save Stage"))	{ StageEditor::save(); }
	ImGui::SameLine();
	if (ImGui::Button("Clear Stage")) { StageEditor::clear_stage(); }
	ImGui::NewLine();

	for (auto& m : manager)
	{
		if (ImGui::Button(m.first.c_str()))
		{
			for (auto& object : objects)
			{
				if (object.body == false)
				{
					StageObject data;
					data.ID = m.first;
					data.position = {};
					data.scales = { 1.0f,1.0f,1.0f };
					data.posture.reset();
					data.isShow = true;
					data.option = -1;
					object.Load(&m.second.m,data);
					break;
				}
			}
		}
	}

	ImGui::End();
	ImGui::Begin("ObjectsParameter");
	//ImGui::SetNextTreeNodeOpen(false, ImGuiSetCond_Once);
	for (auto& object : objects)
	{
		if (object.body == false)
		{
			index++;continue;
		}
		std::string label = "object[" + std::to_string(index) + "]";
		if (ImGui::TreeNode(label.c_str()))//TreeNode
		{
			ImGui::Text(("ID :: " + object.ID).c_str());
			ImGui::Checkbox("isShow",&object.isShow);
			ImGui::SameLine();
			
			if (ImGui::Button("Delete"))
			{
				object.Clear();
			}

			ImGui::InputInt("Option", &object.option, 1, -1);

			//オブジェクトが表示されている場合のみ編集可能
			if (object.isShow)
			{
				ImGui::Text("postition");
				ImGui::InputFloat("postition::X", &object.position.x, 0.5f, -0.5f);
				ImGui::InputFloat("postition::Y", &object.position.y, 0.5f, -0.5f);
				ImGui::InputFloat("postition::Z", &object.position.z, 0.5f, -0.5f);

				ImGui::Text("scales");
				ImGui::InputFloat("scale::X", &object.scales.x, 0.01f, -0.01f);
				ImGui::InputFloat("scale::Y", &object.scales.y, 0.01f, -0.01f);
				ImGui::InputFloat("scale::Z", &object.scales.z, 0.01f, -0.01f);

				ImGui::Text("posture");
				{
					//if (ImGui::Button("X - 180°")) { object.posture.RotationPitch(n180); }
					//ImGui::SameLine();
					//if (ImGui::Button("X - 90°")) { object.posture.RotationPitch(n90); }
					//ImGui::SameLine();
					if (ImGui::Button("X - 30°")) { object.posture.RotationPitch(n30); }
					ImGui::SameLine();
					if (ImGui::Button("X - 15°")) { object.posture.RotationPitch(n15); }
					ImGui::SameLine();
					if (ImGui::Button("X - 1°")) { object.posture.RotationPitch(-OnceInRadians); }
					ImGui::SameLine();
					if (ImGui::Button("X + 1°")) { object.posture.RotationPitch(OnceInRadians); }
					ImGui::SameLine();
					if (ImGui::Button("X + 15°")) { object.posture.RotationPitch(p15); }
					ImGui::SameLine();
					if (ImGui::Button("X + 30°")) { object.posture.RotationPitch(p30); }
					//ImGui::SameLine();
					//if (ImGui::Button("X + 90°")) { object.posture.RotationPitch(p90); }
					//ImGui::SameLine();
					//if (ImGui::Button("X + 180°")) { object.posture.RotationPitch(p180); }
				}
				{
					//if (ImGui::Button("Y - 180°")) { object.posture.RotationYaw(n180); }
					//ImGui::SameLine();
					//if (ImGui::Button("Y - 90°")) { object.posture.RotationYaw(n90); }
					//ImGui::SameLine();
					if (ImGui::Button("Y - 30°")) { object.posture.RotationYaw(n30); }
					ImGui::SameLine();
					if (ImGui::Button("Y - 15°")) { object.posture.RotationYaw(n15); }
					ImGui::SameLine();
					if (ImGui::Button("Y - 1°")) { object.posture.RotationYaw(-OnceInRadians); }
					ImGui::SameLine();
					if (ImGui::Button("Y + 1°")) { object.posture.RotationYaw(OnceInRadians); }
					ImGui::SameLine();
					if (ImGui::Button("Y + 15°")) { object.posture.RotationYaw(p15); }
					ImGui::SameLine();
					if (ImGui::Button("Y + 30°")) { object.posture.RotationYaw(p30); }
					//ImGui::SameLine();
					//if (ImGui::Button("Y + 90°")) { object.posture.RotationYaw(p90); }
					//ImGui::SameLine();
					//if (ImGui::Button("Y + 180°")) { object.posture.RotationYaw(p180); }
				}
				{
					//if (ImGui::Button("Z - 180°")) { object.posture.RotationPitch(n180); }
					//ImGui::SameLine();
					//if (ImGui::Button("Z - 90°")) { object.posture.RotationPitch(n90); }
					//ImGui::SameLine();
					if (ImGui::Button("Z - 30°")) { object.posture.RotationRoll(n30); }
					ImGui::SameLine();
					if (ImGui::Button("Z - 15°")) { object.posture.RotationRoll(n15); }
					ImGui::SameLine();
					if (ImGui::Button("Z - 1°")) { object.posture.RotationRoll(-OnceInRadians); }
					ImGui::SameLine();
					if (ImGui::Button("Z + 1°")) { object.posture.RotationRoll(OnceInRadians); }
					ImGui::SameLine();
					if (ImGui::Button("Z + 15°")) { object.posture.RotationRoll(p15); }
					ImGui::SameLine();
					if (ImGui::Button("Z + 30°")) { object.posture.RotationRoll(p30); }
					//ImGui::SameLine();
					//if (ImGui::Button("Z + 90°")) { object.posture.RotationPitch(p90); }
					//ImGui::SameLine();
					//if (ImGui::Button("Z + 180°")) { object.posture.RotationPitch(p180); }
				}
			}
			ImGui::TreePop();
		}
		index++;
	}
	ImGui::End();
	camera.Control();
}

void StageEditor::Render()
{
	//シェーダに定数バッファを転送
	camera.Active();
	//ambient->direction = camera.LightFloamCamera();
	ambient.Active();

	if (showV)
	{
		Geometric::Vector(camera, {}, {100.0f,0.0f,0.0f}, {0.3f}, { 0,0,0,1.0f }, { DCOLOR_RED });
		Geometric::Vector(camera, {}, {0.0f,0.0f,100.0f}, {0.3f }, { 0,0,0,1.0f }, { DCOLOR_BLUE });
		Geometric::Vector(camera, {}, {0.0f,100.f,0.0f} , {0.3f}, { 0,0,0,1.0f }, { DCOLOR_GREEN });
	}
	Geometric::Board(camera, {}, ScalarToFloat3(200.0f), {}, { 0,0,0,1.0f }, { 1.0f, 1.0f, 1.0f, 0.3f });

	ModelRenderBegin();
	for (auto& object : objects)
	{
		object.Render();
	}
	ModelRenderEnd();

}

StageEditor::StageEditor()
{
	ambient->option.x = 0.5f;
	std::string pass = "Data\\StageData\\When_finished.csv";
	//ファイルがないならロードしない
	if (checkFileExistence(pass))
	{
		FILE* fp = fopen(pass.c_str(), "r");
		static	FLOAT4 q;
		if (fp)
		{
			//念のためオブジェクトをロードしなおす
			load_object();
			int   isbody, isshow;
			for (auto& object : objects)
			{
				char filename[256] = {};
				//使用しているかのフラグ
				fscanf(fp, "%d,", &isbody);
				//表示しているかのフラグ
				fscanf(fp, "%d,", &isshow);
				//座標データ
				fscanf(fp, "%f,", &object.position.x);
				fscanf(fp, "%f,", &object.position.y);
				fscanf(fp, "%f,", &object.position.z);
				//スケール値のデータ
				fscanf(fp, "%f,", &object.scales.x);
				fscanf(fp, "%f,", &object.scales.y);
				fscanf(fp, "%f,", &object.scales.z);
				//クオータニオンの成分データ
				fscanf(fp, "%f,", &q.x);
				fscanf(fp, "%f,", &q.y);
				fscanf(fp, "%f,", &q.z);
				fscanf(fp, "%f,", &q.w);

				fscanf(fp, "%d,", &object.option);
				//ID
				fscanf(fp, "%s", filename);
				fprintf(fp, "\n");
				object.posture.SetQuaternion(q);
				if (isbody == 1)
				{
					object.isShow = (isshow != 0);
					auto it = manager.find(filename);
					if (it != manager.end())
					{
						object.ID = filename;
						object.body.SetModel(&it->second.m);
					}
				}
			}
			fclose(fp);
		}
	}
}

StageEditor::~StageEditor()
{
	//終了時用のファイルに保存
	std::string pass = "Data\\StageData\\When_finished.csv";
	FILE* fp = fopen(pass.c_str(), "w");
	static	FLOAT4 q;
	if (fp)
	{
		//軽く整列する
		for (auto& object : objects)
		{
			if (!object.body)continue;
			q = object.posture.GetQuaternion();
			fprintf(fp, "%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%s \n",
				object.body ? 1 : 0,
				object.isShow ? 1 : 0,
				object.position.x, object.position.y, object.position.z,
				object.scales.x, object.scales.y, object.scales.z,
				q.x, q.y, q.z, q.w,
				object.option,
				object.ID.c_str());
		}
		for (auto& object : objects)
		{
			if (object.body)continue;

			fprintf(fp, "%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%s \n",
				0,
				1,
				0.0f, 0.0f, 0.0f,
				1.0f, 1.0f, 1.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
				-1,
				"empty");
		}
		fclose(fp);
	}
}