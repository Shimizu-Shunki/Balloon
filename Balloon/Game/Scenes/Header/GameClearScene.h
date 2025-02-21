#pragma once
#include "Interface/IScene.h"


class CommonResources;

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



};