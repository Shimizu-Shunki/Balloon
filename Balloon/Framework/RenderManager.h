#pragma once
#include "Interface/ISprite.h"
#include <unordered_map>
#include <shared_mutex>
#include "Interface/IObject.h"
#include "Game/ShadowMap/CascadedShadowMap.h"
#include "Game/Sky/SkyBox.h"
#include "Game/Model3D/Model3D.h"


// �S�Ẵ��f���AUI�̕`����s���N���X

class Transform;
class CameraManager;
class CascadedShadowMap;
class Model3D;
class SkyBox;
class Image;

class RenderManager
{
public:
	// �`��p���f����ݒ�
	void AddModel(Model3D* model)
	{ 
		// ���f���̃G�t�F�N�g�����X�V����
		model->GetModel()->UpdateEffects([](DirectX::IEffect* effect) {
			// �x�[�V�b�N�G�t�F�N�g��ݒ肷��
			DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				// �g�U���ˌ�
				DirectX::SimpleMath::Color diffuseColor = DirectX::SimpleMath::Color(1.0f, 0.95f, 0.9f);
				// ���C�g���Ƃ炷����
				DirectX::SimpleMath::Vector3 lightDirection(0.0f, 1.0f, 0.0f);
			
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);

				// �[���Ԃ̃��C�g�Ɋg�U���ˌ���ݒ肷��
				basicEffect->SetLightDiffuseColor(0, diffuseColor);
				// �[���Ԃ̃��C�g���Ƃ炷������ݒ肷��
				basicEffect->SetLightDirection(0, lightDirection);
			}
			});


		m_pendingModels.push_back(model); 
	}
	// �X�v���C�g��ǉ�
	void AddSprite(Image* sprite) { m_pendingSprite.push_back(sprite); }

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
	// �T���v���[�X�e�[�g�̍쐬
	void CreateSmplerState();


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
	// �T���v���[�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState;
	// ���̓��C�A�E�g
	ID3D11InputLayout* m_spriteInputLayout;

	// UI�̒��_�o�b�t�@�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_UIvertexBuffer;
	// ���_�V�F�[�_�[
	ID3D11VertexShader* m_UIvertexShader;
	// �W�I���g���V�F�[�_�[
	ID3D11GeometryShader* m_UIGeometryShader;

	// 2D�̃}�e���A�����i�[
	std::vector<Image*> m_sprite;
	// 2D �}�e���A���̏����i�K�f�[�^
	std::vector<Image*> m_pendingSprite;

	
	// �J�X�P�[�h�V���h�E�}�b�v�@�܂��J�X�P�[�h����Ă��Ȃ�
	std::unique_ptr<CascadedShadowMap> m_shadowMap;

	// ���f��
	std::vector<Model3D*> m_models;
	// ���f���@�����i�K�f�[�^
	std::vector<Model3D*> m_pendingModels;

	// �X�J�C�{�b�N�X
	std::unique_ptr<SkyBox> m_skyBox;
	// �f�B���N�V���i�����C�g
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_ambientLightBuffer;
	
};