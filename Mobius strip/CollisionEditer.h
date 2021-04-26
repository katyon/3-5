#pragma once
#include "StageData.h"



inline void LoadColBoxs(const std::string& file_pass, 
	std::vector<ColBox>& data)
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
		//データ数分だけコンテナを作成する
		data.resize(static_cast<size_t>(data_size));
		//データ数ループする
		for (auto& d: data)
		{
			//座標データ
			fscanf(fp, "%f,", &d.obb.pos.x);
			fscanf(fp, "%f,", &d.obb.pos.y);
			fscanf(fp, "%f,", &d.obb.pos.z);

			//スケール値のデータ
			fscanf(fp, "%f,", &d.obb.len.x);
			fscanf(fp, "%f,", &d.obb.len.y);
			fscanf(fp, "%f,", &d.obb.len.z);

			//方向ベクトルの成分データ
			//Right
			fscanf(fp, "%f,", &d.obb.direct.right.x);
			fscanf(fp, "%f,", &d.obb.direct.right.y);
			fscanf(fp, "%f,", &d.obb.direct.right.z);
			//Up
			fscanf(fp, "%f,", &d.obb.direct.up.x);
			fscanf(fp, "%f,", &d.obb.direct.up.y);
			fscanf(fp, "%f,", &d.obb.direct.up.z);
			//Forward
			fscanf(fp, "%f,", &d.obb.direct.forward.x);
			fscanf(fp, "%f,", &d.obb.direct.forward.y);
			fscanf(fp, "%f,", &d.obb.direct.forward.z);

			//オプション(判定用のオプション)
			fscanf(fp, "%d,", &d.option);

			fprintf(fp, "\n");
		}
		fclose(fp);
	}
}

inline void SaveColBoxs(const std::string& stage_name,
	const std::vector<ColBox>& data)
{
	//if (std::string("When_finished") == stage_name)
	//{
	//	MessageBoxW(nullptr, L"別の名前で保存してください", L"この名前は使用できません", MB_OK);
	//	return;
	//}
	std::string pass = "Data\\StageData\\";
	pass += stage_name;
	pass += "_CD.csv";
	if (checkFileExistence(pass))
	{
		int result = MessageBoxW(nullptr, L"上書きして保存しますか？",
			L"ファイルが既に存在します", MB_YESNO);
		if (result != IDYES)return;
	
	}
	FILE* fp = fopen(pass.c_str(), "w");
	if (fp)
	{
		//データ数を保存
		fprintf(fp, "%d \n",static_cast<int>(data.size()) );
		for (const auto& d: data)
		{
			fprintf(fp,
				"%f,%f,%f,\
				%f,%f,%f,\
				%f,%f,%f,\
				%f,%f,%f,\
				%f,%f,%f,\
				%d\n",
				d.obb.pos.x, d.obb.pos.y, d.obb.pos.z,
				d.obb.len.x, d.obb.len.y, d.obb.len.z,
				d.obb.direct.right.x, d.obb.direct.right.y, d.obb.direct.right.z,
				d.obb.direct.up.x, d.obb.direct.up.y, d.obb.direct.up.z,
				d.obb.direct.forward.x, d.obb.direct.forward.y, d.obb.direct.forward.z,
				d.option);
		}
		fclose(fp);
	}
}

class CollisionEditer
{
private:

public:
};

