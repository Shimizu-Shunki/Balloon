#pragma once
#include "Interface/IScene.h"
#include <Game/Material/SeaMaterial.h>


class CommonResources;
class PBRLit;
class SkyBox;

class DebugScene : public IScene
{
public:
	// �R���X�g���N�^
	DebugScene();
	// �f�X�g���N�^
	~DebugScene();

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

	DirectX::Model* m_sphereModel;
	DirectX::CommonStates* m_commonStates;

	// �f�o�b�O�J�����Ŏ���
	std::unique_ptr<DebugCamera> m_debugCamera;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	// ���C���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_mainTexture;
	// �m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_normalMap;
	// �L���[�u�}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_skyMap;

	// �u�����h�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;

	// �}�e���A��
	std::unique_ptr<PBRLit> m_PBRLit;

	// �萔�o�b�t�@�p�̃o�b�t�@�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	std::unique_ptr<SkyBox> m_skyBox;
};