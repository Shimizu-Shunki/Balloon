// ============================================
// 
// ファイル名: DebugScene.cpp
// 概要: デバッグ用のシーン
// 
// 製作者 : 清水駿希
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
	// デバッグカメラ
	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(1280, 720);
}

void DebugScene::Start()
{
	
}

void DebugScene::Update()
{
	// カメラを更新
	m_debugCamera->Update();
	m_commonResources->SetViewMatrix(m_debugCamera->GetViewMatrix());
}

void DebugScene::Render()
{
	
}


void DebugScene::Finalize()
{

}

