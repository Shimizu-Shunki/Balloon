#pragma once
#include "Game/UI/JumpMemory.h"
#include "Game/UI/JumpFrame.h"
#include "Interface/ISprite.h"


class JumpFrame;
class JumpMemory;
class CommonResources;
class IObject;
class PhysicsBody;

class Jump
{
private:
	// 最大ジャンプ回数
	const int MAX_JUMPS = 10;
public:
	// コンストラクタ
	Jump(PhysicsBody* physicBody);
	// デストラクタ
	~Jump() = default;

public:

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update();
	// ジャンプ処理
	float TryJump();

private:

	// 共有リソース
	CommonResources* m_commonResources;

	// 対象オブジェクト
	IObject* m_object;

	PhysicsBody* m_physicBody;

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

	// ジャンプフレーム
	std::unique_ptr<ISprite> m_jumpFrame;
	// ジャンプメモリ
	std::unique_ptr<ISprite> m_jumpMemory;
};