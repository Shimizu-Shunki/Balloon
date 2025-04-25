#include "pch.h"
#include "Framework/Renderer.h"
#include "Framework/CommonResources.h"
#include "Interface/IRenderableObject.h"

Renderer::Renderer()
{
	m_commonResources = CommonResources::GetInstance();
	m_context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	m_commonStates = CommonResources::GetInstance()->GetCommonStates();
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
}



void Renderer::Attach(IObject* object, IRenderableObject* renderableObject)
{
	m_renderableObjects[object] = renderableObject;
}