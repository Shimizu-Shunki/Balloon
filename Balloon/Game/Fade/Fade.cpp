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
    // 共有リソースのインスタンスを取得する
    m_commonResources = CommonResources::GetInstance();
    // コンテキストを取得する
    m_context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// フェード用のスプライトを作成
	m_spriteMaterial = std::make_unique<SpriteMaterial>(
        m_commonResources->GetDeviceResources()->GetD3DDevice(),
        m_commonResources->GetDeviceResources()->GetD3DDeviceContext());

    // シェーダーをロードする
    // 頂点シェーダー
    m_spriteMaterial->LoadVertexShader(L"Resources\\Shaders\\cso\\UI_VS.cso");
    // ジオメトリシェーダー
    m_spriteMaterial->LoadGeometryShader(L"Resources\\Shaders\\cso\\UI_GS.cso");
    // ピクセルシェーダー
    m_spriteMaterial->LoadPixelShader(L"Resources\\Shaders\\cso\\UI_PS.cso");

    // テクスチャをロードする
    m_spriteMaterial->LoadTexture(m_commonResources->GetResources()->GetTitleLogo(), m_textureSizeW, m_textureSizeH);
    // ルール画像をロード
    m_spriteMaterial->LoadRuleTexture(m_commonResources->GetResources()->GetTitleLogo());

    // バッファの初期化
    m_constBuffer.windowSize = { (float)m_textureSizeW,(float)m_textureSizeH };
    // 真っ黒のテクスチャとして利用するため無効化する
    m_constBuffer.useTexture = 0;
    // ルール画像を使用する
    m_constBuffer.useRuleTexture = 1;
    // ルール反転しない
    m_constBuffer.ruleInverse = 0;
    // ルール画像の進行度初期化
    m_constBuffer.ruleProgress = 0;
}

// デストラクタ
Fade::~Fade()
{

}

// 更新処理
void Fade::Update()
{
    // フレーム
    float elapseTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

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


void Fade::Render()
{
    if (!m_isActive) return;
    // 描画準備
    m_spriteMaterial->Begin();
    // 描画
    m_context->Draw(1, 0);
    // 描画終了処理
    m_spriteMaterial->End();
}