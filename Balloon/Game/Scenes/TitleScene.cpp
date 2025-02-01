#include "pch.h"
#include "Scenes/TitleScene/TitleScene.h"
#include "Shader/2DSpriteShader/Sprite2DShader.h"
#include "Game/Fade/Fade.h"
#include "Game/Sky/SkySphere.h"

#include "Framework/InputManager.h"
#include "Framework/AudioManager.h"
#include "Framework/TweenManager.h"
#include "Framework/Tween.h"
#include "Interface/IScene.h"
#include "Sounds.h"




TitleScene::TitleScene(SceneManager* scene_manager)
{
	// �O���t�B�b�N�X�C���X�^���X���擾����
	m_graphics = Graphics::GetInstance();
	// �V�[���}�l�[�W���[�̃C���X�^���X���擾����
	m_scene_manager = scene_manager;
	// �C���v�b�g�}�l�[�W���[�̃C���X�^���X���擾����
	m_input_manager = InputManager::GetInstance();
	// �I�[�f�B�I�}�l�[�W���[�̃C���X�^���X���擾����
	m_audioManager = AudioManager::GetInstance();
	// Tween�}�l�[�W���[�̃C���X�^���X���擾����
	m_tweenManager = TweenManager::GetInstance();
	
}

void TitleScene::Initialize()
{
	// �X�J�C�X�t�B�A�쐬
	m_skySphere = std::make_unique<SkySphere>();
	m_skySphere->Initialize();


	m_titleLogo = std::make_unique<Sprite2DShader>();
	m_spaceKey  = std::make_unique<Sprite2DShader>();
	m_startText = std::make_unique<Sprite2DShader>();

	// �^�C�g�����S
	m_titleLogo->Initialize({ 200.0f - 100.0f,95,0.0f },DirectX::SimpleMath::Quaternion::Identity,DirectX::SimpleMath::Vector3::One * 0.5f,
		L"Resources/Shaders/UI_PS.cso");
	// �X�y�[�X�L�[
	m_spaceKey->Initialize({ 1280.0f / 4.0f + 30,720.0f / 2.0f + 70,0.0f }, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.4f,
		L"Resources/Shaders/UI_PS.cso");
	// �X�^�[�g�e�L�X�g
	m_startText->Initialize({1280.0f / 4.0f + 60,720.0f / 2.0f + 50,0.0f}, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.4f,
		L"Resources/Shaders/UI_PS.cso");
	

	// �e�N�X�`���̃��[�h
	m_titleLogo->LoadTexture(L"Resources\\Textures\\Logo2.png",1);
	m_spaceKey->LoadTexture(L"Resources\\Textures\\SpaceKey.png", 1);
	m_startText->LoadTexture(L"Resources\\Textures\\StartText.png",1);

	// �t�F�[�h�̍쐬
	m_fade = std::make_unique<Fade>(m_scene_manager);
	 m_fade->FadeIN();
	//m_fade->FadeIN();
	// BGM���Đ�����
	m_audioManager->PlayFadeOutBgm(XACT_WAVEBANK_SOUNDS_TITLESCENE,2.0f);

	m_position = DirectX::SimpleMath::Vector3::Zero;


	// �A�j���[�V�����̍쐬�Ɛݒ�
	// 1. ���݂̈ʒu�im_position�j��Ώۂɂ���Tween���쐬
	auto tween = std::make_shared<Tween>(m_position);

	// 2. �A�j���[�V�����̏I���ʒu�Ǝ������Ԃ�ݒ�
	tween->DOMove({ 10, 5, 0 }, 2.0f)             // {10, 5, 0} �̈ʒu�܂�2�b�Ԃňړ�����悤�ݒ�
		.SetDelay(3.0f)                           // �A�j���[�V�����J�n��3�b�x�点��
		.SetLoops(2, Tween::LoopType::Yoyo)       // Yoyo�i�����j���[�h��2��J��Ԃ�
		.SetEase(Tween::EaseType::EaseInOutQuad); // �C�[�W���O��EaseInOutQuad���g�p

	// 3. �쐬����Tween��TweenManager�ɓo�^
	// TweenManager�̓A�j���[�V�������Ǘ����A�K�v�ɉ����čX�V�E�폜���s��
	m_tweenManager->RegisterTween(tween);
}

void TitleScene::Start()
{

}


void TitleScene::Update(float elapsed_time)
{
	m_skySphere->Update(elapsed_time);

	// �f�o�b�O�V�[���Ɉړ�
	if (m_input_manager->GetKeyboardTracker()->IsKeyReleased(DirectX::Keyboard::F1))
	{
		// ���ʉ���炷
		m_audioManager->PlaySE();
		// BGM���~
		m_audioManager->StopFadeInBgm(1.0f);
		
		//m_fade->ChangeSceneFadeOUT<HomeScene>();
		return;
	}
	// �X�y�[�X�Ńv���C�V�[���Ɉړ�
	if (m_input_manager->GetKeyboardTracker()->IsKeyPressed(DirectX::Keyboard::Space))
	{

		// ���ʉ���炷
		//m_audioManager->PlaySE();

		/*m_scene_manager->NextSceneLoade<PlayScene>([this]() {
			m_scene_manager->ChageScene();
			});*/

		// BGM���~
		m_audioManager->StopFadeInBgm(1.0f);
		m_fade->ChangeSceneFadeOUT<PlayScene>();
		return;
	}
}

void TitleScene::Render()
{
	m_skySphere->Render();

	m_spaceKey->Render();
	m_startText->Render();

	m_titleLogo->Render();

	

	m_fade->Render();


	//// �e�̏���\��
	//ImGui::Begin("Hierarchy");

	//float position[3] = { m_position.x,  m_position.y, m_position.z };
	//ImGui::DragFloat3("testTween", position);

	//ImGui::End();

	/*m_graphics->GetSpriteBatch()->Begin();
	m_graphics->DrawString(10.0f, 60.0f, L"TitleScene");
	m_graphics->GetSpriteBatch()->End();*/
}

void TitleScene::Finalize()
{

}