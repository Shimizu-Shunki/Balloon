#pragma once


class IMaterial;
class Transform;

class Image
{
public:
	// 状態を設定する
	void SetIsActive(bool isActive) { m_isActive = isActive; }
	// 状態を取得する
	bool GetIsActive() { return m_isActive; }

	IMaterial* GetMaterial() { return m_material; }

	// メインのテクスチャを設定する
	void SetTexture(ID3D11ShaderResourceView* texture, int& width, int& height);
	// ルールテクスチャを設定する
	void SetRuleTexture(ID3D11ShaderResourceView* ruleTexture) { m_ruleTexture = ruleTexture; }

public:
	// コンストラクタ
	Image();
	// デストラクタ
	~Image() = default;

	// 初期化処理
	void Initialize(bool isActive, IMaterial* material, Transform* transform);
	// 描画処理
	IMaterial* Render(ID3D11DeviceContext1* context, ID3D11Buffer* vertexBuffer);


private:
	// 状態設定
	bool m_isActive;

	// マテリアル
	IMaterial* m_material;
	// トランスフォーム
	Transform* m_transform;
	
	// メインテクスチャ
	ID3D11ShaderResourceView* m_texture;
	// ルールテクスチャ
	ID3D11ShaderResourceView* m_ruleTexture;
};