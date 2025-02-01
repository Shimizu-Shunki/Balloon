#pragma once
#include "Interface/IScene.h"
#include "Framework/Graphics.h"
#include "Scenes/SceneManager/SceneManager.h"

class IScene;
class InputManager;
class AudioManager;
class SceneManager;
class TweenManager;
class Sprite2DShader;
class Fade;
class SkySphere;


class TitleScene : public IScene
{

public:
	// コンストラクタ
	TitleScene(SceneManager* scene_manager);
	// デストラクタ
	~TitleScene() override = default;


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
	// オーディオマネージャー
	AudioManager* m_audioManager;
	// Tweenマネージャー
	TweenManager* m_tweenManager;

	// スカイスフィア
	std::unique_ptr<SkySphere> m_skySphere;

	// タイトルロゴ
	std::unique_ptr<Sprite2DShader> m_titleLogo;
	// Startテキスト
	std::unique_ptr<Sprite2DShader> m_spaceKey;
	// Startテキスト
	std::unique_ptr<Sprite2DShader> m_startText;

	// フェード
	std::unique_ptr<Fade> m_fade;

	DirectX::SimpleMath::Vector3 m_position;


	
};