#include "Framework/pch.h"
#include "Framework/Resources.h"
#include "Framework/CommonResources.h"

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
	m_commonResources = CommonResources::GetInstance();

	m_device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	// エフェクトファクトリを生成する
	m_effectFactory = std::make_unique<DirectX::EffectFactory>(m_device);
	// リソースディレクトリを設定する
	m_effectFactory->SetDirectory(L"Resources\\Models\\PlayerModels");
	// プレイヤー　頭モデルをロードする
	m_playerHeadModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\PlayerModels\\Head.cmo", *m_effectFactory);
	// プレイヤー　体モデルをロードする
	m_playerBodyModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\PlayerModels\\Body.cmo", *m_effectFactory);
	// プレイヤー　右腕モデルをロードする
	m_playerRightArmModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\PlayerModels\\RightArm.cmo", *m_effectFactory);
	// プレイヤー　左腕モデルをロードする
	m_playerLeftArmModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\PlayerModels\\LeftArm.cmo", *m_effectFactory);
	// プレイヤー　右足モデルをロードする
	m_playerRightFootModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\PlayerModels\\RightFoot.cmo", *m_effectFactory);
	// プレイヤー　左足モデルをロードする
	m_playerLeftFootModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\PlayerModels\\LeftFoot.cmo", *m_effectFactory);

	// リソースディレクトリを設定する
	m_effectFactory->SetDirectory(L"Resources\\Models");
	// プレイヤー　風船モデルをロードする
	m_balloonModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\Balloon.cmo", *m_effectFactory);
	// プレイヤー　雲モデルをロードする
	m_cloudModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\Cloud.cmo", *m_effectFactory);
	// リソースディレクトリを設定する
	m_effectFactory->SetDirectory(L"Resources\\Models\\SkySphere");
	// プレイヤー　スカイスフィアモデルをロードする
	m_skySphere = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\SkySphere\\SkySphere.cmo", *m_effectFactory);

	//　テクスチャのロード
	// タイトルロゴ
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\Logo.png", nullptr, m_titleLogo.ReleaseAndGetAddressOf());
	// スタートテキスト
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\StartText.png", nullptr, m_startText.ReleaseAndGetAddressOf());

	// ジャンプフレーム
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\JumpFrameUI.png", nullptr, m_jampFrame.ReleaseAndGetAddressOf());
	// ジャンプメモリ
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\JumpBar.png", nullptr, m_jampMemori.ReleaseAndGetAddressOf());
	// タイムフレーム
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\TimeFrame.png", nullptr, m_timeFrame.ReleaseAndGetAddressOf());
	// タイムゲージ
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\TimerBar.png", nullptr, m_timeGage.ReleaseAndGetAddressOf());
	// ナンバーズ
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\numberx128.png", nullptr, m_numbers.ReleaseAndGetAddressOf());
	// ルール画像
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\132.png", nullptr, m_ruleTexture.ReleaseAndGetAddressOf());
}
