#include "pch.h"
#include "Framework/Renderer.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Interface/IRenderableObject.h"
#include "Game/Particle/Particle.h"
#include "Game/Particle/ParticleEmitter.h"

Renderer::Renderer()
{
	m_commonResources = CommonResources::GetInstance();
	m_device          = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	m_context         = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	m_commonStates    = CommonResources::GetInstance()->GetCommonStates();


	m_particleConstBuffer = std::make_unique<ConstantBuffer<ParticleConstBuffer>>();
	m_particleConstBuffer->Initialize(m_commonResources->GetDeviceResources()->GetD3DDevice());

	// 頂点シェーダーを取得する
	m_vertexShader   = Resources::GetInstance()->GetShaderResources()->GetVertexShader(VS_ID::Particle_VS);
	// ジオメトリシェーダーを取得する
	m_geometryShader = Resources::GetInstance()->GetShaderResources()->GetGeometryShader(GS_ID::Particle_GS);
	// インプットレイアウトを取得する
	m_inputLayout    = Resources::GetInstance()->GetShaderResources()->GetParticleInputLayout();

	// シェーダーにデータを渡すためのUIのバーテックスバッファの作成
	D3D11_BUFFER_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	// サイズは必要な頂点分にする
	desc.ByteWidth = sizeof(DirectX::VertexPositionColorTexture) * 700; 
	// 毎フレーム書き換えるならDYNAMICを使う
	desc.Usage = D3D11_USAGE_DYNAMIC;
	// バインドフラグはVertexBuffer
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// CPUから書き込みできるようにする
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// バッファ作成
	m_device->CreateBuffer(&desc, nullptr, &m_vertexBuffer);
}


void Renderer::Render()
{
	DirectX::SimpleMath::Matrix viewMatrix       = m_commonResources->GetViewMatrix();
	DirectX::SimpleMath::Matrix projectionMatrix = m_commonResources->GetProjectionMatrix();

	// オブジェクトを描画を行う
	for (const auto &object : m_renderableObjects)
	{
		if(object.first->GetIsActive() && object.second->GetIsActive())
		object.second->Render(m_context, m_commonStates, viewMatrix, projectionMatrix);
	}

	// パーティクル描画
	this->ParticleRender(viewMatrix, projectionMatrix);
}



void Renderer::Attach(IObject* object, IRenderableObject* renderableObject)
{
	m_renderableObjects[object] = renderableObject;
}


void Renderer::ParticleRender(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	ParticleConstBuffer particleConstBuffer = {};
	particleConstBuffer.projectionMatrix = projectionMatrix.Transpose();
	particleConstBuffer.viewMatrix = viewMatrix.Transpose();
	// ビルボード行列を作る
	m_billboardMatrix = viewMatrix.Invert();
	m_billboardMatrix._41 = 0.0f;
	m_billboardMatrix._42 = 0.0f;
	m_billboardMatrix._43 = 0.0f;
	particleConstBuffer.billboardMatrix = m_billboardMatrix.Transpose();
	particleConstBuffer.worldMatrix = world.Transpose();
	particleConstBuffer.time = DirectX::SimpleMath::Vector4::Zero;

	// 定数バッファの更新
	m_particleConstBuffer->Update(m_context, particleConstBuffer);

	//	シェーダーに定数バッファを渡す
	ID3D11Buffer* cb[1] = { m_particleConstBuffer->GetBuffer() };
	m_context->VSSetConstantBuffers(0, 1, cb);
	m_context->GSSetConstantBuffers(0, 1, cb);
	m_context->PSSetConstantBuffers(0, 1, cb);

	//	半透明描画指定		補間アルファ合成
	ID3D11BlendState* blendstate = m_commonStates->NonPremultiplied();
	//	透明判定処理
	m_context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	m_context->OMSetDepthStencilState(m_commonStates->DepthRead(), 0);

	//	カリングはなし
	m_context->RSSetState(m_commonStates->CullNone());

	//	インプットレイアウトの登録
	m_context->IASetInputLayout(m_inputLayout);

	// プリミティブトポロジーを設定
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// 頂点シェーダーの設定
	m_context->VSSetShader(m_vertexShader, nullptr, 0);
	// ジオメトリシェーダーの設定
	m_context->GSSetShader(m_geometryShader, nullptr, 0);

	for (const auto& particleEmitter : m_particleEmitter)
	{
		if (!particleEmitter->GetIsActive()) break;

		if (particleEmitter->GetInputDatas().size() <= 0) break;

		// ワールド行列を設定
		particleConstBuffer.worldMatrix = DirectX::SimpleMath::Matrix::Identity;

		// 定数バッファの更新
		m_particleConstBuffer->UpdateIfNeeded(m_context, particleConstBuffer);

		// テクスチャの設定
		ID3D11ShaderResourceView* srv = particleEmitter->GetTexture();
		m_context->PSSetShaderResources(0, 1, &srv);

		//	画像用サンプラーの登録
		ID3D11SamplerState* sampler[1] = { m_commonStates->LinearWrap() };
		m_context->PSSetSamplers(0, 1, sampler);

		// ピクセルシェーダーの設定
		m_context->PSSetShader(particleEmitter->GetPixelShader(), nullptr, 0);

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		m_context->Map(m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

		memcpy(mappedResource.pData, particleEmitter->GetInputDatas().data(),
			sizeof(DirectX::VertexPositionColorTexture) * particleEmitter->GetInputDatas().size());

		m_context->Unmap(m_vertexBuffer.Get(), 0);


		UINT stride = sizeof(DirectX::VertexPositionColorTexture);
		UINT offset = 0;
		ID3D11Buffer* buffer = m_vertexBuffer.Get();
		m_context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);

		// 描画処理
		m_context->Draw(static_cast<UINT>(particleEmitter->GetInputDatas().size()), 0);

		// ピクセルシェーダの解放
		m_context->PSSetShader(nullptr, nullptr, 0);

		// テクスチャリソースを解放
		ID3D11ShaderResourceView* nullsrv[] = { nullptr };
		m_context->PSSetShaderResources(0, 1, nullsrv);
	}

	//	シェーダの登録を解除しておく
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->GSSetShader(nullptr, nullptr, 0);
}
