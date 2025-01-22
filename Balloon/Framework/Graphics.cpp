#include "Framework/pch.h"
#include "Framework/Graphics.h"
#include "Framework/Microsoft/DebugDraw.h"


std::unique_ptr<Graphics> Graphics::m_graphics = nullptr;

// �O���t�B�b�N�X�̃C���X�^���X���擾����
Graphics* const Graphics::GetInstance()
{
	if (m_graphics == nullptr)
	{
		// �O���t�B�b�N�X�̃C���X�^���X�𐶐�����
		m_graphics.reset(new Graphics());
	}
	// �O���t�B�b�N�X�̃C���X�^���X��Ԃ�
	return m_graphics.get();
}

// �R���X�g���N�^
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
	// �f�o�C�X���\�[�X�̃C���X�^���X�𐶐�����
	m_device_resources = std::make_unique<DX::DeviceResources>(
		DXGI_FORMAT_B8G8R8A8_UNORM,     // �o�b�N�o�b�t�@�̃t�H�[�}�b�g���w�肷��
		DXGI_FORMAT_D24_UNORM_S8_UINT   // �X�e���V���o�b�t�@���g�p����
	);
}

// �f�X�g���N�^
Graphics::~Graphics()
{
}

// ����������
void Graphics::Initialize(HWND window)
{
	// �f�o�C�X���擾����
	m_device = m_device_resources->GetD3DDevice();
	// �f�o�C�X�R���e�L�X�g���擾����
	m_context = m_device_resources->GetD3DDeviceContext();

	// �R�����X�e�[�g�𐶐�����
	m_common_states = std::make_unique<DirectX::CommonStates>(m_device);
	// �X�v���C�g�o�b�`�𐶐�����
	m_sprite_batch = std::make_unique<DirectX::SpriteBatch>(m_context);
	// �x�[�V�b�N�G�t�F�N�g�𐶐�����
	m_basic_effect = std::make_unique<DirectX::BasicEffect>(m_device);
	// �X�v���C�g�t�H���g�𐶐�����
	m_sprite_font = std::make_unique<DirectX::SpriteFont>(m_device, L"resources\\font\\SegoeUI_18.spritefont");
	// �v���~�e�B�u�o�b�`�𐶐�����
	m_primitive_batch_color = std::make_unique<DirectX::PrimitiveBatch
		<DirectX::VertexPositionColor>>(m_context);
	m_primitive_batch_position = std::make_unique<DirectX::PrimitiveBatch
		<DirectX::VertexPosition>>(m_context);
	m_primitive_batch_texture = std::make_unique<DirectX::PrimitiveBatch
		<DirectX::VertexPositionColorTexture>>(m_context);
	// ���_�J���[��L���ɂ���
	m_basic_effect->SetVertexColorEnabled(true);
	// �e�N�X�`���𖳌��ɂ���
	m_basic_effect->SetTextureEnabled(false);
	void const* shaderByteCode;
	size_t byteCodeLength;
	// ���_�V�F�[�_�[���擾����
	m_basic_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	// ���̓��C�A�E�g�𐶐�����
	m_device->CreateInputLayout(
		DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_input_layout.ReleaseAndGetAddressOf()
	);
	// ���X�^���C�U�[�f�B�X�N���v�V����
	CD3D11_RASTERIZER_DESC rasterizerStateDesc(
		D3D11_FILL_SOLID, D3D11_CULL_NONE,
		FALSE,
		D3D11_DEFAULT_DEPTH_BIAS, D3D11_DEFAULT_DEPTH_BIAS_CLAMP,
		D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS, TRUE,
		FALSE,
		FALSE,
		TRUE
	);
	// ���X�^���C�Y�X�e�[�g�𐶐�����
	m_device->CreateRasterizerState(&rasterizerStateDesc, m_rasterrizer_state.ReleaseAndGetAddressOf());
	// �G�t�F�N�g�t�@�N�g���𐶐�����
	m_effect_factory = std::make_unique<DirectX::EffectFactory>(m_device);
}

// �������`�悷��
void Graphics::DrawString(const float& x, const float& y, const wchar_t* str)
{
	// �������`�悷��
	m_sprite_font->DrawString(m_sprite_batch.get(), str, DirectX::SimpleMath::Vector2(x, y));
}

// �v���~�e�B�u�`����J�n����
void Graphics::DrawPrimitiveBegin(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	// �u�����f�B���O��Ԃ�ݒ肷��
	//m_context->OMSetBlendState(m_common_states->Opaque(), nullptr, 0xFFFFFFFF);
	// �[�x�X�e���V����Ԃ�ݒ肷��
	//m_context->OMSetDepthStencilState(m_common_states->DepthNone(), 0);
	// �J�����O���s��Ȃ�
	//m_context->RSSetState(m_common_states->CullNone());
	// ���X�^���C�U�[��Ԃ�ݒ肷��
	//m_context->RSSetState(m_rasterrizer_state.Get());

	// �r���[�s���ݒ肷��
	m_basic_effect->SetView(view);
	// �v���W�F�N�V�����s���ݒ肷��
	m_basic_effect->SetProjection(projection);
	// ���[���h�s���ݒ肷��
	m_basic_effect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	// �R���e�L�X�g��ݒ肷��
	m_basic_effect->Apply(m_context);
	// ���̓��C�A�E�g��ݒ肷��
	m_context->IASetInputLayout(m_input_layout.Get());
	// �v���~�e�B�u�o�b�`���J�n����
	m_primitive_batch_color->Begin();
}

// �`��v���~�e�B�u���I������
void Graphics::DrawPrimitiveEnd()
{
	// �v���~�e�B�u�o�b�`���I������
	m_primitive_batch_color->End();
}

// ������`�悷��(XZ����)
void Graphics::DrawLine(const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& vector, const DirectX::FXMVECTOR& color)
{
	// ���_�J���[��ݒ肷��
	DirectX::VertexPositionColor vertex[2] =
	{
		{ DirectX::SimpleMath::Vector3(position.x, 0.0f, position.y), color },
		{ DirectX::SimpleMath::Vector3(position.x + vector.x, 0.0f, position.y + vector.y), color }
	};
	// ������`�悷��
	m_primitive_batch_color->DrawLine(vertex[0], vertex[1]);
}

// ������`�悷��
void Graphics::DrawLine(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& vector, const DirectX::FXMVECTOR& color)
{
	// ���_�J���[��ݒ肷��
	DirectX::VertexPositionColor vertex[2] =
	{
		{ DirectX::SimpleMath::Vector3(position.x, position.y, position.z), color },
		{ DirectX::SimpleMath::Vector3(position.x + vector.x, position.y + vector.y, position.z + vector.z), color }
	};
	// ������`�悷��
	m_primitive_batch_color->DrawLine(vertex[0], vertex[1]);
}

// �x�N�g����`�悷��(XZ����)
void Graphics::DrawVector(const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& vector, const DirectX::FXMVECTOR& color)
{
	using namespace DirectX::SimpleMath;
	const float cosTheta = cosf(DirectX::XMConvertToRadians(20.0f));
	const float sinTheta = sinf(DirectX::XMConvertToRadians(20.0f));

	// ���̃x�N�g���̃T�C�Y��ݒ肷��
	Vector2 arrow = -vector;
	// ���K������
	arrow.Normalize();
	// ���̃T�C�Y��ݒ肷��
	arrow *= 3.0f;
	// �E�� X: (xcos��- ysin��)  Y: (xsin��+ ycos��)
	Vector2 arrowR = Vector2(arrow.x * cosTheta - arrow.y * sinTheta, arrow.x * sinTheta + arrow.y * cosTheta);
	// ���� X: (xcos��- ysin��)  Y: (xsin��+ ycos��)
	Vector2 arrowL = Vector2(arrow.x * cosTheta + arrow.y * sinTheta, -arrow.x * sinTheta + arrow.y * cosTheta);
	// ������`�悷��
	DrawLine(position, vector, color);
	// �E���`�悷��
	DrawLine(position + vector, arrowR, color);
	// �����`�悷��
	DrawLine(position + vector, arrowL, color);
}

// �x�N�g����`�悷��
void Graphics::DrawVector(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& vector, const DirectX::FXMVECTOR& color)
{
	using namespace DirectX::SimpleMath;
	const float cosTheta = cosf(DirectX::XMConvertToRadians(20.0f));
	const float sinTheta = sinf(DirectX::XMConvertToRadians(20.0f));

	// ���̃x�N�g���̃T�C�Y��ݒ肷��
	Vector3 arrow = -vector;
	// ���K������
	arrow.Normalize();
	// ���̃T�C�Y��ݒ肷��
	arrow *= 3.0f;
	// �E�� X: (xcos��- zsin��)  Z: (xsin��+ zcos��)
	Vector3 arrowR = Vector3(arrow.x * cosTheta - arrow.z * sinTheta, arrow.y, arrow.x * sinTheta + arrow.z * cosTheta);
	// ���� X: (xcos��- zsin��)  Z: (xsin��+ zcos��)
	Vector3 arrowL = Vector3(arrow.x * cosTheta + arrow.z * sinTheta, arrow.y, -arrow.x * sinTheta + arrow.z * cosTheta);
	// ������`�悷��
	DrawLine(position, vector, color);
	// �E���`�悷��
	DrawLine(position + vector, arrowR, color);
	// �����`�悷��
	DrawLine(position + vector, arrowL, color);
}

// �~��`�悷��(XZ����)
void Graphics::DrawCircle(const DirectX::SimpleMath::Vector2& center, const float& radius, const DirectX::FXMVECTOR& color, const int& split)
{
	using namespace DirectX::SimpleMath;

	// �p�x������������
	float angle = 0.0f;
	// �n�_��錾����
	Vector2 position1 = center + Vector2(cosf(angle), sinf(angle)) * radius;
	for (int index = 0; index < split; index++)
	{
		// �n�_��ݒ肷��
		Vector2 position0 = position1;
		// �p�x���v�Z����
		angle += DirectX::XM_2PI / (float)split;
		// �I�_���v�Z����
		position1 = center + Vector2(cosf(angle), sinf(angle)) * radius;
		// �~��`�悷��
		DrawLine(position0, position1 - position0, color);
	}
}

// �~��`�悷��
void Graphics::DrawCircle(const DirectX::SimpleMath::Vector3& center, const float& radius, const DirectX::FXMVECTOR& color, const int& split)
{
	using namespace DirectX::SimpleMath;

	// �p�x������������
	float angle = 0.0f;
	// �I�_���v�Z����
	Vector3 position1 = center + Vector3(cosf(angle), center.y, sinf(angle)) * radius;
	for (int index = 0; index < split; index++)
	{
		// �n�_��ݒ肷��
		Vector3 position0 = position1;
		// �p�x���v�Z����
		angle += DirectX::XM_2PI / (float)split;
		// �I�_���v�Z����
		position1 = center + Vector3(cosf(angle), center.y, sinf(angle)) * radius;
		// �~��`�悷��
		DrawLine(position0, position1 - position0, color);
	}
}

// ��`��`�悷��
void Graphics::DrawQuad(const DirectX::VertexPositionColor& v1, const DirectX::VertexPositionColor& v2, const DirectX::VertexPositionColor& v3, const DirectX::VertexPositionColor& v4)
{
	// ��`��`�悷��
	m_primitive_batch_color->DrawQuad(v1, v2, v3, v4);
}

// ��`��`�悷��
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

// �O���b�g����`��
void Graphics::DrawGridFloor(
	DirectX::SimpleMath::Vector3 width,
	DirectX::SimpleMath::Vector3 height,
	size_t dive
)
{
	DX::DrawGrid(m_primitive_batch_color.get(),
		width,                              // ����
		height,                             // �c��
		DirectX::SimpleMath::Vector3::Zero, // ���_
		dive,                               // ��������
		dive                                // �c������
	);
}

// ���f����`�悷��
void Graphics::DrawModel(const DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection, const bool& depthBuffer)
{
	if (depthBuffer)
	{

		// ���f����`�悷��
		model->Draw(m_context, *m_common_states.get(), world, view, projection, false);
	}
	else
	{
		// ���f����`�悷��
		model->Draw(m_context, *m_common_states.get(), world, view, projection, false,
			[&]() { 	m_context->OMSetDepthStencilState(m_common_states->DepthNone(), 0); }
		);
	}
}