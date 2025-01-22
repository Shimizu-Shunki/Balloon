#include "pch.h"
#include "Game/UI/Score.h"
#include "Shader/2DSpriteShader/Sprite2DShader.h"

// �R���X�g���N�^
Score::Score()
{

}

// �f�X�g���N�^
Score::~Score()
{

}

// ����������
void Score::Initialize()
{
	// �X�R�A�̒l��������
	m_score = 0;
	// �}�e���A���̍쐬
	m_scoreMaterial = std::unique_ptr<Sprite2DShader>();
	// �}�e���A��������
	m_scoreMaterial->Initialize({ 1280.0f / 2.0f - 211.2f , 0.0f ,0.0f }, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.3f,
		L"Resources/Shaders/NumberUI_PS.cso");
}

void Score::Render()
{
	DirectX::SimpleMath::Vector4 digits;
	digits.x = (m_score / 1000) % 10; // ��̈�
	digits.y = (m_score / 100) % 10;  // �S�̈�
	digits.z = (m_score / 10) % 10;   // �\�̈�
	digits.w = m_score % 10;          // ��̈�

	m_scoreMaterial->SetRect(digits);

	// �`�揈��
	m_scoreMaterial->Render();
}