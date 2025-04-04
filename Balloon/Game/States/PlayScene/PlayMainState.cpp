#include "Framework/pch.h"
#include "Game/States/PlayScene/PlayMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Player/Header/Player.h"
#include "Game/Enemy/Enemy.h"

// �R���X�g���N�^
PlayMainState::PlayMainState(std::vector<IObject*> objects)
{
	// ���̓}�l�[�W���[�̃C���X�^���X�����
	m_inputManager = InputManager::GetInstance();
	// �I�u�W�F�N�g���擾����
	m_objects = objects;
}

// �f�X�g���N�^
PlayMainState::~PlayMainState()
{

}

// ����������
void PlayMainState::PreUpdate()
{
	// �I�u�W�F�N�g��L�����ɂ���
	for (const auto& object : m_objects)
	{
		object->SetIsActive(true);
	}
}

// �X�V����
void PlayMainState::Update(const float& deltaTime)
{
	// �I�u�W�F�N�g�̍X�V���s��
	for (const auto& object : m_objects)
	{
		// �X�V����
		object->Update();
		// Transform�̍X�V����
		object->GetTransform()->Update();
	}
	// �^�C�}�[�̍X�V����

	// �V�[�����̂̍X�V
	
}

// �I������
void PlayMainState::PostUpdate()
{

}