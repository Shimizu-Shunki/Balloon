#pragma once

class CommonResources;
class Transform;

class SkySphere
{
public:
	// �^�[�Q�b�g��Transform��ݒ肷��
	void SetTargetTransform(Transform* transform) { m_targetTransform = transform; }

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
	

private:
	// ���L���\�[�X
	CommonResources* m_commonResources;

	// ���f��
	DirectX::Model* m_model;
	// Transform
	std::unique_ptr<Transform> m_transform;
	// �^�[�Q�b�gTransform
	Transform* m_targetTransform;

};