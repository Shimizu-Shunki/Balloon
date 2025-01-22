#include "Framework/pch.h"
#include "Framework/Graphics.h"
#include "Framework/Microsoft/DebugDraw.h"


std::unique_ptr<Graphics> Graphics::m_graphics = nullptr;

// グラフィックスのインスタンスを取得する
Graphics* const Graphics::GetInstance()
{
	if (m_graphics == nullptr)
	{
		// グラフィックスのインスタンスを生成する
		m_graphics.reset(new Graphics());
	}
	// グラフィックスのインスタンスを返す
	return m_graphics.get();
}

// コンストラクタ
Graphics::Graphics()
	:
	m_screenW(0),
	m_screenH(0),
	m_device_resources{},
	m_common_states{},
	m_sprite_batch{},
	m_sprite_font{},
	m_basic_effect{},
	m_primitive_batch_color{},
	m_primitive_batch_position{},
	m_primitive_batch_texture{},
	m_effect_factory{},
	m_rasterrizer_state{},
	m_input_layout{},
	m_device{},
	m_context{},
	m_view{},
	m_projection{}
{
	// デバイスリソースのインスタンスを生成する
	m_device_resources = std::make_unique<DX::DeviceResources>(
		DXGI_FORMAT_B8G8R8A8_UNORM,     // バックバッファのフォーマットを指定する
		DXGI_FORMAT_D24_UNORM_S8_UINT   // ステンシルバッファを使用する
	);
}

// デストラクタ
Graphics::~Graphics()
{
}

// 初期化する
void Graphics::Initialize(HWND window)
{
	// デバイスを取得する
	m_device = m_device_resources->GetD3DDevice();
	// デバイスコンテキストを取得する
	m_context = m_device_resources->GetD3DDeviceContext();

	// コモンステートを生成する
	m_common_states = std::make_unique<DirectX::CommonStates>(m_device);
	// スプライトバッチを生成する
	m_sprite_batch = std::make_unique<DirectX::SpriteBatch>(m_context);
	// ベーシックエフェクトを生成する
	m_basic_effect = std::make_unique<DirectX::BasicEffect>(m_device);
	// スプライトフォントを生成する
	m_sprite_font = std::make_unique<DirectX::SpriteFont>(m_device, L"resources\\font\\SegoeUI_18.spritefont");
	// プリミティブバッチを生成する
	m_primitive_batch_color = std::make_unique<DirectX::PrimitiveBatch
		<DirectX::VertexPositionColor>>(m_context);
	m_primitive_batch_position = std::make_unique<DirectX::PrimitiveBatch
		<DirectX::VertexPosition>>(m_context);
	m_primitive_batch_texture = std::make_unique<DirectX::PrimitiveBatch
		<DirectX::VertexPositionColorTexture>>(m_context);
	// 頂点カラーを有効にする
	m_basic_effect->SetVertexColorEnabled(true);
	// テクスチャを無効にする
	m_basic_effect->SetTextureEnabled(false);
	void const* shaderByteCode;
	size_t byteCodeLength;
	// 頂点シェーダーを取得する
	m_basic_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	// 入力レイアウトを生成する
	m_device->CreateInputLayout(
		DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_input_layout.ReleaseAndGetAddressOf()
	);
	// ラスタライザーディスクリプション
	CD3D11_RASTERIZER_DESC rasterizerStateDesc(
		D3D11_FILL_SOLID, D3D11_CULL_NONE,
		FALSE,
		D3D11_DEFAULT_DEPTH_BIAS, D3D11_DEFAULT_DEPTH_BIAS_CLAMP,
		D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS, TRUE,
		FALSE,
		FALSE,
		TRUE
	);
	// ラスタライズステートを生成する
	m_device->CreateRasterizerState(&rasterizerStateDesc, m_rasterrizer_state.ReleaseAndGetAddressOf());
	// エフェクトファクトリを生成する
	m_effect_factory = std::make_unique<DirectX::EffectFactory>(m_device);
}

// 文字列を描画する
void Graphics::DrawString(const float& x, const float& y, const wchar_t* str)
{
	// 文字列を描画する
	m_sprite_font->DrawString(m_sprite_batch.get(), str, DirectX::SimpleMath::Vector2(x, y));
}

// プリミティブ描画を開始する
void Graphics::DrawPrimitiveBegin(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	// ブレンディング状態を設定する
	//m_context->OMSetBlendState(m_common_states->Opaque(), nullptr, 0xFFFFFFFF);
	// 深度ステンシル状態を設定する
	//m_context->OMSetDepthStencilState(m_common_states->DepthNone(), 0);
	// カリングを行わない
	//m_context->RSSetState(m_common_states->CullNone());
	// ラスタライザー状態を設定する
	//m_context->RSSetState(m_rasterrizer_state.Get());

	// ビュー行列を設定する
	m_basic_effect->SetView(view);
	// プロジェクション行列を設定する
	m_basic_effect->SetProjection(projection);
	// ワールド行列を設定する
	m_basic_effect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	// コンテキストを設定する
	m_basic_effect->Apply(m_context);
	// 入力レイアウトを設定する
	m_context->IASetInputLayout(m_input_layout.Get());
	// プリミティブバッチを開始する
	m_primitive_batch_color->Begin();
}

// 描画プリミティブを終了する
void Graphics::DrawPrimitiveEnd()
{
	// プリミティブバッチを終了する
	m_primitive_batch_color->End();
}

// 線分を描画する(XZ平面)
void Graphics::DrawLine(const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& vector, const DirectX::FXMVECTOR& color)
{
	// 頂点カラーを設定する
	DirectX::VertexPositionColor vertex[2] =
	{
		{ DirectX::SimpleMath::Vector3(position.x, 0.0f, position.y), color },
		{ DirectX::SimpleMath::Vector3(position.x + vector.x, 0.0f, position.y + vector.y), color }
	};
	// 線分を描画する
	m_primitive_batch_color->DrawLine(vertex[0], vertex[1]);
}

// 線分を描画する
void Graphics::DrawLine(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& vector, const DirectX::FXMVECTOR& color)
{
	// 頂点カラーを設定する
	DirectX::VertexPositionColor vertex[2] =
	{
		{ DirectX::SimpleMath::Vector3(position.x, position.y, position.z), color },
		{ DirectX::SimpleMath::Vector3(position.x + vector.x, position.y + vector.y, position.z + vector.z), color }
	};
	// 線分を描画する
	m_primitive_batch_color->DrawLine(vertex[0], vertex[1]);
}

// ベクトルを描画する(XZ平面)
void Graphics::DrawVector(const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& vector, const DirectX::FXMVECTOR& color)
{
	using namespace DirectX::SimpleMath;
	const float cosTheta = cosf(DirectX::XMConvertToRadians(20.0f));
	const float sinTheta = sinf(DirectX::XMConvertToRadians(20.0f));

	// 矢印のベクトルのサイズを設定する
	Vector2 arrow = -vector;
	// 正規化する
	arrow.Normalize();
	// 矢印のサイズを設定する
	arrow *= 3.0f;
	// 右矢 X: (xcosθ- ysinθ)  Y: (xsinθ+ ycosθ)
	Vector2 arrowR = Vector2(arrow.x * cosTheta - arrow.y * sinTheta, arrow.x * sinTheta + arrow.y * cosTheta);
	// 左矢 X: (xcosθ- ysinθ)  Y: (xsinθ+ ycosθ)
	Vector2 arrowL = Vector2(arrow.x * cosTheta + arrow.y * sinTheta, -arrow.x * sinTheta + arrow.y * cosTheta);
	// 線分を描画する
	DrawLine(position, vector, color);
	// 右矢を描画する
	DrawLine(position + vector, arrowR, color);
	// 左矢を描画する
	DrawLine(position + vector, arrowL, color);
}

// ベクトルを描画する
void Graphics::DrawVector(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& vector, const DirectX::FXMVECTOR& color)
{
	using namespace DirectX::SimpleMath;
	const float cosTheta = cosf(DirectX::XMConvertToRadians(20.0f));
	const float sinTheta = sinf(DirectX::XMConvertToRadians(20.0f));

	// 矢印のベクトルのサイズを設定する
	Vector3 arrow = -vector;
	// 正規化する
	arrow.Normalize();
	// 矢印のサイズを設定する
	arrow *= 3.0f;
	// 右矢 X: (xcosθ- zsinθ)  Z: (xsinθ+ zcosθ)
	Vector3 arrowR = Vector3(arrow.x * cosTheta - arrow.z * sinTheta, arrow.y, arrow.x * sinTheta + arrow.z * cosTheta);
	// 左矢 X: (xcosθ- zsinθ)  Z: (xsinθ+ zcosθ)
	Vector3 arrowL = Vector3(arrow.x * cosTheta + arrow.z * sinTheta, arrow.y, -arrow.x * sinTheta + arrow.z * cosTheta);
	// 線分を描画する
	DrawLine(position, vector, color);
	// 右矢を描画する
	DrawLine(position + vector, arrowR, color);
	// 左矢を描画する
	DrawLine(position + vector, arrowL, color);
}

// 円を描画する(XZ平面)
void Graphics::DrawCircle(const DirectX::SimpleMath::Vector2& center, const float& radius, const DirectX::FXMVECTOR& color, const int& split)
{
	using namespace DirectX::SimpleMath;

	// 角度を初期化する
	float angle = 0.0f;
	// 始点を宣言する
	Vector2 position1 = center + Vector2(cosf(angle), sinf(angle)) * radius;
	for (int index = 0; index < split; index++)
	{
		// 始点を設定する
		Vector2 position0 = position1;
		// 角度を計算する
		angle += DirectX::XM_2PI / (float)split;
		// 終点を計算する
		position1 = center + Vector2(cosf(angle), sinf(angle)) * radius;
		// 円を描画する
		DrawLine(position0, position1 - position0, color);
	}
}

// 円を描画する
void Graphics::DrawCircle(const DirectX::SimpleMath::Vector3& center, const float& radius, const DirectX::FXMVECTOR& color, const int& split)
{
	using namespace DirectX::SimpleMath;

	// 角度を初期化する
	float angle = 0.0f;
	// 終点を計算する
	Vector3 position1 = center + Vector3(cosf(angle), center.y, sinf(angle)) * radius;
	for (int index = 0; index < split; index++)
	{
		// 始点を設定する
		Vector3 position0 = position1;
		// 角度を計算する
		angle += DirectX::XM_2PI / (float)split;
		// 終点を計算する
		position1 = center + Vector3(cosf(angle), center.y, sinf(angle)) * radius;
		// 円を描画する
		DrawLine(position0, position1 - position0, color);
	}
}

// 矩形を描画する
void Graphics::DrawQuad(const DirectX::VertexPositionColor& v1, const DirectX::VertexPositionColor& v2, const DirectX::VertexPositionColor& v3, const DirectX::VertexPositionColor& v4)
{
	// 矩形を描画する
	m_primitive_batch_color->DrawQuad(v1, v2, v3, v4);
}

// 矩形を描画する
void Graphics::DrawQuad(
	const DirectX::FXMVECTOR& point1,
	const DirectX::FXMVECTOR& point2,
	const DirectX::FXMVECTOR& point3,
	const DirectX::FXMVECTOR& point4,
	const DirectX::HXMVECTOR& color
)
{
	DirectX::VertexPositionColor vertexs[5];
	DirectX::XMStoreFloat3(&vertexs[0].position, point1);
	DirectX::XMStoreFloat3(&vertexs[1].position, point2);
	DirectX::XMStoreFloat3(&vertexs[2].position, point3);
	DirectX::XMStoreFloat3(&vertexs[3].position, point4);
	DirectX::XMStoreFloat3(&vertexs[4].position, point1);

	XMStoreFloat4(&vertexs[0].color, color);
	XMStoreFloat4(&vertexs[1].color, color);
	XMStoreFloat4(&vertexs[2].color, color);
	XMStoreFloat4(&vertexs[3].color, color);
	XMStoreFloat4(&vertexs[4].color, color);

	m_primitive_batch_color->Draw(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, vertexs, 5);
}

// グリット床を描画
void Graphics::DrawGridFloor(
	DirectX::SimpleMath::Vector3 width,
	DirectX::SimpleMath::Vector3 height,
	size_t dive
)
{
	DX::DrawGrid(m_primitive_batch_color.get(),
		width,                              // 横軸
		height,                             // 縦軸
		DirectX::SimpleMath::Vector3::Zero, // 原点
		dive,                               // 横分割数
		dive                                // 縦分割数
	);
}

// モデルを描画する
void Graphics::DrawModel(const DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection, const bool& depthBuffer)
{
	if (depthBuffer)
	{

		// モデルを描画する
		model->Draw(m_context, *m_common_states.get(), world, view, projection, false);
	}
	else
	{
		// モデルを描画する
		model->Draw(m_context, *m_common_states.get(), world, view, projection, false,
			[&]() { 	m_context->OMSetDepthStencilState(m_common_states->DepthNone(), 0); }
		);
	}
}