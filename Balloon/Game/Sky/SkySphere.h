#pragma once

class CommonResources;
class Transform;

class SkySphere
{
public:
	// ターゲットのTransformを設定する
	void SetTargetTransform(Transform* transform) { m_targetTransform = transform; }

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
	

private:
	// 共有リソース
	CommonResources* m_commonResources;

	// モデル
	DirectX::Model* m_model;
	// Transform
	std::unique_ptr<Transform> m_transform;
	// ターゲットTransform
	Transform* m_targetTransform;

};