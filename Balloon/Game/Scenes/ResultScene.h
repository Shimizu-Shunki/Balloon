#pragma once
#include "Interface/IScene.h"
#include "Framework/Graphics.h"
#include "Scenes/SceneManager/SceneManager.h"

class IScene;
class InputManager;
class SceneManager;

class ResultScene : public IScene
{

public:
	// �R���X�g���N�^
	ResultScene(SceneManager* scene_manager);
	// �f�X�g���N�^
	~ResultScene() override = default;


	// ����������
	void Initialize() override;
	// �X�^�[�g����
	void Start() override;
	// �X�V����
	void Update(float elapsed_time) override;
	// �`�揈��
	void Render() override;
	// �I������
	void Finalize() override;

private:

	// �O���t�B�b�N�X
	Graphics* m_graphics;

	// �V�[���}�l�[�W���[
	SceneManager* m_scene_manager;
	// �C���v�b�g�}�l�[�W���[
	InputManager* m_input_manager;
};