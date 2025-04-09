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
#include <Game/Material/SeaMaterial.h>


class CommonResources;
class ObjectMessenger;
class PBRLit;
class SkyBox;
class Model3D;
class Player;
class Cloud;
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
	// �V�[���̃X�e�[�g��ύX����
	void ChangeState(IState* newState) override;
	// �����蔻�胁�b�Z�[�W���󂯎��
	void OnSceneMessegeAccepted(Message::SceneMessageID messageID) override;

private:

	// ���L���\�[�X
	CommonResources* m_commonResources;
	ObjectMessenger* m_objectMessenger;

	DirectX::CommonStates* m_commonStates;

	// �f�o�b�O�J�����Ŏ���
	std::unique_ptr<DebugCamera> m_debugCamera;

	std::unique_ptr<Player> m_plaeyr;

	std::unique_ptr<Cloud> m_cloud;

	
};