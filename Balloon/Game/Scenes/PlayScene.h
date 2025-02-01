#pragma once
#include "Interface/IScene.h"
#include "Framework/Graphics.h"
#include "Scenes/SceneManager/SceneManager.h"

class IScene;
class IComponent;
class InputManager;
class SceneManager;
class CollisionManager;
class AudioManager;
class SeaMaterial;
class DebugCamera;
class TPSCamera;

class SkySphere;

class Countdown;
class Fade;
class Timer;

class PlayScene : public IScene
{

private:

public:
	// �R���X�g���N�^
	PlayScene(SceneManager* scene_manager);
	// �f�X�g���N�^
	~PlayScene() override = default;

	// �X�^�[�g����

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
	// �I�u�W�F�N�g�̏�����
	void InitializeObject();
	// �t���A�̍X�V����
	void UpdateFloor(float elapsed_time);

private:

	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// �V�[���}�l�[�W���[
	SceneManager* m_scene_manager;
	// �I�[�f�B�I�}�l�[�W���[
	AudioManager* m_audioManager;
	// �C���v�b�g�}�l�[�W���[
	InputManager* m_input_manager;
	// �����蔻��
	std::unique_ptr<CollisionManager> m_collisionManager;

	// �J����
	// TPS�J����
	std::unique_ptr<TPSCamera> m_tpsCamera;
	// �f�o�b�O�J����
	std::unique_ptr<DebugCamera> m_debugCamera;

	// �X�J�C�X�t�B�A
	std::unique_ptr<SkySphere> m_skySphere;

	// �I�u�W�F�N�g�̒ǉ�
	std::unique_ptr<IComponent> m_floorPlayerStart;
	std::unique_ptr<IComponent> m_floorLeftUp;
	std::unique_ptr<IComponent> m_floorRightUp;
	std::unique_ptr<IComponent> m_floorLeftDown;
	std::unique_ptr<IComponent> m_floorRightDown;

	// �v���C���[
	std::unique_ptr<IComponent> m_player;
	// �G
	std::unique_ptr<IComponent> m_enemy;

	// UI
	// �t�F�[�h
	std::unique_ptr<Fade> m_fade;
	// �^�C�}�[
	std::unique_ptr<Timer> m_timer;
	// �J�E���g�_�E��
	std::unique_ptr<Countdown> m_countdown;

	// �C
	std::unique_ptr<SeaMaterial> m_SeaMaterial;

	bool m_isFade;
};