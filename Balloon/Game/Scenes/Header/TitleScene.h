#pragma once
#include "Interface/IScene.h"



class CommonResources;
class StateMachine;
class RenderManager;
class IObject;
class Transform;
class DebugCamera;
class TitleLogo;
class Fade;


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
	// �X�e�[�g�R���g���[���[�̍쐬
	void CreateStateStateController();
	// �J�����̍쐬
	void CreateCamera();


private:

	// ���L���\�[�X
	CommonResources* m_commonResources;

	// �X�e�[�g�}�V�[��
	std::unique_ptr<StateMachine> m_stateMachine;

	// �t�F�[�h����
	std::unique_ptr<Fade> m_fade;

	// �^�C�g�����S
	std::unique_ptr<TitleLogo> m_titleLogo;

	// �v���C���[
	std::unique_ptr<IObject> m_player;

};