#include "pch.h"
#include "Framework/Resources.h"

std::unique_ptr<Resources> Resources::m_resources = nullptr;

// Resourcesクラスのインスタンスを取得する
Resources* const Resources::GetInstance()
{
	if (m_resources == nullptr)
	{
		// Resourcesクラスのインスタンスを生成する
		m_resources.reset(new Resources());
	}
	// Resourcesクラスのインスタンスを返す
	return m_resources.get();
}

// リソースをロードする
void Resources::LoadResource()
{
	m_device = m_graphics->GetDeviceResources()->GetD3DDevice();

	// リソースディレクトリを設定する
	m_graphics->GetFX()->SetDirectory(L"Resources\\Model\\PlayerModels");
	// プレイヤー　頭モデルをロードする
	m_playerHeadModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\PlayerModels\\Head.cmo", *m_graphics->GetFX());
	// プレイヤー　体モデルをロードする
	m_playerBodyModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\PlayerModels\\Body.cmo", *m_graphics->GetFX());
	// プレイヤー　右腕モデルをロードする
	m_playerRightArmModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\PlayerModels\\RightArm.cmo", *m_graphics->GetFX());
	// プレイヤー　左腕モデルをロードする
	m_playerLeftArmModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\PlayerModels\\LeftArm.cmo", *m_graphics->GetFX());
	// プレイヤー　右足モデルをロードする
	m_playerRightFootModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\PlayerModels\\RightFoot.cmo", *m_graphics->GetFX());
	// プレイヤー　左足モデルをロードする
	m_playerLeftFootModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\PlayerModels\\LeftFoot.cmo", *m_graphics->GetFX());

	// リソースディレクトリを設定する
	m_graphics->GetFX()->SetDirectory(L"Resources\\Model");
	// プレイヤー　風船モデルをロードする
	m_balloonModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\Balloon.cmo", *m_graphics->GetFX());
	// プレイヤー　雲モデルをロードする
	m_cloudModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\Cloud2.cmo", *m_graphics->GetFX());
	// プレイヤー　スカイスフィアモデルをロードする
	m_skySphere = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\SkySphere3.cmo", *m_graphics->GetFX());
}
