// ============================================
// 
// ファイル名: Model3D.cpp
// 概要: 3Dモデルを管理するクラス
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Model3D/Model3D.h"
#include "Interface/IMaterial.h"
#include "Interface/IObject.h"

/// <summary>
/// コンストラクタ
/// </summary>
Model3D::Model3D()
	:
	m_model{},
	m_material{},
	m_object{},
	m_isShadow{}
{
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="model">モデル</param>
/// <param name="material">マテリアル</param>
/// <param name="object">対象のオブジェクト</param>
/// <param name="isShadow">シャドウ有効にするか</param>
void Model3D::Initialize(DirectX::Model* model, IMaterial* material, IObject* object, bool isShadow)
{
	m_model    = model;
	m_material = material;
	m_object   = object;
	m_isShadow = isShadow;
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="context">コンテキスト</param>
/// <param name="states">コモンステート</param>
/// <param name="viewMatrix">ビュー行列</param>
/// <param name="projectionMatrix">射影行列</param>
/// <param name="lightBuffer">ライトのバッファ</param>
void Model3D::Render(ID3D11DeviceContext1* context, DirectX::CommonStates* states,
	DirectX::SimpleMath::Matrix viewMatrix, DirectX::SimpleMath::Matrix projectionMatrix,
	ID3D11Buffer* lightBuffer
)
{
	// ワールド行列を取得する
	DirectX::SimpleMath::Matrix world = m_object->GetTransform()->GetWorldMatrix();

	// モデル描画
	m_model->Draw(context, *states, world, viewMatrix, projectionMatrix, false, [&]
		{
			// 定数バッファを指定する
			ID3D11Buffer* cbuf[] = { lightBuffer };
			context->VSSetConstantBuffers(1, 1, cbuf);
			context->PSSetConstantBuffers(1, 1, cbuf);

			// ブレンドステートを設定 (半透明描画用)
			context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xFFFFFFFF);

			m_material->BeginMaterial();
		});
}