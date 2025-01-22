#include "pch.h"
#include "Game/Fade/Fade.h"
#include "Shader/2DSpriteShader/Sprite2DShader.h"
#include "Scenes/SceneManager/SceneManager.h"



// コンストラクタ
Fade::Fade()
	:
	m_sprite{},
	m_fadeTime{},
    m_isActive(false)
{
    m_sceneManager = SceneManager::GetInstance();
	// フェード用のスプライトを作成
	m_sprite = std::make_unique<Sprite2DShader>();
	// 初期化処理
	m_sprite->Initialize(DirectX::SimpleMath::Vector3::Zero, 
        DirectX::SimpleMath::Quaternion::Identity,
        DirectX::SimpleMath::Vector3::One, L"Resources/Shaders/UI_PS.cso");
	
    // 画像をロード
    m_sprite->LoadTexture(L"Resources\\Textures\\rule1080p\\022.png", 0);
    // ルール画像をロード
    m_sprite->LoadRuleTexture(L"Resources\\Textures\\rule1080p\\022.png");

    m_sprite->SetRuleActive(true);
    m_sprite->SetTexActive(false);
	// タイム
	m_fadeTime = 0;
}


// デストラクタ
Fade::~Fade()
{

}

//// フェードイン処理
//bool Fade::FadeIN()
//{
//    // フェード処理中なら true を返す
//    if (m_isActive)
//        return true;
//
//    m_isActive = true; // フェード処理開始
//    m_sprite->SetTime(1.0f); // アルファ値をシェーダーに設定
//
//    m_sprite->SetReversed(0);
//
//    // 非同期タスクを起動
//    m_future = std::async(std::launch::async, [this]() 
//    {
//        // 初期アルファ値（完全不透明）
//        float alpha = 1.0f;   
//        // アルファ値の減少量（60FPS基準で更新）
//        const float step = 0.016f; 
//
//        while (alpha > 0.0f)
//        {
//            alpha -= step;
//            if (alpha < 0.0f) alpha = 0.0f;
//            // アルファ値をシェーダーに設定
//            m_sprite->SetRuleProgress(alpha); 
//            
//            // フレーム待機 (16ms → 60FPS相当)
//            std::this_thread::sleep_for(std::chrono::milliseconds(16));
//        }
//        // 完了後にアクティブ状態を解除
//        m_isActive = false; 
//    });
//    // フェード処理中は true を返す
//    return m_isActive; 
//}
//
//
//// フェードアウト処理
//bool Fade::FadeOUT()
//{
//    return false;
//}

void Fade::Render()
{
    if (!m_isActive) return;

    m_sprite->Render();       // 描画処理
}