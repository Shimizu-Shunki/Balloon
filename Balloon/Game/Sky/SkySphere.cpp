#include "Framework/pch.h"
#include "Game/Sky/SkySphere.h"
#include "Framework/CommonResources.h"
#include "Game/Transform/Transform.h"

// �C���X�s�[�h
const float SkySphere::ROTATION_SPEED = 1.5f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SkySphere::SkySphere()
	:
	m_model{},
	m_transform{},
	m_targetTransform{},
	m_commonResources{}
{
	// �C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();
}


/// <summary>
/// ����������
/// </summary>
void SkySphere::Initialize()
{
	// ���f�����擾���� �u�X�J�C�X�t�B�A�v
	m_model = m_commonResources->GetResources()->GetSkySphere();
	// Transform���쐬����
	m_transform = std::make_unique<Transform>();

	// �e�͂Ȃ�
	m_transform->SetParent(nullptr);

	// ���W������
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Up * 250.0f);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale({ 5.0f, 3.5f, 5.0f });

	// �X�J�C�X�t�B�A��RenderManager�ɓo�^����
	m_commonResources->GetRenderManager()->SetSkySphereObject(m_transform.get(),m_model);
}

/// <summary>
/// �X�V����
/// </summary>
void SkySphere::Update()
{
	// �t���[��
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// Y���ɉ�]
	m_transform->SetLocalRotation(
		m_transform->GetLocalRotation() *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(ROTATION_SPEED * elapsedTime))
	);

	// �^�[�Q�b�g���K�����Ă���ꍇ���W���^�[�Q�b�g�̍��W�ɂ���
	if (m_targetTransform != nullptr)
		m_transform->SetLocalPosition(m_targetTransform->GetLocalPosition());
	else
		m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Up * 250.0f);

	// Transform�X�V
	m_transform->Update();
}

