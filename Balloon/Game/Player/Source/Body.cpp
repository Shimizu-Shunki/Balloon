#include "Framework/pch.h"
#include "Game/Player/Header/Body.h"
#include "Framework/CommonResources.h"

// 部品
#include "Game/Player/Header/Head.h"
#include "Game/Player/Header/LeftArm.h"
#include "Game/Player/Header/RightArm.h"
#include "Game/Player/Header/LeftFoot.h"
#include "Game/Player/Header/RightFoot.h"



Body::Body(IObject* parent)
	:
	m_parent(parent),
	m_transform{},
	m_childs{},
	m_objectId{},
	m_isActive{},
	m_model{}
{
	// Transformを生成
	m_transform = std::make_unique<Transform>();
}

void Body::Initialize(ObjectID objectID, const bool& active)
{
	// 共有リソース
	CommonResources* commonResources = CommonResources::GetInstance();

	// オブジェクトIDを設定
	m_objectId = objectID;
	// オブジェクトアクティブを設定
	m_isActive = active;

	// プレイヤーの体モデルを取得
	m_model = commonResources->GetResources()->GetPlayerBodyModel();
	
	// 描画管理クラスにTransformとモデルを設定
	commonResources->GetRenderManager()->AddModel({
		this,
		m_model
	});

	// プレイヤー
	if (m_objectId == ObjectID::PLAYER_BODY)
	{
		// アタッチ
		// 頭
		this->Attach(std::make_unique<Head>(this)           , ObjectID::PLAYER_HEAD);
		// 左腕
		this->Attach(std::make_unique<LeftArm>(this)    , ObjectID::PLAYER_LEFT_ARM);
		// 右腕
		this->Attach(std::make_unique<RightArm>(this)  , ObjectID::PLAYER_RIGHT_ARM);
		// 左足
		this->Attach(std::make_unique<LeftFoot>(this)  , ObjectID::PLAYER_LEFT_FOOT);
		// 右足
		this->Attach(std::make_unique<RightFoot>(this), ObjectID::PLAYER_RIGHT_FOOT);
	}
	// 敵
	else
	{
		// アタッチ
		// 頭
		this->Attach(std::make_unique<Head>(this)           , ObjectID::ENEMY_HEAD);
		// 左腕
		this->Attach(std::make_unique<LeftArm>(this)    , ObjectID::ENEMY_LEFT_ARM);
		// 右腕
		this->Attach(std::make_unique<RightArm>(this)  , ObjectID::ENEMY_RIGHT_ARM);
		// 左足
		this->Attach(std::make_unique<LeftFoot>(this)  , ObjectID::ENEMY_LEFT_FOOT);
		// 右足
		this->Attach(std::make_unique<RightFoot>(this), ObjectID::ENEMY_RIGHT_FOOT);
	}
	
}

/// <summary>
/// Transformを初期化
/// </summary>
/// <param name="position">初期座標</param>
/// <param name="rotation">初期回転</param>
/// <param name="scale">初期スケール</param>
void Body::InitialTransform(
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
void Body::Update()
{
	// 子供を更新する
	for (const auto& childObject : m_childs)
	{
		childObject->Update();
	}
}

/// <summary>
/// 終了処理
/// </summary>
void Body::Finalize() {}

/// <summary>
/// アタッチ
/// </summary>
/// <param name="object">オブジェクト</param>
/// <param name="objectId">オブジェクトID</param>
/// <param name="position">初期座標</param>
/// <param name="rotation">初期回転</param>
/// <param name="scale">初期スケール</param>
void Body::Attach(std::unique_ptr<IObject> object, IObject::ObjectID objectId,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	// パーツの初期化
	object->Initialize(objectId, true);
	// Transformの初期化
	object->InitialTransform(position, rotation, scale);

	// 子供に登録
	m_childs.emplace_back(std::move(object));
}

/// <summary>
/// デタッチ
/// </summary>
/// <param name="turretParts">オブジェクト</param>
void Body::Detach(std::unique_ptr<IObject> turretParts)
{

}