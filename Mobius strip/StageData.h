#pragma once
#define	_CRT_SECURE_NO_WARNINGS
#include <iosfwd>
#include "AliceLib/AliceLib.h"


/*
	ステージ内にあるオブジェクトのデータ構造体
*/
struct StageObject
{
	//モデルのファイルアドレスが入る
	//このIDを使いモデルを取得する
	std::string		ID;
	//モデルを設置する座標
	FLOAT3			position;
	//モデルのスケール
	FLOAT3			scales;
	//モデル姿勢
	Quaternion		posture;
	//描画するかのフラグ
	bool			isShow = true;
	//モデルの複製品
	ModelReplica	body;
	//オプション　アイテムで使う
	//デフォルト値 -1
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
	ステージ内に設置するモデル
	をカプセルしたクラス
*/
typedef struct cStageModel final
{
	Model m;
	cStageModel(std::string file_pass)
	{
		//全てのモデルはMayaで作られているていで設定
		ModelLoad(m, file_pass.c_str(), MAYA);
	}
}SE_Model;


/*
	ファイルが存在するかテストする関数
*/
inline bool checkFileExistence(const std::string& str)
{
	std::ifstream ifs(str);
	return ifs.is_open();
}


/*
	ファイルからステージデータを取得する関数
*/
template<size_t arr_size>
inline void load_stage_from_file(const std::string& file_pass,
	StageObject(&objects)[arr_size], std::map<std::string, cStageModel>* manager)
{
	//ファイルがないならロードしない
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
			//オプション
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
	ファイルからステージデータを取得する関数
*/
template<size_t arr_size>
inline void load_stage_from_file_ex(const std::string& file_pass,
	StageObject(&objects)[arr_size],
	std::vector<ColBox>& ColBoxs,
	std::map<std::string, cStageModel>* manager)
{
	//ファイルがないならロードしない
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
			//オプション
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
	//ファイルが無ければ終了
	if (!checkFileExistence(file_pass))return;
	//ファイルポインタを取得
	FILE* fp = fopen(file_pass.c_str(), "r");
	if (fp)
	{
		//データを空にしておく
		data.clear();
		int data_size = 0;
		//データ数を取得
		fscanf(fp, "%d", &data_size);
		fprintf(fp, "\n");
		//データが0に満たない場合終了
		if (data_size <= 0)
		{
			fclose(fp);
			return;
		}
		FLOAT4 _Qu;
		Quaternion Qu;
		//データ数分だけコンテナを作成する
		data.resize(static_cast<size_t>(data_size));
		//データ数ループする
		for (auto& d : data)
		{
			//座標データ
			fscanf(fp, "%f,", &d.obb.pos.x);
			fscanf(fp, "%f,", &d.obb.pos.y);
			fscanf(fp, "%f,", &d.obb.pos.z);

			//スケール値のデータ
			fscanf(fp, "%f,", &d.obb.len.x);
			fscanf(fp, "%f,", &d.obb.len.y);
			fscanf(fp, "%f,", &d.obb.len.z);

			//姿勢データを取得
			fscanf(fp, "%f,", &_Qu.x);
			fscanf(fp, "%f,", &_Qu.y);
			fscanf(fp, "%f,", &_Qu.z);
			fscanf(fp, "%f,", &_Qu.w);

			Qu.SetQuaternion(_Qu);
			d.obb.setVector(Qu);

			//オプション(判定用のオプション)
			fscanf(fp, "%d,", &d.option);

			fprintf(fp, "\n");
		}
		fclose(fp);
	}
}


/*
	ステージのデータ
*/
class StageData
{
public:
	static constexpr UINT MaxObjects = 128u;
protected:
	//ステージ内に設置するオブジェクト
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