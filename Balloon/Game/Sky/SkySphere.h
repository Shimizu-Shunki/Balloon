#pragma once

class CommonResources;
class Transform;

class SkySphere
{
private:
	// スピート
	static const float ROTATION_SPEED;

public:
	// コンストラクタ
	SkySphere();
	// デストラクタ
	~SkySphere() = default;

	// 初期化
	void Initialize();
	// 更新処理
	void Update();
	// 描画処理
	void Render();

private:
	// 共有リソース
	CommonResources* m_commonResources;

	// コンテキスト
	ID3D11DeviceContext1* m_context;

	// モデル
	DirectX::Model* m_model;
	// Transform
	std::unique_ptr<Transform> m_transform;

};