#include "Framework/pch.h"
#include "Game/Fade/Fade.h"
#include "Framework/SceneManager.h"
#include "Framework/CommonResources.h"



// コンストラクタ
Fade::Fade()
	:
    m_textureSizeW(1280),
    m_textureSizeH(720),
    m_isActive(false),
    m_duration{},
    m_curentRuleProgress{},
    m_curentTime{},
    m_startProgress{},
    m_endProgress{},
    m_future{}
{
    m_commonResources = CommonResources::GetInstance();
}

void Fade::Initialize()
{
    
    auto commonResources = CommonResources::GetInstance();

    commonResources->GetRenderManager()->AddSprite(this);

    m_sceneManager = commonResources->GetSceneManager();

    // Transformの作成
    m_transform = std::make_unique<Transform>();

    // マテリアルの作成
    m_spriteMaterial = std::make_unique<SpriteMaterial>(
        commonResources->GetDeviceResources()->GetD3DDevice(), commonResources->GetDeviceResources()->GetD3DDeviceContext());

    // 定数バッファを設定
    m_spriteMaterial->SetConstBuffer<ConstBuffer>();

    // シェーダーを設定
    m_spriteMaterial->SetVertexShader  (commonResources->GetResources()->GetUI_VS());
    m_spriteMaterial->SetGeometryShader(commonResources->GetResources()->GetUI_GS());
    m_spriteMaterial->SetPixelShader   (commonResources->GetResources()->GetUI_PS());

    int width, height;

    // 画像をロード
    m_spriteMaterial->SetTexture(commonResources->GetResources()->GetTitleLogo(), width, height);

    m_spriteMaterial->SetRuleTexture(commonResources->GetResources()->GetRuleTexture());

    m_constBuffer.windowSize = { 1280.0f,720.0f };
    m_constBuffer.textureSize = { (float)width,(float)height };
    m_constBuffer.useTexture = 0;
    m_constBuffer.useRuleTexture = 1;
    m_constBuffer.ruleProgress = 0.0f;
    m_constBuffer.ruleInverse = 0;

    m_transform->SetLocalPosition({ 1280.0f / 2.0f, 720.0f / 2.0f,0.0f });

    m_vertexBuffer.position = DirectX::SimpleMath::Vector4(
        m_transform->GetLocalPosition().x,
        m_transform->GetLocalPosition().y,
        m_transform->GetLocalPosition().z,
        1.0f
    );
    m_vertexBuffer.scale = DirectX::SimpleMath::Vector3::One;

    m_vertexBuffer.color = DirectX::SimpleMath::Vector4::One;

    m_vertexBuffer.rect = { 0.0f , 0.0f , (float)width,(float)height };

    m_vertexBuffer.rotate = DirectX::SimpleMath::Vector3::Zero;

    // 定数バッファの更新をする
    //m_spriteMaterial->UpdateConstBuffer<ConstBuffer>(m_constBuffer, 0);

    m_spriteMaterial->SetVertexBuffer(m_vertexBuffer);

    m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);    
}



// 更新処理
void Fade::Update()
{
    // フレーム
    float elapseTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

    if (!m_isActive) return;

    // 経過時間を更新
    m_curentTime += elapseTime;

    // 線形補間を使用して音量を更新
    float t = m_curentTime / m_duration; // 0.0f～1.0f の範囲
    t = std::min(t, 1.0f); // tが1を超えないように制限

    // 現在の進行度を更新
    m_curentRuleProgress = m_startProgress + t * (m_endProgress - m_startProgress);
    // 現在の進行度を更新する
    m_constBuffer.ruleProgress = m_curentRuleProgress;

    // フェードが終了したら
    if (m_curentTime >= 1.0f) {
        m_curentRuleProgress = m_endProgress;
        // 最終音量を設定
        m_constBuffer.ruleProgress = m_curentRuleProgress;

        // フェードアウトの時
        if (m_endProgress == 1.0f)
        {
            // 次のシーンに遷移する
            m_sceneManager->ChageScene();
        }
        // パラメーターの初期化
        m_startProgress = 0.0f;
        m_endProgress = 0.0f;
        m_curentRuleProgress = 0.0f;
        m_curentTime = 0.0f;
        
        // フェードを非アクティブ
        m_isActive = false;
    }

    m_spriteMaterial->UpdateConstBuffer<ConstBuffer>(m_constBuffer, 0);
}

// フェードイン処理
void Fade::FadeIN(float duration)
{
    // フェード処理中なら true を返す
    if (m_isActive) return;

    // フェード時間を設定
    m_duration = duration;

    // ルール画像の進行度を初期化
    m_constBuffer.ruleProgress = 1.0f;
    // ルール画像の反転をしない
    m_constBuffer.ruleInverse = 0;

    // スタート進行度
    m_startProgress = 1.0f;
    // エンド進行度
    m_endProgress = 0.0f;

    // フェード処理をアクティブにする
    m_isActive = true;
}
