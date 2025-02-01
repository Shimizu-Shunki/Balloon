#pragma once
#include "Interface/IScene.h"
#include "Framework/Graphics.h"
#include "Scenes/SceneManager/SceneManager.h"

class IScene;
class IComponent;
class InputManager;
class SceneManager;
class CollisionManager;
class AudioManager;
class SeaMaterial;
class DebugCamera;
class TPSCamera;

class SkySphere;

class Countdown;
class Fade;
class Timer;

class PlayScene : public IScene
{

private:

public:
	// コンストラクタ
	PlayScene(SceneManager* scene_manager);
	// デストラクタ
	~PlayScene() override = default;

	// スタート処理

	// 初期化処理
	void Initialize() override;
	// スタート処理
	void Start() override;
	// 更新処理
	void Update(float elapsed_time) override;
	// 描画処理
	void Render() override;
	// 終了処理
	void Finalize() override;

private:
	// オブジェクトの初期化
	void InitializeObject();
	// フロアの更新処理
	void UpdateFloor(float elapsed_time);

private:

	// グラフィックス
	Graphics* m_graphics;
	// シーンマネージャー
	SceneManager* m_scene_manager;
	// オーディオマネージャー
	AudioManager* m_audioManager;
	// インプットマネージャー
	InputManager* m_input_manager;
	// 当たり判定
	std::unique_ptr<CollisionManager> m_collisionManager;

	// カメラ
	// TPSカメラ
	std::unique_ptr<TPSCamera> m_tpsCamera;
	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;

	// スカイスフィア
	std::unique_ptr<SkySphere> m_skySphere;

	// オブジェクトの追加
	std::unique_ptr<IComponent> m_floorPlayerStart;
	std::unique_ptr<IComponent> m_floorLeftUp;
	std::unique_ptr<IComponent> m_floorRightUp;
	std::unique_ptr<IComponent> m_floorLeftDown;
	std::unique_ptr<IComponent> m_floorRightDown;

	// プレイヤー
	std::unique_ptr<IComponent> m_player;
	// 敵
	std::unique_ptr<IComponent> m_enemy;

	// UI
	// フェード
	std::unique_ptr<Fade> m_fade;
	// タイマー
	std::unique_ptr<Timer> m_timer;
	// カウントダウン
	std::unique_ptr<Countdown> m_countdown;

	// 海
	std::unique_ptr<SeaMaterial> m_SeaMaterial;

	bool m_isFade;
};