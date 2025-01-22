#pragma once

class IScene
{
public:
	// �f�X�g���N�^
	virtual ~IScene() = default;

public:
	// ����������
	virtual void Initialize() = 0;
	// �X�^�[�g����
	virtual void Start() = 0;
	// �X�V����
	virtual void Update(float elapsed_time) = 0;
	// �`�揈��
	virtual void Render() = 0;
	// �I������
	virtual void Finalize() = 0;
};