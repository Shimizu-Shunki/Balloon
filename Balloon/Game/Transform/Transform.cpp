#include "Framework/pch.h"
#include "Game/Transform/Transform.h"
#include "Framework/Tween/TweenManager.h"
#include "Framework/Tween/Tween.h"

Transform::Transform()
	:
	m_parent(nullptr)
{
	// TweenManagerのインスタンスを取得する
	m_tweenManager = TweenManager::GetInstance();
}

void Transform::Initialize(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	// ワールド座標系を設定する
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
	// ローカル座標系を設定する
	m_localPosition = position;
	m_localRotation = rotation;
	m_localScale    = scale;
}


void Transform::Update()
{
	// ローカル行列を計算する
		m_worldMatrix =
		DirectX::SimpleMath::Matrix::CreateScale(m_localScale) *
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_localRotation) *
		DirectX::SimpleMath::Matrix::CreateTranslation(m_localPosition);

	if (m_parent != nullptr)
	{
		// 子の行列に親の変位分を上乗せする
		m_worldMatrix *= m_parent->GetWorldMatrix() ;
	}
	
	// 子供の行列計算を行う
	for (auto& child : m_childs)
	{
		child->Update();
	}
}

// 親のTransofrmを設定する
void Transform::SetParent(Transform* parent)
{
	using namespace DirectX::SimpleMath;


	if (parent == nullptr) return;

	DirectX::SimpleMath::Matrix parentMatrix =
		DirectX::SimpleMath::Matrix::CreateScale(parent->GetLocalScale()) *
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(parent->GetLocalRotation()) *
		DirectX::SimpleMath::Matrix::CreateTranslation(parent->GetLocalPosition());

	DirectX::SimpleMath::Matrix childMatrix =
		DirectX::SimpleMath::Matrix::CreateScale(m_localScale) *
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_localRotation) *
		DirectX::SimpleMath::Matrix::CreateTranslation(m_localPosition);

	childMatrix *= parentMatrix.Invert();

	// ローカル座標を計算
	m_localPosition = { childMatrix._41,childMatrix._42, childMatrix._43 };


	// 各軸のスケールを計算
	float scaleX = Vector3(childMatrix._11, childMatrix._12, childMatrix._13).Length();
	float scaleY = Vector3(childMatrix._21, childMatrix._22, childMatrix._23).Length();
	float scaleZ = Vector3(childMatrix._31, childMatrix._32, childMatrix._33).Length();

	m_localScale = { scaleX, scaleY, scaleZ };

	// スケールを除去して回転行列を取り出す
	Vector3 scale = m_localScale;

	Matrix rotationMatrix = childMatrix;
	rotationMatrix._11 /= scale.x;
	rotationMatrix._12 /= scale.x;
	rotationMatrix._13 /= scale.x;

	rotationMatrix._21 /= scale.y;
	rotationMatrix._22 /= scale.y;
	rotationMatrix._23 /= scale.y;

	rotationMatrix._31 /= scale.z;
	rotationMatrix._32 /= scale.z;
	rotationMatrix._33 /= scale.z;

	// 行列の正規化（オルトノーマル化）
	rotationMatrix = rotationMatrix.Transpose().Invert();

	// 回転行列からクォータニオンを作成
	m_localRotation =  Quaternion::CreateFromRotationMatrix(rotationMatrix);
	
	m_parent = parent;

	// 親に自分自身を設定
	//parent->SetChild(this);
}


// Tweenを取得する
Tween* Transform::GetTween()
{
	// 進行中ではないtweenを取得する
	auto tween = m_tweenManager->GetTween();
	// 自身を設定する
	tween->SetTransform(this);
	// tweenを起動する
	tween->Play();
	// Tweenを返す
	return tween;
}