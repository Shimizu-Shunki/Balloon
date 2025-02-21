#pragma once
#include "Buffers.h"

class SpriteMaterial
{
public:
	// 頂点バッファを設定する
	void SetVertexBuffer(const VertexBuffer& vertexBuffer) { m_vertexBuffer = vertexBuffer; }
	// 頂点シェーダーを設定
	void SetVertexShader(ID3D11VertexShader* vertexShader) { m_vertexShader = vertexShader; }
	// ジオメトリシェーダーを設定
	void SetGeometryShader(ID3D11GeometryShader* geometryShader) { m_geometryShader = geometryShader; }
	// ピクセルシェーダーを設定
	void SetPixelShader(ID3D11PixelShader* pixelShader) { m_pixelShader = pixelShader; }

private:
	// スクリーンサイズ
	const float SCREEN_WIDTH = 1280.0f;
	const float SCREEN_HEIGHT = 720.0f;

public:
	// コンストラクタ
	SpriteMaterial(ID3D11Device1* device , ID3D11DeviceContext1* context);
	// デストラクタ
	~SpriteMaterial();

	// 定数バッファの追加
	template <typename T>
	void SetConstBuffer()
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

		// シェーダーにデータを渡すためのコンスタントバッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(T);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		m_device->CreateBuffer(&bd, nullptr, &buffer);

		// バッファを更新
		m_cBuffers.push_back(std::move(buffer));
	}

	// バッファを更新する
	template <typename T>
	void UpdateConstBuffer(T buffer,int index)
	{
		// 定数バッファのデータを更新
		m_context->UpdateSubresource(m_cBuffers[index].Get(), 0, NULL, &buffer, 0, 0);
	}

	// テクスチャを設定
	void SetTexture(ID3D11ShaderResourceView* texture, int& width, int& height);
	// ルール画像を設定
	void SetRuleTexture(ID3D11ShaderResourceView* texture);

	// 全てをセットする描画準備
	void Begin();
	// 終了処理　解放
	void End();

private:
	// デバイス
	ID3D11Device1* m_device;
	// コンテキスト
	ID3D11DeviceContext1* m_context;

	// 共通のバッファ
	// 頂点バッファ
	VertexBuffer m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vBuffer;
	// 定数バッファ
	std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> m_cBuffers;

	// テクスチャ
	ID3D11ShaderResourceView* m_texture;
	// ルールテクスチャ
	ID3D11ShaderResourceView* m_ruleTexture;

	// 頂点シェーダー
	ID3D11VertexShader*   m_vertexShader;
	// ジオメトリシェーダー
	ID3D11GeometryShader* m_geometryShader;
	// ピクセルシェーダー
	ID3D11PixelShader*    m_pixelShader;
};