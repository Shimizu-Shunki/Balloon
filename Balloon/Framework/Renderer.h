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
	// �R���X�g���N�^
	Renderer();
	// �f�X�g���N�^
	~Renderer() = default;

	// �`��I�u�W�F�N�g�ǉ�
	void Attach(IObject* object, IRenderableObject* renderableObject);
	void Attach(ParticleEmitter* emitter) { m_particleEmitter.push_back(emitter); }

	// �`�揈��
	void Render();

private:

	// �p�[�e�B�N���`��
	void ParticleRender(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix);

private:
	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �f�o�C�X
	ID3D11Device1* m_device;
	// �R���e�L�X�g
	ID3D11DeviceContext1* m_context;
	// �R�����X�e�[�g
	DirectX::CommonStates* m_commonStates;

	// �`��I�u�W�F�N�g
	std::unordered_map<IObject*, IRenderableObject*> m_renderableObjects;


	// �萔�o�b�t�@
	std::unique_ptr<ConstantBuffer<ParticleConstBuffer>> m_particleConstBuffer;

	std::vector<ParticleEmitter*> m_particleEmitter;

	// �C���v�b�g���C�A�E�g
	ID3D11InputLayout* m_inputLayout;

	// ���_�V�F�[�_�[
	ID3D11VertexShader* m_vertexShader;
	// �W�I���g���V�F�[�_�[
	ID3D11GeometryShader* m_geometryShader;

	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;

	// �r���{�[�h
	DirectX::SimpleMath::Matrix m_billboardMatrix;

};