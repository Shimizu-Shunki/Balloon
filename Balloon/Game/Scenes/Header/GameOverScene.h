#pragma once
#include "Interface/IScene.h"


class CommonResources;

class GameOverScene : public IScene
{
public:
	// �R���X�g���N�^
	GameOverScene();
	// �f�X�g���N�^
	~GameOverScene();

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