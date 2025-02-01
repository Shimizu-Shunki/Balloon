#include "pch.h"
#include "Scenes/HomeScene/HomeScene.h"
#include "Game/Camera/DebugCamera.h"

#include "Framework/InputManager.h"
#include "Game/Object/Object.h"
#include "Framework/CollisionManager.h"
#include "Game/Player/Player.h"
#include "Game/Camera/TPSCamera.h"
#include "Game/Balloon/Balloon.h"
#include "Game/Player/Enemy.h"
#include "Interface/IComponent.h"
#include "Game/Camera/CameraManager.h"
#include "Interface/ICamera.h"
#include "Game/Camera/FixedCamera.h"

#include "Interface/IScene.h"
#include "Framework/Microsoft/RenderTexture.h"
#include <chrono>
#include <thread>




HomeScene::HomeScene(SceneManager* scene_manager)
{
	// �O���t�B�b�N�X�C���X�^���X���擾����
	m_graphics = Graphics::GetInstance();
	// �V�[���}�l�[�W���[�̃C���X�^���X���擾����
	m_scene_manager = scene_manager;
	// �C���v�b�g�}�l�[�W���[�̃C���X�^���X���擾����
	m_input_manager = InputManager::GetInstance();
}

HomeScene::~HomeScene()
{
	m_renderTexture->ReleaseDevice();
}

void HomeScene::Initialize()
{
	// �X�N���[���T�C�Y
	int w, h;
	m_graphics->GetScreenSize(w, h);

	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(w, h);

	// TPS�J�����쐬�@������
	m_tpsCamera = std::make_unique<TPSCamera>();
	m_tpsCamera->Initialize();

	// �I�u�W�F�N�g�̏�����
	m_floor = std::make_unique<Object>();
	m_floor->Initialize(IComponent::ObjectID::CLOUD, true);

	m_collisionManager = std::make_unique<CollisionManager>();
	
	// �v���C���[�̍쐬
	m_player = std::make_unique<Player>(m_collisionManager.get(), nullptr, 3, DirectX::SimpleMath::Vector3::Zero, 0.0f);
	m_player->Initialize(IComponent::ObjectID::PLAYER, true);

	// �G�̍쐬
	m_enemy = std::make_unique<Enemy>(m_collisionManager.get(), nullptr, 3, DirectX::SimpleMath::Vector3::Forward * 2.0f, 0.0f);
	m_enemy->Initialize(IComponent::ObjectID::ENEMY, true);

	// ���D�̍쐬�Ə�����
	/*m_balloon = std::make_unique<Balloon>();
	m_balloon->Initialize();*/

	m_collisionManager->Attach(m_player.get());
	//m_collisionManager->Attach(m_enemy.get());
	m_collisionManager->Attach(m_floor.get());

	/* �菇�P */
	/* �����_�[�e�N�X�`������������ */
	const auto& size = m_graphics->GetDeviceResources()->GetOutputSize();
	m_renderTexture = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_B8G8R8A8_UNORM);
	m_renderTexture->SetDevice(m_graphics->GetDeviceResources()->GetD3DDevice());
	m_renderTexture->SetWindow(size);


	// �J����
	m_cameraManager = std::make_unique<CameraManager>();

	// �J�������쐬
	std::unique_ptr<ICamera> camera = std::make_unique<FixedCamera>();
	camera->Initialize({ 0.0f,-5.0f,5.0f }, { 0.0f,0.0f,0.0f }, DirectX::SimpleMath::Quaternion::Identity);

	m_cameraManager->Attach(std::move(camera));
	
	camera = std::make_unique<FixedCamera>();
	camera->Initialize({ 5.0f,5.0f,0.0f }, { 0.0f,2.0f,0.0f }, DirectX::SimpleMath::Quaternion::Identity);

	m_cameraManager->Attach(std::move(camera));

	//m_collisionManager->Attach(m_balloon.get());
	m_cameraManager->ChageCamera(1);
}

void HomeScene::Start()
{

}

void HomeScene::Update(float elapsed_time)
{
	//m_debugCamera->Update();

	m_cameraManager->Update(elapsed_time);

	// ���I�u�W�F�N�g�X�V����
	m_floor->Update(elapsed_time,DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Quaternion::Identity);
	


	// �G�̍X�V����
	m_enemy->Update(elapsed_time, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);

	m_tpsCamera->Update(elapsed_time, m_player->GetPosition());
	// �r���[�s��̍쐬
	//m_tpsCamera->CalculateViewMatrix();

	// �v���C���[�X�V����
	m_player->Update(elapsed_time, DirectX::SimpleMath::Vector3::Zero, m_tpsCamera->GetRotation());


	//auto state = m_input_manager->GetGamePad()->GetState(0);

	//// �Q�[���p�b�h����
	//if (m_input_manager->GetButtonStateTracker()->a)
	//{
	//	if (state.IsConnected())
	//	{
	//		m_input_manager->GetGamePad()->SetVibration(0, 0.5f, 0.5f);

	//		// �U������ (1�b��)
	//		std::this_thread::sleep_for(std::chrono::seconds(1));

	//		// �U�����~
	//		m_input_manager->GetGamePad()->SetVibration(0, 0.0f, 0.0f);
	//	}
	//}
	
}

void HomeScene::Render()
{

	//auto context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	//auto states = m_graphics->GetCommonStates();

	///* �菇�Q */
	///* �����_�[�^�[�Q�b�g���I�t�X�N���[���ɐ؂�ւ��� */
	//// �I�t�X�N���[����RTV�Ɗ���̐[�x�o�b�t�@���擾����
	//auto rtv = m_renderTexture->GetRenderTargetView();
	//auto defaultDSV = m_graphics->GetDeviceResources()->GetDepthStencilView();

	//// RTV���N���A����
	//context->ClearRenderTargetView(rtv, DirectX::Colors::CornflowerBlue);
	//// �[�x�o�b�t�@���N���A����
	//context->ClearDepthStencilView(defaultDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
	//// RTV��DSV��ݒ肷��
	//context->OMSetRenderTargets(1, &rtv, defaultDSV);

	// 3. �V�[���̕`��
	// ���f���̕`��
	m_floor->Render();
	m_player->Render();
	m_enemy->Render();
	//m_balloon->Render();

	m_collisionManager->CheckCollision();

	// ���̕`��
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	m_graphics->DrawGridFloor({ 10.0f,0.0f,0.0f }, { 0.0f,0.0f,10.0f }, 20);
	m_graphics->DrawPrimitiveEnd();

	//// 4. �t���[���o�b�t�@�ɖ߂�
	//auto defaultRTV = m_graphics->GetDeviceResources()->GetRenderTargetView();
	//context->OMSetRenderTargets(1, &defaultRTV, nullptr);


	//// ImGui�E�B���h�E�J�n
	//ImGui::Begin("Scene View");
	//// ���݂�ImGui�E�B���h�E���̗��p�\�̈���擾
	//ImVec2 contentSize = ImGui::GetContentRegionAvail();
	//
	//// 5. ImGui�Ńe�N�X�`����\��
	//if (m_renderTexture->GetShaderResourceView())
	//{
	//	ImGui::Image((ImTextureID)m_renderTexture->GetShaderResourceView(), contentSize);
	//}
	//else
	//{
	//	ImGui::Text("RenderTexture is not ready.");
	//}
	//ImGui::End();

	
	
	m_graphics->GetSpriteBatch()->Begin();
	m_graphics->DrawString(10.0f, 60.0f, L"HomeScene");
	m_graphics->GetSpriteBatch()->End();
}

void HomeScene::Finalize()
{

}