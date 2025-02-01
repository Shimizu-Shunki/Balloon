#pragma once
#include "Game/Material/SpriteMaterial.h"
#include <unordered_map>

// �S�Ẵ��f���AUI�̕`����s���N���X

class Transform;
class CameraManager;

class RenderManager
{
public:
	// ���[���h�s��ϊ��͊e�N���X�ōs��

	struct RenderableObject
	{
		// ���i�[���ꂽTransform�N���X�̃|�C���^
		 Transform* transform;
		// ���f��
		DirectX::Model* model;
		// �}�e���A��
	};



public:
	// �v���W�F�N�V�����s����擾����
	DirectX::SimpleMath::Matrix GetProjectionMatrix() const { return m_projectionMatrix; }
	// �`��p���f����ݒ�
	void AddModel(RenderManager::RenderableObject model) { m_pendingRenderableObjects.push_back(model); }
	// �X�J�C�X�t�B�A��o�^����
	void SetSkySphereObject(RenderManager::RenderableObject object) { m_skySphere = object; }

public:
	// �`�揀���o�^
	void RegisterPendingDrawables();
	// �`��p�i�[�ɂɈړ�����
	void CommitPendingDrawables();

private:
	//	�R���X�g���N�^
	RenderManager();
	//	�f�X�g���N�^
	~RenderManager() = default;
public:
	RenderManager(const RenderManager&) = delete;             // �R�s�[�֎~
	RenderManager& operator=(const RenderManager&) = delete;  // �R�s�[����֎~
	RenderManager(const RenderManager&&) = delete;            // ���[�u�֎~
	RenderManager& operator=(const RenderManager&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static RenderManager* GetInstance()
	{
		static RenderManager instance;
		return &instance;
	}

public:

	// �`�揈��
	void Render();


private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;
	DirectX::CommonStates* m_commonStates;

	CameraManager* m_cameraManager;

	// 2D�̃}�e���A�����i�[
	std::vector<SpriteMaterial*> m_spriteMaterials;
	// 2D �}�e���A���̏����i�K�f�[�^
	std::vector<SpriteMaterial*> m_pendingSpriteMaterials;


	// �X�J�C�X�t�B�A
	RenderableObject m_skySphere;
	// 3D�`��ɕK�v�ȏ��i�[�\����
	std::vector<RenderableObject> m_renderableObjects;
	// 3D ���f���̏����i�K�f�[�^
	std::vector<RenderableObject> m_pendingRenderableObjects;

	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_projectionMatrix;
};