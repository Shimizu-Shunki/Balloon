// �C�̕\�����s���}�e���A��

#include "Framework/pch.h"
#include "Game/Material/SeaMaterial.h"
#include "Framework/CommonResources.h"
#include <Framework/Microsoft/ReadData.h>


SeaMaterial::SeaMaterial()
{
	// �C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();
	m_time = 0.0f;
}

SeaMaterial::~SeaMaterial()
{
}

void SeaMaterial::Initialize()
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	

	m_states = std::make_unique<DirectX::DX11::CommonStates>(device);

	m_texture = m_commonResources->GetResources()->GetSeaTexture();


	// �V�F�[�_���擾����
	m_vertexShader = m_commonResources->GetResources()->GetSeaVS();
	m_hullShader   = m_commonResources->GetResources()->GetSeaHS();
	m_domainShader = m_commonResources->GetResources()->GetSeaDS();
	m_pixelShader  = m_commonResources->GetResources()->GetSeaPS();

	m_inputLayout = m_commonResources->GetResources()->GetSeaInputLayout();

	// �u�����h�X�e�[�g�̍쐬
	CreateBlendState(device, context);
	// �[�x�X�e���V���X�e�[�g�̍쐬
	CreateDepthStencilState(device, context);
	// ���X�^���C�U�[�X�e�[�g�̍쐬
	CreateRasterizerState(device, context);

	//	�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);

	// ���_�f�[�^���`�i4�̐���_�j
	DirectX::VertexPositionTexture vertex[4] =
	{
		{ DirectX::XMFLOAT3(-5.0f,  0.0f,  5.0f),  DirectX::XMFLOAT2(0.0f, 0.0f) }, // ����
		{ DirectX::XMFLOAT3(5.0f,   0.0f,  5.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },  // �E��
		{ DirectX::XMFLOAT3(5.0f,   0.0f, -5.0f),  DirectX::XMFLOAT2(1.0f, 1.0f) }, // �E��
		{ DirectX::XMFLOAT3(-5.0f,  0.0f, -5.0f),  DirectX::XMFLOAT2(0.0f, 1.0f) }  // ����
	};

	// ���_�o�b�t�@�̐���
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionTexture) * _countof(vertex); // ���_�f�[�^�S�̂̃T�C�Y
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;

	// ���_�f�[�^�̏�����
	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = vertex;

	device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);

	m_index = 6.0f;
}

void SeaMaterial::Render()
{
	m_time += 0.06f;

	m_index = 8.0f;

	ID3D11DeviceContext1* context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			DirectX::SimpleMath::Vector3 position;
			position.z = 600.0f / 2;
			position.x = -600.0f / 2;

			position.z += -i * 19.0f;
			position.x += j * 19.0f;
			
			float angle = 0.0f;

			if (j % 2 == 1)
			{
				angle = -1.0f;
			}


			DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateScale(2.0f) *
				DirectX::SimpleMath::Matrix::CreateTranslation((position + DirectX::SimpleMath::Vector3::UnitY * -2.0f));

			//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
			ConstBuffer cbuff;
			cbuff.matView = m_commonResources->GetCameraManager()->GetViewMatrix().Transpose();
			cbuff.matProj = m_commonResources->GetCameraManager()->GetProjectionMatrix().Transpose();
			cbuff.matWorld = world.Transpose();
			cbuff.Diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
			cbuff.TessellationFactor = DirectX::SimpleMath::Vector4(m_index, m_time, angle, 0.0f);

			//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
			context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

			// ���_�o�b�t�@��ݒ�
			ID3D11Buffer* buffers[] = { m_vertexBuffer.Get() };
			UINT stride[] = { sizeof(DirectX::VertexPositionTexture) };
			UINT offset[] = { 0 };
			context->IASetVertexBuffers(0, 1, buffers, stride, offset);


			//	�V�F�[�_�[�Ƀo�b�t�@��n��
			ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
			context->VSSetConstantBuffers(1, 1, cb);
			context->HSSetConstantBuffers(1, 1, cb);
			context->DSSetConstantBuffers(1, 1, cb);
			context->PSSetConstantBuffers(1, 1, cb);

			// �T���v���[�X�e�[�g���s�N�Z���V�F�[�_�[�ɐݒ�
			ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
			context->PSSetSamplers(0, 1, sampler);

			// �u�����h�X�e�[�g��ݒ� (�������`��p)
			context->OMSetBlendState(m_blendState.Get(), nullptr, 0xFFFFFFFF);
			// �[�x�X�e���V���X�e�[�g��ݒ� (�[�x�o�b�t�@�̏������݂ƎQ��)
			//context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);


			// ���̓��C�A�E�g��ݒ�
			context->IASetInputLayout(m_inputLayout);

			// �v���~�e�B�u�g�|���W�[��ݒ�
			context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);

			//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
			//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
			context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

			// ���X�^���C�U�[�X�e�[�g�̐ݒ�
			context->RSSetState(m_rasterizerState.Get());

			//	�V�F�[�_���Z�b�g����
			context->VSSetShader(m_vertexShader,nullptr, 0);
			context->HSSetShader(m_hullShader,  nullptr, 0);
			context->DSSetShader(m_domainShader,nullptr, 0);
			context->PSSetShader(m_pixelShader, nullptr, 0);

			// �s�N�Z���V�F�[�_�[�Ƀe�N�X�`�����\�[�X��ݒ�
			context->PSSetShaderResources(0, 1, &m_texture);

			// �`��R�[��
			context->Draw(4, 0);

			//	�V�F�[�_�̓o�^���������Ă���
			context->VSSetShader(nullptr, nullptr, 0);
			context->HSSetShader(nullptr, nullptr, 0);
			context->DSSetShader(nullptr, nullptr, 0);
			context->PSSetShader(nullptr, nullptr, 0);
		}
	}
}

// �u�����h�X�e�[�g�̍쐬
void SeaMaterial::CreateBlendState(ID3D11Device1* device, ID3D11DeviceContext1* context)
{
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = FALSE;  // �J�o���b�W���A���t�@�Ɋ�Â��ėL��������
	blendDesc.IndependentBlendEnable = FALSE; // �����̃����_�[�^�[�Q�b�g��Ɨ����Đݒ肷��

	D3D11_RENDER_TARGET_BLEND_DESC rtBlendDesc = {};
	rtBlendDesc.BlendEnable = TRUE;              // �u�����h��L����
	rtBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;        // �\�[�X�̃A���t�@
	rtBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;    // �t�A���t�@
	rtBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;           // ���Z�u�����h
	rtBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;              // �A���t�@�l�̃\�[�X
	rtBlendDesc.DestBlendAlpha = D3D11_BLEND_ZERO;             // �A���t�@�l�̃f�X�e�B�l�[�V����
	rtBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;           // �A���t�@�l�̉��Z
	rtBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // RGBA�S�Ă�L��

	blendDesc.RenderTarget[0] = rtBlendDesc;

	// �J�X�^���u�����h�X�e�[�g���쐬

	device->CreateBlendState(&blendDesc, &m_blendState);
}

// �[�x�X�e���V���X�e�[�g�̍쐬
void SeaMaterial::CreateDepthStencilState(ID3D11Device1* device, ID3D11DeviceContext1* context)
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = TRUE;                          // �[�x�e�X�g��L����
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // �[�x�o�b�t�@�̏������݂�L����
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;      // �[�x�e�X�g���� (�������ꍇ�̂ݕ`��)
	depthStencilDesc.StencilEnable = FALSE;                       // �X�e���V���e�X�g�𖳌���

	// �[�x�X�e���V���X�e�[�g���쐬
	device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
}

// ���X�^���C�U�[�X�e�[�g�̍쐬
void SeaMaterial::CreateRasterizerState(ID3D11Device1* device, ID3D11DeviceContext1* context)
{
	D3D11_RASTERIZER_DESC rasterDesc = {};
	rasterDesc.FillMode = D3D11_FILL_SOLID;      // �h��Ԃ� (�܂��� D3D11_FILL_WIREFRAME)D3D11_FILL_SOLID
	rasterDesc.CullMode = D3D11_CULL_FRONT;       // �J�����O�Ȃ� (�܂��� D3D11_CULL_FRONT / D3D11_CULL_BACK)
	rasterDesc.FrontCounterClockwise = FALSE;    // ���v���̒��_������\�ʂƂ��ĔF��
	rasterDesc.DepthClipEnable = TRUE;           // �[�x�N���b�s���O��L����
	// ���X�^���C�U�[�X�e�[�g�̍쐬
	device->CreateRasterizerState(&rasterDesc, &m_rasterizerState);
}