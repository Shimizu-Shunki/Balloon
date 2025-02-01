#pragma once
#include "Interface/IScene.h"


class CommonResources;
class IObject;
class Transform;
class DebugCamera;


class PlayScene : public IScene
{
public:
	// �R���X�g���N�^
	PlayScene();
	// �f�X�g���N�^
	~PlayScene();

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

	// �I�u�W�F�N�g�̃��[�g
	std::vector<std::unique_ptr<IObject>> m_rootObject;
	// Transform�̃��[�g
	std::unique_ptr<Transform> m_rootTransform;
	// �f�o�b�O�J�����Ŏ���
	std::unique_ptr<DebugCamera> m_debugCamera;
};