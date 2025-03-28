#pragma once
#include "Interface/IScene.h"


class CommonResources;

class StateMachine;
class Fade;

class GameClearScene : public IScene
{
public:
	// コンストラクタ
	GameClearScene();
	// デストラクタ
	~GameClearScene();

public:
	// 初期化処理
	void Initialize() override;
	// スタート処理
	void Start()  override;
	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;
	// 終了処理
	void Finalize() override;

private:

	// 共有リソース
	CommonResources* m_commonResources;
	// ステートマシーン
	std::unique_ptr<StateMachine> m_stateMachine;

	// フェード処理
	std::unique_ptr<Fade> m_fade;



};