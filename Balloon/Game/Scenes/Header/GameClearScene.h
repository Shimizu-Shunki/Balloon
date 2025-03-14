#pragma once
#include "Interface/IScene.h"


class CommonResources;

class StateMachine;
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

private:

	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �X�e�[�g�}�V�[��
	std::unique_ptr<StateMachine> m_stateMachine;

	// �t�F�[�h����
	std::unique_ptr<Fade> m_fade;



};