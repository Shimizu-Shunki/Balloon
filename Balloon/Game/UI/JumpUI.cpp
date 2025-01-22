#include "pch.h"
#include "Game/Player/Jump.h"
#include "Shader/2DSpriteShader/Sprite2DShader.h"

Jump::Jump()
{

}


void Jump::Initialize()
{
    // マテリアルの作成
    m_jumpMaterial = std::make_unique<Sprite2DShader>();
    m_hpBarMaterial = std::make_unique<Sprite2DShader>();

    // マテリアル初期化
    m_jumpMaterial->Initialize({ 20.0f , 60.0f ,0.0f }, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.5f ,
        L"Resources/Shaders/UI_PS.cso");
    // マテリアル初期化
    m_hpBarMaterial->Initialize({ 72.0f , 78.0f ,0.0f }, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.45f + DirectX::SimpleMath::Vector3::Up * 0.2f,
        L"Resources/Shaders/UI_PS.cso");


    // テクスチャをロードする
    m_jumpMaterial->LoadTexture(L"Resources\\Textures\\JumpFrameUI.png", 1);
    m_hpBarMaterial->LoadTexture(L"Resources\\Textures\\JumpBar.png", 1);

    m_hpBarMaterial->SetReversed(0);
    m_hpBarMaterial->SetRuleActive(true);
    m_hpBarMaterial->SetRuleProgress(1.0f);
    m_hpBarMaterial->SetTexActive(1);


    // 回復時間初期化
    recoveryRate = 0.5f;
    // クールダウン状態初期化
    isCooldown = false;
    currentJumps = 10;
    cooldownTime = 3.0f;
}


void Jump::Update(const float& elapsedTime)
{

    m_hpBarMaterial->SetRect(
        { 0.0f,0.0f, 
        100.0f * currentJumps ,50.0f }
    );
    m_hpBarMaterial->SetRenderSize( 100.0f * currentJumps , 50.0f);

    // クールタイム処理中
    if (isCooldown) {
        elapsedTimeSinceLastJump += elapsedTime;

        // クールダウンが終了した場合
        if (elapsedTimeSinceLastJump >= cooldownTime) {
            // クールダウン終了
            isCooldown = false;
            // 回復時間をリセット
            elapsedTimeSinceLastJump = 0.0f; 
        }
        return;
    }

    // クールダウンが終了して回復処理に移行
    if (currentJumps < MAX_JUMPS) {
        elapsedTimeSinceLastJump += elapsedTime;
        // 回復時間に応じて回復を行う
        if (elapsedTimeSinceLastJump >= recoveryRate) {
            ++currentJumps;
            // 回復時間をリセット
            elapsedTimeSinceLastJump = 0.0f; 
        }
    }
}

void Jump::Render()
{
    // UIを描画させる
    m_jumpMaterial->Render();

   m_hpBarMaterial->Render();
}

float Jump::TryJump(const float& elapsedTime)
{
    if (currentJumps > 0) {
        --currentJumps;
       
        // ジャンプ処理
        // ジャンプ処理を行う
        float vecY = 300.0f * elapsedTime;

        // クールダウンをリスタート
        isCooldown = true;
        elapsedTimeSinceLastJump = 0.0f;

        return vecY;
    }

    return 0.0f;
}


void Jump::DebugRender()
{
    ImGui::Begin("Jump");
    ImGui::DragInt("JumpIndex", &currentJumps);
    ImGui::End();
}