#include "Framework/pch.h"
#include "Game/Balloon/Balloon.h"
#include "Framework/CommonResources.h"


Balloon::Balloon(IObject* parent, float angle)
	:
	m_parent(parent),
	m_angle(angle),
	m_transform{},
	m_objectId{},
	m_isActive{},
	m_model{}
{
	// インスタンスを取得する
	m_commonResources = CommonResources::GetInstance();
}

Balloon::~Balloon()
{

}


void Balloon::Initialize(ObjectID objectID, const bool& active)
{
	// オブジェクトIDを設定
	m_objectId = objectID;
	// オブジェクトアクティブを設定
	m_isActive = active;
	// モデルを取得
	m_model = m_commonResources->GetResources()->GetBalloonModel();

	m_transform = std::make_unique<Transform>();

	// 位置を初期化
	m_transform->SetLocalPosition({ 0.0f,0.0f,0.0f });
	// 回転角を初期化
	m_transform->SetLocalRotation(
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3::Forward,DirectX::XMConvertToRadians(m_angle)
		)
	);
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

void Balloon::Update()
{


}

void Balloon::Finalize() {}

void Balloon::OnCollisionEnter(IObject* object) { (void)object; }
void Balloon::OnCollisionStay(IObject* object) { (void)object; }
void Balloon::OnCollisionExit(IObject* object) { (void)object; }
void Balloon::OnTriggerEnter(IObject* object) { (void)object; }
void Balloon::OnTriggerStay(IObject* object) { (void)object; }
void Balloon::OnTriggerExit(IObject* object) { (void)object; }
