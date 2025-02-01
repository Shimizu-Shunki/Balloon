#include "pch.h"
#include "Scenes/PlayScene/PlayScene.h"
#include "Game/Camera/TPSCamera.h"

#include "Framework/InputManager.h"
#include "Game/Fade/Fade.h"
#include "Game/UI/Timer.h"
#include "Game/UI/Countdown.h"
#include "Game/Sky/SkySphere.h"
#include "Game/Player/Player.h"
#include "Framework/AudioManager.h"

#include "Game/Camera/DebugCamera.h"
#include "Game/Object/Object.h"
#include "Framework/CollisionManager.h"
#include "Shader/Material/SeaMaterial.h"

#include "Interface/IScene.h"




PlayScene::PlayScene(SceneManager* scene_manager)
{
	// �O���t�B�b�N�X�C���X�^���X���擾����
	m_graphics = Graphics::GetInstance();
	// �V�[���}�l�[�W���[�̃C���X�^���X���擾����
	m_scene_manager = scene_manager;
	// �I�[�f�B�I�}�l�[�W���[�̃C���X�^���X���擾����
	m_audioManager = AudioManager::GetInstance();
	// �C���v�b�g�}�l�[�W���[�̃C���X�^���X���擾����
	m_input_manager = InputManager::GetInstance();
}

void PlayScene::Initialize()
{
	// �����蔻��Ǘ����쐬
	m_collisionManager = std::make_unique<CollisionManager>();

	// TPS�J�����쐬�@������
	m_tpsCamera = std::make_unique<TPSCamera>();
	m_tpsCamera->Initialize();

	// �X�J�C�X�t�B�A�쐬
	m_skySphere = std::make_unique<SkySphere>();
	m_skySphere->Initialize();

	m_SeaMaterial = std::make_unique<SeaMaterial>();
	m_SeaMaterial->Initialize();

	
	// �v���C���[�̍쐬
	m_player = std::make_unique<Player>(m_collisionManager.get(), nullptr, 3, DirectX::SimpleMath::Vector3::Up * 26.0f , 0.0f);
	m_player->Initialize(IComponent::ObjectID::PLAYER, true);

	// ���I�u�W�F�N�g���쐬�Ə�����
	this->InitializeObject();

	m_collisionManager->Attach(m_player.get());
	// �G�̍쐬

	// UI�̏�����
	// �t�F�[�h�̍쐬
	m_fade = std::make_unique<Fade>(m_scene_manager);
	
	// �^�C�}�[�쐬
	m_timer = std::make_unique<Timer>();
	m_timer->Initialize(false,66.0f);
	// �J�E���g�_�E���쐬
	m_countdown = std::make_unique<Countdown>();
	m_countdown->Initialize();

	// �����蔻��̏�����
	m_collisionManager->Initialize();

	// BGM���Đ�����
	m_audioManager->PlayFadeOutBgm(XACT_WAVEBANK_SOUNDS_PLAYSCENE, 2.0f);

	m_isFade = true;
}

void PlayScene::Start()
{
	// �t�F�[�h�������s��
	m_fade->FadeIN();
}


void PlayScene::Update(float elapsed_time)
{
	// �X�J�C�X�t�B�A�i��j�X�V����
	m_skySphere->Update(elapsed_time);
	// ����̍X�V����
	UpdateFloor(elapsed_time);


	// �v���C���[�X�V����
	m_player->Update(elapsed_time, DirectX::SimpleMath::Vector3::Zero, m_tpsCamera->GetRotation());
	// �J�����̍X�V����
	m_tpsCamera->Update(elapsed_time, m_player->GetPosition());
	// �r���[�s��̍쐬
	m_tpsCamera->CalculateViewMatrix();

	
	// �G�̍X�V����

	// �^�C�}�[�̏���
	m_timer->Update(elapsed_time);
	// �J�E���g�_�E���̏���
	m_countdown->Update(elapsed_time);

	// �����蔻����s��
	m_collisionManager->CheckCollision();
}

void PlayScene::Render()
{
	// �X�J�C�X�t�B�A�i��j�X�V����
	m_skySphere->Render();

	// ���̕`��
	m_floorPlayerStart->Render();
	m_floorLeftUp->Render();
	m_floorRightUp->Render();
	m_floorLeftDown->Render();
	m_floorRightDown->Render();
	m_floorPlayerStart->Render();

	// �v���C���[�̕`��
	m_player->Render();
	// �G�̕`��

	

	// ���̕`��
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	m_graphics->DrawGridFloor({ 10.0f,0.0f,0.0f }, { 0.0f,0.0f,10.0f }, 20);
	m_graphics->DrawPrimitiveEnd();

	m_SeaMaterial->Render();

	// UI�̕`��
	
	// �^�C�}�[�̕`��
	m_timer->Render();
	// �J�E���g�_�E���̕`��
	m_countdown->Render();
	// �t�F�[�h
	m_fade->Render();

	/*m_graphics->GetSpriteBatch()->Begin();
	m_graphics->DrawString(10.0f, 60.0f, L"PlayScene");
	m_graphics->GetSpriteBatch()->End();*/
}

void PlayScene::Finalize()
{

}

void PlayScene::InitializeObject()
{
	// �I�u�W�F�N�g�̏�����
	m_floorPlayerStart = std::make_unique<Object>();
	m_floorLeftUp      = std::make_unique<Object>();
	m_floorRightUp     = std::make_unique<Object>();
	m_floorLeftDown    = std::make_unique<Object>();
	m_floorRightDown   = std::make_unique<Object>();

	m_floorPlayerStart->Initialize(IComponent::ObjectID::CLOUD , true);
	m_floorLeftUp->Initialize(IComponent::ObjectID::CLOUD, true);
	m_floorRightUp->Initialize(IComponent::ObjectID::CLOUD, true);
	m_floorLeftDown->Initialize(IComponent::ObjectID::CLOUD, true);
	m_floorRightDown->Initialize(IComponent::ObjectID::CLOUD, true);

	m_collisionManager->Attach(m_floorPlayerStart.get());
	m_collisionManager->Attach(m_floorLeftUp.get());
	m_collisionManager->Attach(m_floorRightUp.get());
	m_collisionManager->Attach(m_floorLeftDown.get());
	m_collisionManager->Attach(m_floorRightDown.get());

}

void PlayScene::UpdateFloor(float elapsed_time)
{
	// ���I�u�W�F�N�g�X�V����
	m_floorPlayerStart->Update(elapsed_time, {  0.0f , 24.0f ,   0.0f }, DirectX::SimpleMath::Quaternion::Identity);
	m_floorLeftUp->Update(elapsed_time,      {-15.0f , 18.0f ,  15.0f }, DirectX::SimpleMath::Quaternion::Identity);
	m_floorRightUp->Update(elapsed_time,     { 15.0f , 18.0f ,  15.0f }, DirectX::SimpleMath::Quaternion::Identity);
	m_floorLeftDown->Update(elapsed_time,    {-15.0f , 18.0f , -15.0f }, DirectX::SimpleMath::Quaternion::Identity);
	m_floorRightDown->Update(elapsed_time,   { 15.0f , 18.0f , -15.0f }, DirectX::SimpleMath::Quaternion::Identity);
}