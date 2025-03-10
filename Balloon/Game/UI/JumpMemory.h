#pragma once
#include "Interface/ISprite.h"
#include "Game/Material/Buffers.h"


class JumpMemory : public ISprite
{
public:
	// Transformを取得する
	Transform* GetTransform() const { return m_transform.get(); }
	// マテリアルを取得する
	SpriteMaterial* GetSpriteMaterial() const { return m_spriteMaterial.get(); }

	void GetTexSize(float& sizeW, float& sizeH) { sizeW = m_texSizeW; sizeH = m_texSizeH; }

	void SetRect(DirectX::SimpleMath::Vector4 rect) {m_vertexBuffer.rect = rect;}

public:

	// コンストラクタ
	JumpMemory();
	// デストラクタ
	~JumpMemory() override = default;

	// 初期化
	void Initialize();
	// 更新処理
	void Update();

	void Begin() override { m_spriteMaterial->Begin(); }

	void End() override { m_spriteMaterial->End(); }

private:

	// Transform
	std::unique_ptr<Transform> m_transform;

	float m_texSizeW, m_texSizeH;

	// マテリアル
	std::unique_ptr<SpriteMaterial> m_spriteMaterial;

	// 頂点バッファ
	VertexBuffer m_vertexBuffer;
	// 定数バッファ
	ConstBuffer m_constBuffer;
};