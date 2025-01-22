#include "pch.h"
#include "Game/UI/Timer.h"
#include "Framework/Graphics.h"
#include "Shader/2DSpriteShader/Sprite2DShader.h"

// コンストラクタ
Timer::Timer()
	:
	m_timerMaterial{},
	m_isCountingUp{},
	m_currentTime{},
	m_timer{},
	m_isActive(true)
{
	// インスタンスを取得する
	m_graphics = Graphics::GetInstance();
}

// デストラクタ
Timer::~Timer()
{

}

void Timer::Initialize(const bool& isCountingUp, const float& timeLimit)
{
	// マテリアルの作成
	m_timerMaterial = std::make_unique<Sprite2DShader>();
	m_timerFrameMaterial = std::make_unique<Sprite2DShader>();
	m_timerNumberMaterial = std::make_unique<Sprite2DShader>();

	// マテリアル初期化
	m_timerMaterial->Initialize({ 1280.0f / 2.0f + 87 , 85.0f ,0.0f}, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.5f ,
		L"Resources/Shaders/Timer_PS.cso");
	// マテリアル初期化
	m_timerFrameMaterial->Initialize({1280.0f / 2.0f + 80 , 60.0f ,0.0f}, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.5f,
		L"Resources/Shaders/UI_PS.cso");
	// マテリアル初期化
	m_timerNumberMaterial->Initialize({ 1280.0f / 2.0f + 532 , 82.0f ,0.0f }, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.06f + DirectX::SimpleMath::Vector3::Up * 0.07f,
		L"Resources/Shaders/NumberUI_PS.cso");


	m_timerMaterial->LoadTexture(L"Resources\\Textures\\TimerBar.png",1);
	m_timerFrameMaterial->LoadTexture(L"Resources\\Textures\\TimeFrame.png", 1);
	m_timerNumberMaterial->LoadTexture(L"Resources\\Textures\\numberx128.png", 1);
	// タイマーのモード初期化
	m_isCountingUp = isCountingUp;

	// カウントダウンの場合制限時間を設定
	if (!m_isCountingUp)
		m_currentTime = timeLimit;
}

void Timer::Update(const float& elapsedTime)
{
	if (!m_isActive) return;

	if (m_isCountingUp)
	{
		m_currentTime += elapsedTime;
	}
	else
	{
		if (m_currentTime > 0.0f)
		{
			m_currentTime -= elapsedTime;
		}
		else
		{
			m_currentTime = 0.0f;
		}
		
	}
}


void Timer::Render()
{
	if (!m_isActive) return;

	// タイムの値を正規化してシェーダーに渡す
	// シェーダーは灰色でUV値をみて黄色にする　黒のところは黒のまま出力する

	float timer = m_currentTime / 180.0f;

	// 分と秒を計算
	int minutes = static_cast<int>(m_currentTime) / 60;
	int seconds = static_cast<int>(m_currentTime) % 60;

	// 各桁を計算 (例: 23:45 -> {2, 3, 4, 5})
	DirectX::SimpleMath::Vector4 digits;
	digits.x = minutes / 10; // 分の10の位
	digits.y = minutes % 10; // 分の1の位
	digits.z = seconds / 10; // 秒の10の位
	digits.w = seconds % 10; // 秒の1の位

	m_timerNumberMaterial->SetRect(digits);

	m_timerMaterial->SetRuleProgress(timer);


	// 描画処理
	m_timerFrameMaterial->Render();
	m_timerMaterial->Render();
	m_timerNumberMaterial->Render();
}

