#pragma once
#include "Shader/2DSpriteShader/Sprite2DShader.h"

class Sprite2DShader;

class Jump
{
private:
    // 最大ジャンプ回数
    const int MAX_JUMPS = 10;


public:
    // コンストラクタ
    Jump();
    // デストラクタ
    ~Jump() = default;


public:
    // 初期化処理
    void Initialize();
    // 更新処理
    void Update(const float& elapsedTime);
    // 描画処理
    void Render();
    // ジャンプ処理
    float TryJump(const float& elapsedTime);

    void DebugRender();

private: 

    // 2Dマテリアル HPUI
    std::unique_ptr<Sprite2DShader> m_jumpMaterial;
    // 2Dマテリアル HPBarUI
    std::unique_ptr<Sprite2DShader> m_hpBarMaterial;

    // 現在のジャンプ回数
    int currentJumps;
    // クールダウン時間（秒）
    float cooldownTime;
    // 1回復ごとの時間（秒）
    float recoveryRate;   
    // 最後のジャンプからの経過時間
    float elapsedTimeSinceLastJump;
    // クールダウン中かどうか
    bool isCooldown;               

};