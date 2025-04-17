// ============================================
// 
// �t�@�C����: DebugScene.h
// �T�v: DebugScene.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IScene.h"


class CommonResources;
class DebugCamera;


class DebugScene : public IScene
{
public:
	// �R���X�g���N�^
	DebugScene();
	// �f�X�g���N�^
	~DebugScene();

public:
	// ����������
	void Initialize() override;
	// �X�^�[�g����
	void Start()  override;
	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;
	// �I������
	void Finalize() override;

private:

	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �f�o�b�O�J�����Ŏ���
	std::unique_ptr<DebugCamera> m_debugCamera;
};