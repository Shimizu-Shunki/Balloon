#pragma once
#include "Interface/IScene.h"
#include "Framework/Graphics.h"
#include "Scenes/SceneManager/SceneManager.h"
#include "Interface/IComponent.h"
#include "Game/Camera/CameraManager.h"
#include "Interface/ICamera.h"

class IScene;
class InputManager;
class DebugCamera;
class CollisionManager;
class TPSCamera;
class Balloon;
class Enemy;
class ICamera;
class CameraManager;

namespace DX
{
	class RenderTexture;
}

class Object;

class HomeScene : public IScene
{

public:
	// �R���X�g���N�^
	HomeScene(SceneManager* scene_manager);
	// �f�X�g���N�^
	~HomeScene() override;


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
	// �f�o�b�O�J����
	std::unique_ptr<DebugCamera> m_debugCamera;
	// TPS�J����
	std::unique_ptr<TPSCamera> m_tpsCamera;

	// �V�[���}�l�[�W���[
	SceneManager* m_scene_manager;
	// �C���v�b�g�}�l�[�W���[
	InputManager* m_input_manager;
	// �����蔻��
	std::unique_ptr<CollisionManager> m_collisionManager;

	// �I�u�W�F�N�g�̒ǉ�
	std::unique_ptr<IComponent> m_floor;
	// �v���C���[
	std::unique_ptr<IComponent> m_player;
	// �G
	std::unique_ptr<IComponent> m_enemy;

	// �|�X�g�v���Z�X
	std::unique_ptr<DirectX::BasicPostProcess> m_postProcess;
	// �����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	// �J�����}�l�[�W���[
	std::unique_ptr<CameraManager> m_cameraManager;
};