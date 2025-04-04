#pragma once
#include "Interface/IScene.h"


class CommonResources;
class Fade;

class GameClearScene : public IScene
{
public:
	// �R���X�g���N�^
	GameClearScene();
	// �f�X�g���N�^
	~GameClearScene();

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

	// �t�F�[�h����
	std::unique_ptr<Fade> m_fade;

	// ���݂̃X�e�[�g
	IState* m_currentState;
	// �e�X�e�[�g
	std::unique_ptr<IState> m_fadeInState;
	std::unique_ptr<IState> m_fadeOutState;
	std::unique_ptr<IState> m_gameClearMainState;
};