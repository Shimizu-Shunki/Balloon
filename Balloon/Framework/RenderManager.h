#pragma once
#include "Game/Material/SpriteMaterial.h"
#include "Interface/ISprite.h"
#include <unordered_map>
#include <shared_mutex>
#include "Interface/IObject.h"
#include "Game/ShadowMap/CascadedShadowMap.h"
#include "Game/Sky/SkyBox.h"


// �S�Ẵ��f���AUI�̕`����s���N���X

class Transform;
class CameraManager;
class CascadedShadowMap;
class Model3D;
class SkyBox;

class RenderManager
{
public:
	// �`��p���f����ݒ�
	void AddModel(Model3D* model) { m_pendingModels.push_back(model); }
	// �X�v���C�g��ǉ�
	void AddSprite(ISprite* sprite) { m_pendingSprite.push_back(sprite); }

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

	// 2D�`��
	void SpriteRender();

private:
	// �u�����h�X�e�[�g�̍쐬
	void CreateSpriteBlendState();
	// �[�x�X�e���V���X�e�[�g�̍쐬
	void CreateSpriteDepthStencilState();
	// ���X�^���C�U�[�X�e�[�g�̍쐬
	void CreateSpriteRasterizerState();


private:
	ID3D11Device1* m_device;
	ID3D11DeviceContext1* m_context;
	DirectX::CommonStates* m_commonStates;

	CameraManager* m_cameraManager;

	// �u�����h�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_spriteBlendState;
	// �[�x�X�e���V���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_spriteDepthStencilState;
	// ���X�^���C�U�[�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_spriteRasterizerState;
	//	�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	// ���̓��C�A�E�g
	ID3D11InputLayout* m_spriteInputLayout;

	// 2D�̃}�e���A�����i�[
	std::vector<ISprite*> m_sprite;
	// 2D �}�e���A���̏����i�K�f�[�^
	std::vector<ISprite*> m_pendingSprite;


	// �J�X�P�[�h�V���h�E�}�b�v�@�܂��J�X�P�[�h����Ă��Ȃ�
	std::unique_ptr<CascadedShadowMap> m_shadowMap;

	// �X�J�C�{�b�N�X
	std::unique_ptr<SkyBox> m_skyBox;

	// ���f��
	std::vector<Model3D*> m_models;
	// ���f���@�����i�K�f�[�^
	std::vector<Model3D*> m_pendingModels;
};