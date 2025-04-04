#include "Framework/pch.h"
#include "Game/Player/Header/RightFoot.h"
#include "Framework/CommonResources.h"
#include "Game/Model3D/Model3D.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/MaterialResources.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親オブジェクト</param>
RightFoot::RightFoot(IObject* parent)
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
/// <param name="active"></param>
void RightFoot::Initialize(ObjectID objectID, const bool& active)
{
	// 共有リソース
	CommonResources* commonResources = CommonResources::GetInstance();

	// オブジェクトIDを設定
	m_objectId = objectID;
	// オブジェクトアクティブを設定
	m_isActive = active;
	// 3Dモデルを準備する
	m_model = std::make_unique<Model3D>();
	m_model->Initialize(commonResources->GetResources()->GetModelResources()->GetPlayerRightFootModel(),
		commonResources->GetResources()->GetMaterialResources()->GetDefaultPBRLit(), this
	);

	// 描画マネージャーに渡す
	commonResources->GetRenderManager()->AddModel(m_model.get());

}

/// <summary>
/// Transformを初期化
/// </summary>
/// <param name="position">初期座標</param>
/// <param name="rotation">初期回転</param>
/// <param name="scale">初期スケール</param>
void RightFoot::InitialTransform(
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
void RightFoot::Update() {}

/// <summary>
/// 終了処理
/// </summary>
void RightFoot::Finalize() {}


void RightFoot::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}

void RightFoot::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}