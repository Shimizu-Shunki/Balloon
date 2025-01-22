#pragma once

class Graphics;
class Sprite2DShader;

class Timer
{
public:
	// 表示設定をする
	void SetIsActive(bool isActive) { m_isActive = isActive; }

public:

	// コンストラクタ
	Timer();
	// デストラクタ
	~Timer();


public:
	// 初期化
	void Initialize(const bool &isCountingUp , const float &timeLimit);
	// 更新処理
	void Update(const float& elapsedTime);
	// 描画処理
	void Render();

public:
	// リセット処理
	void Reset();

private:

	// グラフィック
	Graphics* m_graphics;
	// 2Dマテリアル
	std::unique_ptr<Sprite2DShader> m_timerMaterial;

	std::unique_ptr<Sprite2DShader> m_timerFrameMaterial;

	std::unique_ptr<Sprite2DShader> m_timerNumberMaterial;

	// 表示するか
	bool m_isActive;

	// タイマーがカウントアップかどうか
	bool m_isCountingUp;


	// 現在の時間
	float m_currentTime;

	// 数値
	float m_timer;
};