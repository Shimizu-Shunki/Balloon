#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Framework/RenderManager.h"
#include "Game/Scenes/Header/PlayScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"
#include "Framework/Tween/Tween.h"

#include "Game/Player/Header/Player.h"

#include "Game/Cameras/DebugCamera.h"

PlayScene::PlayScene()
{
	m_commonResources = CommonResources::GetInstance();
}


PlayScene::~PlayScene()
{

}

void PlayScene::Initialize()
{
	// �f�o�b�O�J����
	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(1280, 720);

	// Transform���쐬
	m_rootTransform = std::make_unique<Transform>();

	// �e�����Ȃ��̂�nullptr��ݒ�
	m_rootTransform->SetParent(nullptr);
	// �v���C���[�̍쐬
	m_rootObject.push_back(std::make_unique<Player>(nullptr,nullptr));

	m_rootObject[0]->Initialize(IObject::ObjectID::PLAYER,true);

	// �v���C���[��Transform���q���Ƃ��Đݒ�
	m_rootTransform->SetChild(m_rootObject[0]->GetTransform());
}

void PlayScene::Start()
{
	// Tween�e�X�g
	m_rootObject[0]->GetTransform()->GetTween()->DORotation({ 0.0f,30.0f,30.0f }, 4.0f).SetEase(Tween::EasingType::EaseInBounce);
}

void PlayScene::Update()
{
	m_rootObject[0]->Update();

	m_rootTransform->Update();

	m_debugCamera->Update();
	m_commonResources->GetCameraManager()->SetViewMatrix(m_debugCamera->GetViewMatrix());
}

void PlayScene::Render()
{
	//���f���̕`��
	m_commonResources->GetRenderManager()->Render();
}


void PlayScene::Finalize()
{

}

