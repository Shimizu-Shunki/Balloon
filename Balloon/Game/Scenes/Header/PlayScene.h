#pragma once
#include "Interface/IScene.h"
#include "Interface/ICamera.h"


class CommonResources;
class IObject;
class Transform;
class DebugCamera;
class StateMachine;
class Fade;
class Jump;
class Enemy;




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
	// �X�e�[�g�R���g���[���[�̍쐬
	void CreateStateStateController();

private:

	// ���L���\�[�X
	CommonResources* m_commonResources;

	// �X�e�[�g�}�V�[��
	std::unique_ptr<StateMachine> m_stateMachine;

	// �t�F�[�h����
	std::unique_ptr<Fade> m_fade;

	std::vector<Enemy*> m_enemys;

	// �I�u�W�F�N�g�̃��[�g
	std::vector<std::unique_ptr<IObject>> m_rootObject;
	// Transform�̃��[�g
	std::unique_ptr<Transform> m_rootTransform;
	// �f�o�b�O�J�����Ŏ���
	std::unique_ptr<DebugCamera> m_debugCamera;

	std::unique_ptr<ICamera>  m_camera;
};