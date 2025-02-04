#include "Framework/pch.h"
#include "Game/Transform/Transform.h"
#include "Framework/Tween/TweenManager.h"
#include "Framework/Tween/Tween.h"

Transform::Transform()
{
	// TweenManagerのインスタンスを取得する
	m_tweenManager = TweenManager::GetInstance();
}


void Transform::Update()
{
	// ワールド行列を計算する
	m_worldMatrix =
		DirectX::SimpleMath::Matrix::CreateScale(m_localScale) *
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_localRotation) *
		DirectX::SimpleMath::Matrix::CreateTranslation(m_localPosition);

	// 親のワールド行列をかける
	if(m_parent != nullptr)
	m_worldMatrix = m_parent->GetWorldMatrix() * m_worldMatrix;

	// 子供の行列計算を行う
	for (auto& child : m_childs)
	{
		child->Update();
	}
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