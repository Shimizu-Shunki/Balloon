// ============================================
// 
// �t�@�C����: DebugScene.cpp
// �T�v: �f�o�b�O�p�̃V�[��
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/DebugScene.h"
#include "Interface/IScene.h"
#include "Game/Cameras/DebugCamera.h"


DebugScene::DebugScene()
{
	m_commonResources = CommonResources::GetInstance();
}


DebugScene::~DebugScene()
{

}

void DebugScene::Initialize()
{
	// �f�o�b�O�J����
	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(1280, 720);
}

void DebugScene::Start()
{
	
}

void DebugScene::Update()
{
	// �J�������X�V
	m_debugCamera->Update();
	m_commonResources->SetViewMatrix(m_debugCamera->GetViewMatrix());
}

void DebugScene::Render()
{
	
}


void DebugScene::Finalize()
{

}

