#include "pch.h"
#include "Game/UI/Score.h"
#include "Shader/2DSpriteShader/Sprite2DShader.h"

// コンストラクタ
Score::Score()
{

}

// デストラクタ
Score::~Score()
{

}

// 初期化処理
void Score::Initialize()
{
	// スコアの値を初期化
	m_score = 0;
	// マテリアルの作成
	m_scoreMaterial = std::unique_ptr<Sprite2DShader>();
	// マテリアル初期化
	m_scoreMaterial->Initialize({ 1280.0f / 2.0f - 211.2f , 0.0f ,0.0f }, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.3f,
		L"Resources/Shaders/NumberUI_PS.cso");
}

void Score::Render()
{
	DirectX::SimpleMath::Vector4 digits;
	digits.x = (m_score / 1000) % 10; // 千の位
	digits.y = (m_score / 100) % 10;  // 百の位
	digits.z = (m_score / 10) % 10;   // 十の位
	digits.w = m_score % 10;          // 一の位

	m_scoreMaterial->SetRect(digits);

	// 描画処理
	m_scoreMaterial->Render();
}