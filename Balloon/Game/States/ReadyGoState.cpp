#include "Framework/pch.h"
#include "Game/States/ReadyGoState.h"
#include "Game/UI/ReadyGoUI.h"
#include "Framework/Tween/Tween.h"
#include "Framework/StateMachine/StateController.h"
#include "Game/Message/SceneMessenger.h"

// コンストラクタ
ReadyGoState::ReadyGoState(ReadyGoUI* readyGoUI)
{
	// 取得
	m_readyGoUI = readyGoUI;
}

// デストラクタ
ReadyGoState::~ReadyGoState()
{

}

// 初期化処理
void ReadyGoState::PreUpdate()
{
	// ステート切り替えフラグを非アクティブ
	m_changeFlag = false;

	

	// アニメーションを設定
	this->ReadyGoSetAnimation();
}

// 更新処理
void ReadyGoState::Update(const float& deltaTime)
{
	// ステートを切り替えるフラグがオンになったら
	if (m_changeFlag)
	{
		// ステートを切り替える
		SceneMessenger::GetInstance()->Dispatch(Message::COUNTDOWN);
	}
}

// 終了処理
void ReadyGoState::PostUpdate()
{

}

void ReadyGoState::ReadyGoSetAnimation()
{
	// Readyを中央に移動
	m_readyGoUI->GetTransform()->GetTween()->DOMove({ 1280.0f / 2.0f , 720.0f / 2.0f , 0.0f }, 1.0f).
		SetEase(Tween::EasingType::EaseOutCirc).OnComplete([this] {


		// Readyを左へフェードアウト
		m_readyGoUI->GetTransform()->GetTween()->DOMove({ -500.0f , 720.0f / 2.0f , 0.0f }, 1.0f).
			SetEase(Tween::EasingType::EaseOutCirc).SetDelay(0.5f).OnComplete([this] {
			// フェードアウトしたらGOに切り替える Rectを設定
			m_readyGoUI->GetTransform()->SetRect({
				0.0f,
				m_readyGoUI->GetTransform()->GetRect().w,
				m_readyGoUI->GetTransform()->GetRect().z,
				m_readyGoUI->GetTransform()->GetRect().w * 2.0f,
				});
			// スケールをゼロにする
			m_readyGoUI->GetTransform()->SetLocalScale(DirectX::SimpleMath::Vector3::Zero);
			// 座標を初期化
			m_readyGoUI->GetTransform()->SetLocalPosition({ 1280.0f / 2.0f , 720.0f / 2.0f , 0.0f });
				});

			});

	

	// Goをフェードイン
	m_readyGoUI->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One, 1.0f).
		SetEase(Tween::EasingType::EaseOutElastic).SetDelay(4.0f).OnComplete([this] {

		// GOをフェードアウト
		m_readyGoUI->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::Zero, 0.5f).
			SetEase(Tween::EasingType::EaseOutQuad).SetDelay(0.5f).OnComplete([this] {
				});
		m_changeFlag = true;
		m_readyGoUI->SetIsActive(false);
			});
	
}
