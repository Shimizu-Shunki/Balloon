// ============================================
// 
// ファイル名: Model3D.h
// 概要: Model3D.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include <Model.h>

class IMaterial;
class IObject;

class Model3D
{
public:
	// モデルを取得する
	DirectX::Model* GetModel() const { return m_model; }
	// オブジェクトを取得する
	IObject* GetObject() const { return m_object; }
	// 影を描画するか
	bool GetIsShadow() const { return m_isShadow; }
	// マテリアルを取得する
	IMaterial* GetMaterial() { return m_material; }

public:
	// コンストラクタ
	Model3D();
	// デストラクタ
	~Model3D() = default;

public:
	// 初期化
	void Initialize(DirectX::Model* model , IMaterial* material , IObject* object , bool isShadow = true);
	// 描画処理
	void Render(ID3D11DeviceContext1* context , DirectX::CommonStates* states ,
		DirectX::SimpleMath::Matrix viewMatrix , DirectX::SimpleMath::Matrix projectionMatrix,
		ID3D11Buffer* lightBuffer
		);

private:
	// モデル
	DirectX::Model* m_model;
	// マテリアル
	IMaterial* m_material;
	// オブジェクト
	IObject* m_object;

	// 影
	bool m_isShadow;
};