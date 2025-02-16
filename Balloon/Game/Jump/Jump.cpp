#include "Framework/pch.h"
#include "Game/Jump/Jump.h"
#include "Framework/CommonResources.h"
#include "Game/UI/JumpFrame.h"
#include "Game/UI/JumpMemory.h"
#include "Game/PhysicsBody/PhysicsBody.h"

Jump::Jump(PhysicsBody* physicBody)
{
    // 共有リソースのインスタンスを取得する
    m_commonResources = CommonResources::GetInstance();
    // オブジェクトを取得
    /*m_object = object;*/
    m_physicBody = physicBody;
}

void Jump::Initialize()
{
    // スプライト作成
    m_jumpFrame = std::make_unique<JumpFrame>();
    m_jumpFrame->Initialize();
    m_jumpMemory = std::make_unique<JumpMemory>();
    m_jumpMemory->Initialize();

    // 回復時間初期化
    recoveryRate = 0.5f;
    // クールダウン状態初期化
    isCooldown = false;
    currentJumps = 10000;
    cooldownTime = 3.0f;
}

void Jump::Update()
{
    float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();
   
    if (m_commonResources->GetInputManager()->OnKeyDown(InputManager::Keys::Space))
    {
        this->TryJump();
    }

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

float Jump::TryJump()
{
    float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();
    
    if (currentJumps > 0) {
        --currentJumps;

        // ジャンプ処理
        // ジャンプ処理を行う
        float vecY = 300.0f * elapsedTime;

        DirectX::SimpleMath::Vector3 jampFoce = { 0.0f , 1000.0f , 0.0f };

        m_physicBody->SetFoce(m_physicBody->GetFoce() + jampFoce);

        // クールダウンをリスタート
        isCooldown = true;
        elapsedTimeSinceLastJump = 0.0f;

        return vecY;
    }

    return 0.0f;
}