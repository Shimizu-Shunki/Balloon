#pragma once
#include "Game/Material/Buffers.h"
#include "Interface/IMaterial.h"

class IMaterial;
class Resources;

class BalloonMaterial : public IMaterial
{
public:
	// ベースカラーを設定
	void SetBaseColor(const DirectX::SimpleMath::Vector4& color) { m_PBRLitconstantBuffer.baseColor = color; }
	// 金属値を設定
	void SetMatallic(float matallic) { m_PBRLitconstantBuffer.matallic = matallic; }
	// 粗さを設定
	void SetSmoothness(float smoothness) { m_PBRLitconstantBuffer.smoothness = smoothness; }
	// ベースマップを使用するか設定
	void SetUseBaseMap(float active) { m_PBRLitconstantBuffer.useBaseMap = active; }
	// 法線マップを使用するか設定
	void SetUseNormalMap(float active) { m_PBRLitconstantBuffer.useNormalMap = active; }

	// ベースマップを設定する
	void SetBaseMap(ID3D11ShaderResourceView* baseMap) { m_baseMap = baseMap; }
	// ノーマルマップを設定する
	void SetNormalMap(ID3D11ShaderResourceView* normalMap) { m_normalMap = normalMap; }
	// 環境マップを設定
	void SetSkyMap(ID3D11ShaderResourceView* skyMap) { m_skyMap = skyMap; }

public:
	// コンストラクタ
	BalloonMaterial();
	// デストラクタ
	~BalloonMaterial() = default;

	void Initialize(Resources* resources);

	void BeginMaterial() override;

	void EndMaterial() override;

	void UpdateConstBuffer() override;

private:

	// インプットレイアウト
	ID3D11InputLayout* m_inputLayout;

	ID3D11DeviceContext1* m_context;

	DirectX::CommonStates* m_states;

	// シェーダー
	// 頂点シェーダー
	ID3D11VertexShader* m_vertexShader;
	// ピクセルシェーダー
	ID3D11PixelShader* m_pixelShader;

	// 定数バッファ
	PBRLitConstantBuffer m_PBRLitconstantBuffer;
	// 定数バッファ用のバッファオブジェクト
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	// メインテクスチャ
	ID3D11ShaderResourceView* m_baseMap;
	// ノーマルマップ
	ID3D11ShaderResourceView* m_normalMap;
	// 環境マップ
	ID3D11ShaderResourceView* m_skyMap;
};