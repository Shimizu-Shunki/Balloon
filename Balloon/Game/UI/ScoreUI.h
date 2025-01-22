#pragma once

class Graphics;
class Sprite2DShader;

class Score
{
public:
	// スコアの値を設定する
	void SetScore(const int score) { m_score = score; }
	// スコアの値を取得する
	int GetScore() const { return m_score; }
	// スコアリセット
	void ResetScore() { m_score = 0; }

public:

	// コンストラクタ
	Score();
	// デストラクタ
	~Score();

public:

	// 初期化
	void Initialize();
	// 描画処理
	void Render();

private:
	// 数値
	int m_score;
	// 2Dマテリアル
	std::unique_ptr<Sprite2DShader> m_scoreMaterial;
};