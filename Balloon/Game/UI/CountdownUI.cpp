#include "pch.h"
#include "Game/UI/Countdown.h"
#include "Framework/Graphics.h"
#include "Shader/2DSpriteShader/Sprite2DShader.h"

// コンストラクタ
Countdown::Countdown()
	:
	m_currentTime{},
	m_timer{}
{
	// インスタンスを取得する
	m_graphics = Graphics::GetInstance();
}

// デストラクタ
Countdown::~Countdown()
{

}

void Countdown::Initialize()
{
	// マテリアルの作成
	m_FrameMaterial = std::make_unique<Sprite2DShader>();
	m_ReadyMaterial = std::make_unique<Sprite2DShader>();
	m_GoMaterial    = std::make_unique<Sprite2DShader>();

	// マテリアル初期化
	m_FrameMaterial->Initialize({ 1280.0f / 2.0f - 250.0f * 0.3f, 50.0f ,0.0f }, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.3f,
		L"Resources/Shaders/UI_PS.cso");
	// マテリアル初期化
	m_ReadyMaterial->Initialize({ 1280.0f / 2.0f - 145.5 * 0.8f , 75.0f ,0.0f }, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.8f,
		L"Resources/Shaders/UI_PS.cso");
	// マテリアル初期化
	m_GoMaterial->Initialize({ 1280.0f / 2.0f - 91.0f * 0.8f, 75.0f ,0.0f }, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.8f,
		L"Resources/Shaders/UI_PS.cso");

	m_FrameMaterial->LoadTexture(L"Resources\\Textures\\CountdownFrame.png", 1);
	m_ReadyMaterial->LoadTexture(L"Resources\\Textures\\ReadyText.png", 1);
	m_GoMaterial->LoadTexture(L"Resources\\Textures\\GoText.png", 1);
	m_angle = 0.0f;

	m_currentTime = 0.0f;
}

bool Countdown::Update(const float& elapsedTime)
{
	m_currentTime += elapsedTime;

	m_angle +=  50.0f * elapsedTime;
	m_FrameMaterial->SetRotation(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right,DirectX::XMConvertToRadians(m_angle)));

	if (m_currentTime >= 3.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Countdown::Render()
{
	// 描画処理
	if (m_currentTime <= 1.5f)
	{
		m_FrameMaterial->Render();
		m_ReadyMaterial->Render();
	}
	else if (m_currentTime <= 3.0f)
	{
		m_FrameMaterial->Render();
		m_GoMaterial->Render();
	}
}

