// ============================================
// 
// ファイル名: StageResources.h
// 概要: StageResources.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

class StageResources
{
public:
	struct StageData
	{
		int score;
		int time;
	};
public:
	// ステージデータを取得する
	StageData GetStageData(int number) { return m_stageData[number]; }
	// ステージデータを設定する
	void SetStageData(int number, StageData stageData) { m_stageData[number] = stageData; }

public:
	StageResources(const StageResources&) = delete;             // コピー禁止
	StageResources& operator=(const StageResources&) = delete;  // コピー代入禁止
	StageResources(const StageResources&&) = delete;            // ムーブ禁止
	StageResources& operator=(const StageResources&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static StageResources* GetInstance()
	{
		static StageResources instance;
		return &instance;
	}

private:
	// コンストラクタ
	StageResources();
	// デストラクタ
	~StageResources() = default;

public:
	// リソースをロードする
	void LoadResource(const nlohmann::json& data);

private:

	// ステージデータ
	std::unordered_map<int, StageData> m_stageData;

};