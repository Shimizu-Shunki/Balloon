#pragma once
#include "Interface/IScene.h"


class CommonResources;
class StateMachine;
class RenderManager;
class IObject;
class Transform;
class DebugCamera;


class TitleScene: public IScene
{
public:
	// �R���X�g���N�^
	TitleScene();
	// �f�X�g���N�^
	~TitleScene();

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

	// �X�e�[�g�}�V�[��
	std::unique_ptr<StateMachine> m_stateMachine;


};