#pragma once
#include "Interface/IScene.h"
#include "Interface/ICamera.h"


class CommonResources;
class IObject;
class Transform;
class DebugCamera;
class StateMachine;
class Fade;
class Jump;
class Enemy;




class PlayScene : public IScene
{
public:
	// コンストラクタ
	PlayScene();
	// デストラクタ
	~PlayScene();

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
	// ステートコントローラーの作成
	void CreateStateStateController();

private:

	// 共有リソース
	CommonResources* m_commonResources;

	// ステートマシーン
	std::unique_ptr<StateMachine> m_stateMachine;

	// フェード処理
	std::unique_ptr<Fade> m_fade;

	std::vector<Enemy*> m_enemys;

	// オブジェクトのルート
	std::vector<std::unique_ptr<IObject>> m_rootObject;
	// Transformのルート
	std::unique_ptr<Transform> m_rootTransform;
	// デバッグカメラで実装
	std::unique_ptr<DebugCamera> m_debugCamera;

	std::unique_ptr<ICamera>  m_camera;
};