#include "Framework/pch.h"
#include "Framework/Resources.h"
#include "Framework/CommonResources.h"
#include "Microsoft/ReadData.h"

std::unique_ptr<Resources> Resources::m_resources = nullptr;

const std::vector<D3D11_INPUT_ELEMENT_DESC> Resources::UI_INPUT_LAYOUT =
{ 
   // セマンティック名 インデックス フォーマット         入力スロット    オフセット                                                                                                                                         データ種別        インスタンスステップ率
		{ "SV_Position",0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  0,                                                                                                                                                         D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4 position
		{ "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  sizeof(DirectX::SimpleMath::Vector4),                                                                                                                      D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 rotate
		{ "TEXCOORD" ,  0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3),                                                                               D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 scale
		{ "TEXCOORD" ,  1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector3),                                        D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4 rect
		{ "COLOR",      0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 }  // float4 color
};
const std::vector<D3D11_INPUT_ELEMENT_DESC> Resources::SEA_INPUT_LAYOUT =
{
	{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,                                    D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,    0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

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

	// リソースディレクトリを設定
	m_effectFactory->SetDirectory(L"Resources\\Models\\EnemyModel");
	// 敵　頭モデルをロードする
	m_enemyHeadModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\EnemyModel\\EnemyFace.cmo", *m_effectFactory);

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
	// スペースキー
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\SpaceKey.png", nullptr, m_spaceKey.ReleaseAndGetAddressOf());

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
		m_device, L"Resources\\Textures\\200.png", nullptr, m_ruleTexture.ReleaseAndGetAddressOf());
	// ゲームクリアテキスト画像
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\ClearText.png", nullptr, m_clearText.ReleaseAndGetAddressOf());
	// ゲームオーバーテキスト画像
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\FailedText.png", nullptr, m_failedText.ReleaseAndGetAddressOf());
	// 海画像
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\water5.png", nullptr, m_SeaTexture.ReleaseAndGetAddressOf());

	// シェーダー
	std::vector<uint8_t> blob;
	// 頂点シェーダをロードする
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\UI_VS.cso");
	DX::ThrowIfFailed(
		m_device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_UI_VS.ReleaseAndGetAddressOf())
	);
	//	インプットレイアウトの作成
	m_device->CreateInputLayout(&UI_INPUT_LAYOUT[0],
		static_cast<UINT>(UI_INPUT_LAYOUT.size()),
		blob.data(), blob.size(),
		m_UIinputLayout.GetAddressOf());

	// ジオメトリシェーダをロードする
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\UI_GS.cso");
	DX::ThrowIfFailed(
		m_device->CreateGeometryShader(blob.data(), blob.size(), nullptr, m_UI_GS.ReleaseAndGetAddressOf())
	);
	// ピクセルシェーダをロードする
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\UI_PS.cso");
	DX::ThrowIfFailed(
		m_device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_UI_PS.ReleaseAndGetAddressOf())
	);

	// 頂点シェーダをロードする
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\Sea_VS.cso");
	DX::ThrowIfFailed(
		m_device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_SeaVS.ReleaseAndGetAddressOf())
	);

	//	インプットレイアウトの作成
	m_device->CreateInputLayout(&SEA_INPUT_LAYOUT[0],
		static_cast<UINT>(SEA_INPUT_LAYOUT.size()),
		blob.data(), blob.size(),
		m_SeaInputLayout.GetAddressOf());

	// ハルシェーダーをロードする
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\Sea_HS.cso");
	DX::ThrowIfFailed(
		m_device->CreateHullShader(blob.data(), blob.size(), nullptr, m_SeaHS.ReleaseAndGetAddressOf())
	);

	// ドメインシェーダをロードする
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\Sea_DS.cso");
	DX::ThrowIfFailed(
		m_device->CreateDomainShader(blob.data(), blob.size(), nullptr, m_SeaDS.ReleaseAndGetAddressOf())
	);

	// ピクセルシェーダをロードする
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\Sea_PS.cso");
	DX::ThrowIfFailed(
		m_device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_SeaPS.ReleaseAndGetAddressOf())
	);
}
