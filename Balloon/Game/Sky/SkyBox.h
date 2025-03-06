#pragma once


class SkyBox
{
private:
	struct MatricesConstBuffer
	{
		DirectX::SimpleMath::Matrix worldMatrix;
		DirectX::SimpleMath::Matrix viewMatrix;
		DirectX::SimpleMath::Matrix projectionMatrix;
	};

public:
	// コンストラクタ
	SkyBox();
	// デストラクタ
	~SkyBox() = default;

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(DirectX::SimpleMath::Matrix view , DirectX::SimpleMath::Matrix projection);
	// 描画処理
	void Render();

private:

	// スカイボックスモデル
	std::unique_ptr<DirectX::GeometricPrimitive> m_skyboxModel;
	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_skyInputLayout;
	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader>   m_skyVertexShader;
	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_skyPixelShader;

	// 環境テクスチャ（キューブマップ）
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cubemap;

	// 定数バッファ用のバッファオブジェクト
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
};