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
	void CreateBlendState(ID3D11Device1* device);
	// 深度ステンシルステートの作成
	void CreateDepthStencilState(ID3D11Device1* device);
	// ラスタライザーステートの作成
	void CreateRasterizerState(ID3D11Device1* device);


private:

	CommonResources* m_commonResources;

	// 頂点シェーダー
	ID3D11VertexShader* m_vertexShader;
	// ハルシェーダー
	ID3D11HullShader* m_hullShader;
	// ドメインシェーダー
	ID3D11DomainShader* m_domainShader;
	// ピクセルシェーダー
	ID3D11PixelShader* m_pixelShader;

	// 定数バッファ用のバッファオブジェクト
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	// 入力レイアウト
	ID3D11InputLayout* m_inputLayout;


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
	ID3D11ShaderResourceView* m_texture;

	float m_time;

	float m_index;
};