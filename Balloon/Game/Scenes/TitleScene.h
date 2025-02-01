#pragma once
#include "Interface/IScene.h"
#include "Framework/Graphics.h"
#include "Scenes/SceneManager/SceneManager.h"

class IScene;
class InputManager;
class AudioManager;
class SceneManager;
class TweenManager;
class Sprite2DShader;
class Fade;
class SkySphere;


class TitleScene : public IScene
{

public:
	// �R���X�g���N�^
	TitleScene(SceneManager* scene_manager);
	// �f�X�g���N�^
	~TitleScene() override = default;


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
	// �I�[�f�B�I�}�l�[�W���[
	AudioManager* m_audioManager;
	// Tween�}�l�[�W���[
	TweenManager* m_tweenManager;

	// �X�J�C�X�t�B�A
	std::unique_ptr<SkySphere> m_skySphere;

	// �^�C�g�����S
	std::unique_ptr<Sprite2DShader> m_titleLogo;
	// Start�e�L�X�g
	std::unique_ptr<Sprite2DShader> m_spaceKey;
	// Start�e�L�X�g
	std::unique_ptr<Sprite2DShader> m_startText;

	// �t�F�[�h
	std::unique_ptr<Fade> m_fade;

	DirectX::SimpleMath::Vector3 m_position;


	
};