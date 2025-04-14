// ============================================
// 
// ファイル名: LeftArm.cpp
// 概要: 左腕オブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Player/Header/LeftArm.h"
#include "Framework/CommonResources.h"
#include "Game/Model3D/Model3D.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/MaterialResources.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親オブジェクト</param>
LeftArm::LeftArm(IObject* parent)
	:
	m_parent(parent),
	m_transform{},
	m_objectId{},
	m_isActive{},
	m_model{}
{
	// Transformを生成
	m_transform = std::make_unique<Transform>();
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="objectID">オブジェクトID</param>
/// <param name="active">アクティブ設定</param>
void LeftArm::Initialize(ObjectID objectID, const bool& active)
{
	// 共有リソース
	CommonResources* commonResources = CommonResources::GetInstance();

	// オブジェクトIDを設定
	m_objectId = objectID;
	// オブジェクトアクティブを設定
	m_isActive = active;
	
	if (m_objectId == IObject::ObjectID::PLAYER_LEFT_ARM)
	{
		// 3Dモデルを準備する
		m_model = std::make_unique<Model3D>();
		m_model->Initialize(commonResources->GetResources()->GetModelResources()->GetPlayerLeftArmModel(),
			commonResources->GetResources()->GetMaterialResources()->GetDefaultPBRLit(), this
		);
	}
	else
	{
		// 3Dモデルを準備する
		m_model = std::make_unique<Model3D>();
		m_model->Initialize(commonResources->GetResources()->GetModelResources()->GetPlayerLeftArmModel(),
			commonResources->GetResources()->GetMaterialResources()->GetEnemy(), this
		);
	}
	

	// 描画マネージャーに渡す
	commonResources->GetRenderManager()->AddModel(m_model.get());

}

/// <summary>
/// Transformを初期化
/// </summary>
/// <param name="position">初期座標</param>
/// <param name="rotation">初期回転</param>
/// <param name="scale">初期スケール</param>
void LeftArm::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	// 位置を初期化
	m_transform->SetLocalPosition(position);
	// 回転角を初期化
	m_transform->SetLocalRotation(rotation);
	// スケールを初期化
	m_transform->SetLocalScale(scale);

	// トランスフォームを親に設定
	m_transform->SetParent(m_parent->GetTransform());
}

/// <summary>
/// 更新処理
/// </summary>
void LeftArm::Update() {}

/// <summary>
/// 終了処理
/// </summary>
void LeftArm::Finalize() {}

/// <summary>
/// メッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
void LeftArm::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}

/// <summary>
/// 当たり判定のメッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
/// <param name="sender">当たった相手のオブジェクト</param>
void LeftArm::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}