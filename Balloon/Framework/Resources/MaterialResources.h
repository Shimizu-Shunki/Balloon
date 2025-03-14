#pragma once
#include "Interface/IMaterial.h"

class PBRLit;
class IMaterial;
class Resources;

class MaterialResources
{
public:
	// デフォルトのPBRLitマテリアルを取得する
	IMaterial* GetDefaultPBRLit() const { return m_defaultPBRLit.get(); }

public:
	MaterialResources(const MaterialResources&) = delete;             // コピー禁止
	MaterialResources& operator=(const MaterialResources&) = delete;  // コピー代入禁止
	MaterialResources(const MaterialResources&&) = delete;            // ムーブ禁止
	MaterialResources& operator=(const MaterialResources&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static MaterialResources* GetInstance()
	{
		static MaterialResources instance;
		return &instance;
	}
private:
	// コンストラクタ
	MaterialResources();

public:
	// 初期化処理
	void Initialize(Resources* resources);

private:
	// デフォルトPBRLit
	std::unique_ptr<IMaterial> m_defaultPBRLit;
	// UI
	std::unique_ptr<IMaterial> m_defaultUi;

};