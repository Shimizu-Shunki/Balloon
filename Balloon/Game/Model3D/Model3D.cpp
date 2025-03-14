#include "Framework/pch.h"
#include "Game/Model3D/Model3D.h"

#include "Interface/IMaterial.h"
#include "Interface/IObject.h"

Model3D::Model3D()
	:
	m_model{},
	m_material{},
	m_object{},
	m_isShadow{}
{
}


void Model3D::Initialize(DirectX::Model* model, IMaterial* material, IObject* object, bool isShadow)
{
	m_model    = model;
	m_material = material;
	m_object   = object;
	m_isShadow = isShadow;
}


void Model3D::Render(ID3D11DeviceContext1* context, DirectX::CommonStates* states,
	DirectX::SimpleMath::Matrix viewMatrix, DirectX::SimpleMath::Matrix projectionMatrix,
	ID3D11Buffer* lightBuffer
)
{
	// ワールド行列を取得する
	DirectX::SimpleMath::Matrix world = m_object->GetTransform()->GetWorldMatrix();

	// モデル描画
	m_model->Draw(context, *states, world, viewMatrix, projectionMatrix, false, [&]
		{
			// 定数バッファを指定する
			ID3D11Buffer* cbuf[] = { lightBuffer };
			context->VSSetConstantBuffers(1, 1, cbuf);
			context->PSSetConstantBuffers(1, 1, cbuf);

			m_material->BeginMaterial();
		});
}