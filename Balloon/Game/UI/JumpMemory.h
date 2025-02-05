#pragma once
#include "Interface/ISprite.h"
#include "Game/Material/Buffers.h"


class JumpMemory : public ISprite
{
public:
	// Transform���擾����
	Transform* GetTransform() const { return m_transform.get(); }
	// �}�e���A�����擾����
	SpriteMaterial* GetSpriteMaterial() const { return m_spriteMaterial.get(); }

public:

	// �R���X�g���N�^
	JumpMemory();
	// �f�X�g���N�^
	~JumpMemory() override = default;

	// ������
	void Initialize();
	// �X�V����
	void Update();

	void Begin() override { m_spriteMaterial->Begin(); }

	void End() override { m_spriteMaterial->End(); }

private:

	// Transform
	std::unique_ptr<Transform> m_transform;

	// �}�e���A��
	std::unique_ptr<SpriteMaterial> m_spriteMaterial;

	// ���_�o�b�t�@
	VertexBuffer m_vertexBuffer;
	// �萔�o�b�t�@
	ConstBuffer m_constBuffer;
};