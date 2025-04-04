#pragma once
#include "Interface/IScene.h"


class CommonResources;
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
	// シーンのステートを変更する
	void ChangeState(IState* newState) override;
	// 当たり判定メッセージを受け取る
	void OnSceneMessegeAccepted(Message::SceneMessageID messageID) override;

private:

	// 共有リソース
	CommonResources* m_commonResources;

	// フェード処理
	std::unique_ptr<Fade> m_fade;

	// 現在のステート
	IState* m_currentState;
	// 各ステート
	std::unique_ptr<IState> m_fadeInState;
	std::unique_ptr<IState> m_fadeOutState;
	std::unique_ptr<IState> m_gameClearMainState;
};