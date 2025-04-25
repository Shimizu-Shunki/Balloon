#pragma once
#include <variant>
#include <SimpleMath.h>
#include <string>
#include "Game/Parameters/ParameterKeys.h"

class Parameters
{
public:

	// バリアント
	using ParameterValue = std::variant<float, int, DirectX::SimpleMath::Vector3>;
	using json = nlohmann::json;

	// パラメータを取得 int
	int GetParameter(const ParameterKeysI& key) const;
	// パラメータを取得 float
	float GetParameter(const ParameterKeysF& key) const;
	// パラメータを取得 Vector3
	DirectX::SimpleMath::Vector3 GetParameter(const ParameterKeysV& key) const;

	// デバッグウィンドウ
	void ShowImGuiEditor();
private:

	// ファイルを開く
	std::string OpenFile() const;
	// JSONデータをロード
	void LoadFromJson(const std::string& filepath);
	// データを保存
	std::string SaveFile() const;
	// JSONデータを保存
	void SaveToJson(const std::string& filepath);

private:
	//	コンストラクタ
	Parameters();
	//	デストラクタ
	~Parameters() = default;
public:
	Parameters(const Parameters&) = delete;             // コピー禁止
	Parameters& operator=(const Parameters&) = delete;  // コピー代入禁止
	Parameters(const Parameters&&) = delete;            // ムーブ禁止
	Parameters& operator=(const Parameters&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static Parameters* GetInstance()
	{
		static Parameters instance;
		return &instance;
	}

private:

	// パラメーター
	std::unordered_map<std::string, ParameterValue> m_parameters;
};