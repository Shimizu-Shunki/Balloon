// ============================================
// 
// ファイル名: MaterialResources.h
// 概要: MaterialResources.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================

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
	// 風船のマテリアルを取得する
	IMaterial* GetBalloon() const { return m_balloon.get(); }
	// 雲のマテリアルを取得する
	IMaterial* GetCloud() const { return m_cloud.get(); }

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
	// プレイヤー
	std::unique_ptr<IMaterial> m_defaultPBRLit;
	// 風船
	std::unique_ptr<IMaterial> m_balloon;
	// 風船
	std::unique_ptr<IMaterial> m_cloud;
	// UI
	std::unique_ptr<IMaterial> m_defaultUi;

};