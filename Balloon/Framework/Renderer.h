#pragma once
#include "Interface/IObject.h"
#include "Interface/IRenderableObject.h"

class CommonResources;

class Renderer
{

public:
	// �R���X�g���N�^
	Renderer();
	// �f�X�g���N�^
	~Renderer() = default;

	// �`��I�u�W�F�N�g�ǉ�
	void Attach(IObject* object, IRenderableObject* renderableObject);
	// �`�揈��
	void Render();
private:
	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �R���e�L�X�g
	ID3D11DeviceContext1* m_context;
	// �R�����X�e�[�g
	DirectX::CommonStates* m_commonStates;

	// �`��I�u�W�F�N�g
	std::unordered_map<IObject*, IRenderableObject*> m_renderableObjects;
};