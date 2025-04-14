// ============================================
// 
// �t�@�C����: ReadyGoState.cpp
// �T�v: �J�E���g�_�E���X�e�[�g
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/ReadyGoState.h"
#include "Game/UI/ReadyGoUI.h"
#include "Framework/Tween/Tween.h"
#include "Framework/StateMachine/StateController.h"
#include "Game/Message/SceneMessenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ReadyGoState::ReadyGoState(ReadyGoUI* readyGoUI)
{
	// �擾
	m_readyGoUI = readyGoUI;
}


/// <summary>
/// ��������
/// </summary>
void ReadyGoState::PreUpdate()
{
	// �X�e�[�g�؂�ւ��t���O���A�N�e�B�u
	m_changeFlag = false;

	

	// �A�j���[�V������ݒ�
	this->ReadyGoSetAnimation();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void ReadyGoState::Update(const float& deltaTime)
{
	(void)deltaTime;

	// �X�e�[�g��؂�ւ���t���O���I���ɂȂ�����
	if (m_changeFlag)
	{
		// �X�e�[�g��؂�ւ���
		SceneMessenger::GetInstance()->Dispatch(Message::COUNTDOWN);
	}
}


/// <summary>
/// �I������
/// </summary>
void ReadyGoState::PostUpdate()
{

}

/// <summary>
/// �J�E���g�_�E���A�j���[�V�����ݒ�
/// </summary>
void ReadyGoState::ReadyGoSetAnimation()
{
	// Ready�𒆉��Ɉړ�
	m_readyGoUI->GetTransform()->GetTween()->DOMove({ 1280.0f / 2.0f , 720.0f / 2.0f , 0.0f }, 1.0f).
		SetEase(Tween::EasingType::EaseOutCirc).OnComplete([this] {


		// Ready�����փt�F�[�h�A�E�g
		m_readyGoUI->GetTransform()->GetTween()->DOMove({ -500.0f , 720.0f / 2.0f , 0.0f }, 1.0f).
			SetEase(Tween::EasingType::EaseOutCirc).SetDelay(0.5f).OnComplete([this] {
			// �t�F�[�h�A�E�g������GO�ɐ؂�ւ��� Rect��ݒ�
			m_readyGoUI->GetTransform()->SetRect({
				0.0f,
				m_readyGoUI->GetTransform()->GetRect().w,
				m_readyGoUI->GetTransform()->GetRect().z,
				m_readyGoUI->GetTransform()->GetRect().w * 2.0f,
				});
			// �X�P�[�����[���ɂ���
			m_readyGoUI->GetTransform()->SetLocalScale(DirectX::SimpleMath::Vector3::Zero);
			// ���W��������
			m_readyGoUI->GetTransform()->SetLocalPosition({ 1280.0f / 2.0f , 720.0f / 2.0f , 0.0f });
				});

			});

	

	// Go���t�F�[�h�C��
	m_readyGoUI->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One, 1.0f).
		SetEase(Tween::EasingType::EaseOutElastic).SetDelay(4.0f).OnComplete([this] {

		// GO���t�F�[�h�A�E�g
		m_readyGoUI->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::Zero, 0.5f).
			SetEase(Tween::EasingType::EaseOutQuad).SetDelay(0.5f).OnComplete([this] {
				});
		m_changeFlag = true;
		m_readyGoUI->SetIsActive(false);
			});
	
}
