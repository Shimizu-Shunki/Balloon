#pragma once
#include "Interface/IObject.h"
#include "Interface/IRenderableObject.h"
#include "Game/Buffers/ConstantBuffer.h"
#include "Game/Particle/ParticleEmitter.h"

class CommonResources;
class Particle;
class ParticleEmitter;

class Renderer
{

public:
	// コンストラクタ
	Renderer();
	// デストラクタ
	~Renderer() = default;

	// 描画オブジェクト追加
	void Attach(IObject* object, IRenderableObject* renderableObject);
	void Attach(ParticleEmitter* emitter) { m_particleEmitter.push_back(emitter); }

	// 描画処理
	void Render();

private:

	// パーティクル描画
	void ParticleRender(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix);

private:
	// 共有リソース
	CommonResources* m_commonResources;
	// デバイス
	ID3D11Device1* m_device;
	// コンテキスト
	ID3D11DeviceContext1* m_context;
	// コモンステート
	DirectX::CommonStates* m_commonStates;

	// 描画オブジェクト
	std::unordered_map<IObject*, IRenderableObject*> m_renderableObjects;


	// 定数バッファ
	std::unique_ptr<ConstantBuffer<ParticleConstBuffer>> m_particleConstBuffer;

	std::vector<ParticleEmitter*> m_particleEmitter;

	// インプットレイアウト
	ID3D11InputLayout* m_inputLayout;

	// 頂点シェーダー
	ID3D11VertexShader* m_vertexShader;
	// ジオメトリシェーダー
	ID3D11GeometryShader* m_geometryShader;

	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;

	// ビルボード
	DirectX::SimpleMath::Matrix m_billboardMatrix;

};