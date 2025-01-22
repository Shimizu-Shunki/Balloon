#pragma once

class Graphics;
class Sprite2DShader;

class Countdown
{
public:

	// コンストラクタ
	Countdown();
	// デストラクタ
	~Countdown();


public:
	// 初期化
	void Initialize();
	// 更新処理
	bool Update(const float& elapsedTime);
	// 描画処理
	void Render();

private:

	// グラフィック
	Graphics* m_graphics;
	// 2Dマテリアル
	std::unique_ptr<Sprite2DShader> m_FrameMaterial;
	std::unique_ptr<Sprite2DShader> m_ReadyMaterial;
	std::unique_ptr<Sprite2DShader> m_GoMaterial;

	float m_angle;

	// 現在の時間
	float m_currentTime;
	// 数値
	float m_timer;
};