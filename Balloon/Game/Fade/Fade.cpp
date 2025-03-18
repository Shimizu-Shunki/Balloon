#include "Framework/pch.h"
#include "Game/Fade/Fade.h"
#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"

#include "Framework/CommonResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"


/// <summary>
/// コンストラクタ
/// </summary>
Fade::Fade()
	:
    m_textureSizeW(1280),
    m_textureSizeH(720),
    m_isActive(false),
    m_duration{},
    m_curentRuleProgress{},
    m_curentTime{},
    m_startProgress{},
    m_endProgress{}
{
    // 共有リソースのインスタンスを取得する
    m_commonResources = CommonResources::GetInstance();

    m_sceneManager = CommonResources::GetInstance()->GetSceneManager();
}

/// <summary>
/// 初期化処理
/// </summary>
void Fade::Initialize()
{
    int width, height;

    // Transformの作成
    m_transform = std::make_unique<Transform>();
    // Imageの作成
    m_image = std::make_unique<Image>();
    // Materialの作成
    m_material = std::make_unique<DefaultUi>();

    // Imageの初期化
    m_image->Initialize(true, m_material.get(), m_transform.get());
    m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetTitleLogo(), width, height);
    m_image->SetRuleTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetRuleTexture());
    m_image->SetIsActive(true);

    m_commonResources->GetRenderManager()->AddSprite(m_image.get());

    // Transformの初期化
    m_transform->SetLocalPosition({ 1280.0f / 2.0f , 720.0f / 2.0f , 0.0f });
    m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
    m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
    m_transform->SetRect({ 0.0f,0.0f,(float)width,(float)height });
    m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

    // マテリアルを初期化する
    this->InitialMaterial(width, height);
}

/// <summary>
/// 更新処理
/// </summary>
void Fade::Update()
{
    // フレーム
    float elapseTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

    // フェード中で無ければスキップ
    if (!m_isActive) return;

    auto material = dynamic_cast<DefaultUi*>(m_material.get());

    // 経過時間を更新
    m_curentTime += elapseTime;

    // 線形補間を使用して音量を更新
    float t = m_curentTime / m_duration; // 0.0f～1.0f の範囲
    t = std::min(t, 1.0f); // tが1を超えないように制限

    // 現在の進行度を更新
    m_curentRuleProgress = m_startProgress + t * (m_endProgress - m_startProgress);
    // 現在の進行度を更新する
    material->SetRuleProgress(m_curentRuleProgress);

    // フェードが終了したら
    if (m_curentTime >= 1.0f) {
        m_curentRuleProgress = m_endProgress;
        // 最終音量を設定
        material->SetRuleProgress(m_curentRuleProgress);

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

    // 定数バッファの更新
    material->UpdateConstBuffer();
}

/// <summary>
/// フェードインを行う
/// </summary>
/// <param name="duration">秒数</param>
void Fade::FadeIN(float duration)
{
    // フェード処理中なら true を返す
    if (m_isActive) return;

    // フェード時間を設定
    m_duration = duration;

    auto material = dynamic_cast<DefaultUi*>(m_material.get());

    // ルール画像の進行度を初期化
    material->SetRuleInverse(0.0f);
    // ルール画像の反転設定
    material->SetRuleProgress(0.0f);

    // スタート進行度
    m_startProgress = 1.0f;
    // エンド進行度
    m_endProgress = 0.0f;

    // フェード処理をアクティブにする
    m_isActive = true;

    // 定数バッファの更新
    material->UpdateConstBuffer();
}


/// <summary>
/// マテリアルの初期化
/// </summary>
/// <param name="width">テクスチャサイズ横</param>
/// <param name="height">テクスチャサイズ高さ</param>
void Fade::InitialMaterial(int width, int height)
{
    auto material = dynamic_cast<DefaultUi*>(m_material.get());

    material->SetPixelShader(CommonResources::GetInstance()->GetResources()->GetShaderResources()->GetUI_PS());
    material->SetWindowSize({ 1280.0f,720.0f });
    material->SetTextureSize({ (float)width, (float)height });
    material->SetUseTexture(0.0f);
    material->SetUseRuleTexture(1.0f);
    material->SetRuleProgress(0.0f);
    material->SetRuleInverse(0.0f);
}
