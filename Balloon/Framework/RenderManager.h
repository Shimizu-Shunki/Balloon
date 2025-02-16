#pragma once
#include "Game/Material/SpriteMaterial.h"
#include "Interface/ISprite.h"
#include <unordered_map>
#include <shared_mutex>

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
	// �`��p���f����ݒ�
	void AddModel(RenderManager::RenderableObject model) { m_pendingRenderableObjects.push_back(model); }
	// �X�v���C�g��ǉ�
	void AddSprite(ISprite* sprite) { m_pendingSprite.push_back(sprite); }

	// �X�J�C�X�t�B�A��o�^����
	void SetSkySphereObject(RenderManager::RenderableObject object) { m_skySphere = object; }

public:
	// �`��p�i�[�ɂɈړ�����
	void SwitchRenderbleObjects();

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
	std::vector<ISprite*> m_sprite;
	// 2D �}�e���A���̏����i�K�f�[�^
	std::vector<ISprite*> m_pendingSprite;


	// �X�J�C�X�t�B�A
	RenderableObject m_skySphere;
	// 3D�`��ɕK�v�ȏ��i�[�\����
	std::vector<RenderableObject> m_renderableObjects;
	// 3D ���f���̏����i�K�f�[�^
	std::vector<RenderableObject> m_pendingRenderableObjects;

	std::shared_mutex m_mutex;  // �ǂݏ������b�N
};