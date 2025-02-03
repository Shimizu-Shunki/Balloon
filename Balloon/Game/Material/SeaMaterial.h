#pragma once

class CommonResources;

class SeaMaterial
{
public:

	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4    TessellationFactor;
	};

	// コンストラクタ
	SeaMaterial();
	// デストラクタ
	~SeaMaterial();

public:

	// 初期化処理
	void Initialize();
	// 描画処理
	void Render();

private:
	// ブレンドステートの作成
	void CreateBlendState(ID3D11Device1* device, ID3D11DeviceContext1* context);
	// 深度ステンシルステートの作成
	void CreateDepthStencilState(ID3D11Device1* device, ID3D11DeviceContext1* context);
	// ラスタライザーステートの作成
	void CreateRasterizerState(ID3D11Device1* device, ID3D11DeviceContext1* context);


private:
	//	関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	CommonResources* m_commonResources;

	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// ハルシェーダー
	Microsoft::WRL::ComPtr<ID3D11HullShader> m_hullShader;
	// ドメインシェーダー
	Microsoft::WRL::ComPtr<ID3D11DomainShader> m_domainShader;
	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	// 定数バッファ用のバッファオブジェクト
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	//	コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;

	// ブレンドステート
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;
	// 深度ステンシルステート
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	// ラスタライザーステート
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	float m_time;

	float m_index;
};