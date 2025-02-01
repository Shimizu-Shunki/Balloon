#include "Framework/pch.h"
#include "Game/Player/Header/LeftArm.h"
#include "Framework/CommonResources.h"



LeftArm::LeftArm(IObject* parent)
	:
	m_parent(parent),
	m_transform{},
	m_childs{},
	m_objectId{},
	m_isActive{},
	m_model{}
{
	// インスタンスを取得する
	m_commonResources = CommonResources::GetInstance();
}

LeftArm::~LeftArm()
{

}


void LeftArm::Initialize(ObjectID objectID, const bool& active)
{
	// オブジェクトIDを設定
	m_objectId = objectID;
	// オブジェクトアクティブを設定
	m_isActive = active;
	// モデルを取得
	m_model = m_commonResources->GetResources()->GetPlayerLeftArmModel();

	m_transform = std::make_unique<Transform>();

	// 位置を初期化
	m_transform->SetLocalPosition({ 0.0f,0.0f,0.0f });
	// 回転角を初期化
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	// スケールを初期化
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);

	// トランスフォームを親に設定
	m_transform->SetParent(m_parent->GetTransform());
	// 親のTransformに自分自身を子供に設定
	m_parent->GetTransform()->SetChild(m_transform.get());

	// 描画管理クラスにTransformとモデルを設定
	m_commonResources->GetRenderManager()->AddModel({
		m_transform.get(),
		m_model
	});

}

void LeftArm::Update()
{

	// 子供を更新する
	for (const auto& childObject : m_childs)
	{
		childObject->Update();
	}
}

void LeftArm::Finalize() {}


void LeftArm::Attach(std::unique_ptr<IObject> turretParts, IObject::ObjectID objectId)
{
	// パーツの初期化
	turretParts->Initialize(objectId, true);
	// 子供に登録
	m_childs.emplace_back(std::move(turretParts));
}


void LeftArm::Detach(std::unique_ptr<IObject> turretParts)
{

}

void LeftArm::OnCollisionEnter(IObject* object) { (void)object; }
void LeftArm::OnCollisionStay(IObject* object) { (void)object; }
void LeftArm::OnCollisionExit(IObject* object) { (void)object; }
void LeftArm::OnTriggerEnter(IObject* object) { (void)object; }
void LeftArm::OnTriggerStay(IObject* object) { (void)object; }
void LeftArm::OnTriggerExit(IObject* object) { (void)object; }
