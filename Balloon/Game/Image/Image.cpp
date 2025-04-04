#include "Framework/pch.h"
#include "Game/Image/Image.h"
#include "Game/Transform/Transform.h"
#include "Game/Material/Buffers.h"
#include "Interface/IMaterial.h"

Image::Image()
	:
	m_isActive{},
	m_material{},
	m_transform{},
	m_texture{},
	m_ruleTexture{}
{
}

void Image::Initialize(bool isActive, IMaterial* material, Transform* transform)
{
	// �������ݒ�
	m_isActive = isActive;
	m_transform = transform;
	m_material = material;
	m_texture = nullptr;
	m_ruleTexture = nullptr;
}

IMaterial* Image::Render(ID3D11DeviceContext1* context,ID3D11Buffer* vertexBuffer)
{
	UIVertexBuffer UiVertexBuffer;

	UiVertexBuffer.position = {
		m_transform->GetLocalPosition().x , m_transform->GetLocalPosition().y ,
		m_transform->GetLocalPosition().z , 1.0f
	};
	UiVertexBuffer.rotation = m_transform->GetLocalRotation().ToEuler();
	UiVertexBuffer.scale    = m_transform->GetLocalScale();
	UiVertexBuffer.rect     = m_transform->GetRect();
	UiVertexBuffer.color    = m_transform->GetColor();

	// ���_�o�b�t�@�̍X�V
	context->UpdateSubresource(vertexBuffer, 0, NULL, &UiVertexBuffer, 0, 0);

	// ���_�o�b�t�@�ݒ�
	ID3D11Buffer* buffers[] = { vertexBuffer };
	UINT stride[] = { sizeof(UIVertexBuffer) };
	UINT offset[] = { 0 };
	context->IASetVertexBuffers(0, 1, buffers, stride, offset);

	// �}�e���A����K��
	m_material->BeginMaterial();

	context->PSSetShaderResources(0, 1, &m_texture);

	if (m_ruleTexture != nullptr) {
		context->PSSetShaderResources(1, 1, &m_ruleTexture);
	}



	return m_material;
}

void Image::SetTexture(ID3D11ShaderResourceView* texture, int& width, int& height)
{
	// �摜���Z�b�g
	m_texture = texture;

	// �摜�̃T�C�Y���擾����
	// �ꎞ�I�ȕϐ��̐錾
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	D3D11_TEXTURE2D_DESC desc;

	// �e�N�X�`���̏����擾����================================
	// �e�N�X�`����ID3D11Resource�Ƃ��Č���
	m_texture->GetResource(resource.GetAddressOf());
	// ID3D11Resource��ID3D11Texture2D�Ƃ��Č���
	resource.As(&texture2D);
	// �e�N�X�`�������擾����
	texture2D->GetDesc(&desc);

	// �e�N�X�`���T�C�Y���擾���Afloat�^�ɕϊ�����
	width = static_cast<int>(desc.Width);
	height = static_cast<int>(desc.Height);
}