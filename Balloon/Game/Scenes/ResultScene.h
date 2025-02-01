#pragma once
#include "Interface/IScene.h"
#include "Framework/Graphics.h"
#include "Scenes/SceneManager/SceneManager.h"

class IScene;
class InputManager;
class SceneManager;

class ResultScene : public IScene
{

public:
	// コンストラクタ
	ResultScene(SceneManager* scene_manager);
	// デストラクタ
	~ResultScene() override = default;


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

	// シーンマネージャー
	SceneManager* m_scene_manager;
	// インプットマネージャー
	InputManager* m_input_manager;
};