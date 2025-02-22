#include "Framework/pch.h"
#include "Game/Player/Header/Head.h"
#include "Framework/CommonResources.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親オブジェクト</param>
Head::Head(IObject* parent)
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
void Head::Initialize(ObjectID objectID, const bool& active)
{
	// 共有リソース
	CommonResources* commonResources = CommonResources::GetInstance();

	// オブジェクトIDを設定
	m_objectId = objectID;
	// オブジェクトアクティブを設定
	m_isActive = active;

	// モデルを取得
	// プレイヤーモデル
	if (objectID == ObjectID::PLAYER_HEAD)
		m_model = commonResources->GetResources()->GetPlayerHeadModel();
	// 敵モデル
	else
		m_model = commonResources->GetResources()->GetEnemyHeadModel();


	// 描画管理クラスにTransformとモデルを設定
	commonResources->GetRenderManager()->AddModel({
		this,
		m_model
	});
}

/// <summary>
/// Transformを初期化
/// </summary>
/// <param name="position">初期座標</param>
/// <param name="rotation">初期回転</param>
/// <param name="scale">初期スケール</param>
void Head::InitialTransform(
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
void Head::Update() {}
/// <summary>
/// 終了処理
/// </summary>
void Head::Finalize() {}

