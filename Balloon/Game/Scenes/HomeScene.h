#pragma once
#include "Interface/IScene.h"
#include "Framework/Graphics.h"
#include "Scenes/SceneManager/SceneManager.h"
#include "Interface/IComponent.h"
#include "Game/Camera/CameraManager.h"
#include "Interface/ICamera.h"

class IScene;
class InputManager;
class DebugCamera;
class CollisionManager;
class TPSCamera;
class Balloon;
class Enemy;
class ICamera;
class CameraManager;

namespace DX
{
	class RenderTexture;
}

class Object;

class HomeScene : public IScene
{

public:
	// コンストラクタ
	HomeScene(SceneManager* scene_manager);
	// デストラクタ
	~HomeScene() override;


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

	// グラフィックス
	Graphics* m_graphics;
	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;
	// TPSカメラ
	std::unique_ptr<TPSCamera> m_tpsCamera;

	// シーンマネージャー
	SceneManager* m_scene_manager;
	// インプットマネージャー
	InputManager* m_input_manager;
	// 当たり判定
	std::unique_ptr<CollisionManager> m_collisionManager;

	// オブジェクトの追加
	std::unique_ptr<IComponent> m_floor;
	// プレイヤー
	std::unique_ptr<IComponent> m_player;
	// 敵
	std::unique_ptr<IComponent> m_enemy;

	// ポストプロセス
	std::unique_ptr<DirectX::BasicPostProcess> m_postProcess;
	// レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	// カメラマネージャー
	std::unique_ptr<CameraManager> m_cameraManager;
};