// ============================================
// 
// ファイル名: Resources.cpp
// 概要: 各種リソースの管理と読み込みを行うクラス（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Framework/Resources.h"
#include <iostream>
#include <fstream>

#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"
#include "Framework/Resources/MaterialResources.h"

/// <summary>
/// コンストラクタ
/// </summary>
Resources::Resources()
	
{
	// インスタンスを取得する
	m_modelResources    = ModelResources::GetInstance();
	m_shaderResources   = ShaderResources::GetInstance();
	m_textureResources  = TextureResources::GetInstance();
	m_materialResources = MaterialResources::GetInstance();
}


/// <summary>
/// 各リソースのロード
/// </summary>
void Resources::LoadResource()
{
	// JSONファイルを開く
	std::ifstream file("Resources/Json/GameResourceData.json");
	assert(file);
	// JSON をロード
	nlohmann::json data;
	file >> data; 

	// モデルをロードする
	m_modelResources->LoadResource(data);
	// シェーダーをロードする
	m_shaderResources->LoadResource(data);
	// テクスチャをロードする
	m_textureResources->LoadResource(data);

	m_materialResources->Initialize(this);
}
