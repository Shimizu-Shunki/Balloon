#pragma once

class CommonResources;
class Transform;

class SkySphere
{
private:
	// �X�s�[�g
	static const float ROTATION_SPEED;

public:
	// �R���X�g���N�^
	SkySphere();
	// �f�X�g���N�^
	~SkySphere() = default;

	// ������
	void Initialize();
	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	// ���L���\�[�X
	CommonResources* m_commonResources;

	// �R���e�L�X�g
	ID3D11DeviceContext1* m_context;

	// ���f��
	DirectX::Model* m_model;
	// Transform
	std::unique_ptr<Transform> m_transform;

};