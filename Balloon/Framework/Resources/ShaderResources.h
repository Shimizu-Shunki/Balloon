// ============================================
// 
// �t�@�C����: ShaderResources.h
// �T�v: ShaderResources.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================

#pragma once
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <VertexTypes.h>


class ShaderResources
{
public:
	//	UI�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> UI_INPUT_LAYOUT;
	//	�C�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> SEA_INPUT_LAYOUT;
public:
	// UI �C���v�b�g���C�A�E�g���擾����
	ID3D11InputLayout* GetUIinputLayout() { return m_UIinputLayout.Get(); }
	// UI ���_�V�F�[�_�[���擾
	ID3D11VertexShader* GetUI_VS()        { return m_UI_VS.Get(); }
	// UI �W�I���g���V�F�[�_�[���擾
	ID3D11GeometryShader* GetUI_GS()      { return m_UI_GS.Get(); }
	// UI �s�N�Z���V�F�[�_�[���擾
	ID3D11PixelShader* GetUI_PS()         { return m_UI_PS.Get(); }
	// UI�i���o�[ �s�N�Z���V�F�[�_�[���擾
	ID3D11PixelShader* GetNumberPS() { return m_numberPS.Get(); }
	// UI�X�R�A�i���o�[ �s�N�Z���V�F�[�_�[���擾
	ID3D11PixelShader* GetScorePS() { return m_scorePS.Get(); }

	// �C �C���v�b�g���C�A�E�g���擾
	ID3D11InputLayout* GetSeaInputLayout() { return m_SeaInputLayout.Get(); }
	// �C ���_�V�F�[�_�[���擾
	ID3D11VertexShader* GetSeaVS()         { return m_SeaVS.Get(); }
	// �C �W�I���g���V�F�[�_�[���擾
	ID3D11HullShader* GetSeaHS()           { return m_SeaHS.Get(); }
	// �C �W�I���g���V�F�[�_�[���擾
	ID3D11DomainShader* GetSeaDS()         { return m_SeaDS.Get(); }
	// �C �s�N�Z���V�F�[�_�[���擾
	ID3D11PixelShader* GetSeaPS()          { return m_SeaPS.Get(); }

	// �����x�[�X�����_�����O �C���v�b�g���C�A�E�g���擾
	ID3D11InputLayout* GetPBRLitInputLayout() { return m_PBRLitInputLayout.Get(); }
	// �����x�[�X�����_�����O ���_�V�F�[�_�[���擾
	ID3D11VertexShader* GetPBRLitVS()         { return m_PBRLitVS.Get(); }
	// �����x�[�X�����_�����O �s�N�Z���V�F�[�_�[���擾
	ID3D11PixelShader* GetPBRLitPS()          { return m_PBRLitPS.Get(); }
	// ���D �s�N�Z���V�F�[�_�[���擾
	ID3D11PixelShader* GetBalloonPS() { return m_balloonPS.Get(); }

	// �e ���_�V�F�[�_�[���擾
	ID3D11VertexShader* GetShadowVS() { return m_ShadowVS.Get(); }
	// �e �s�N�Z���V�F�[�_�[���擾
	ID3D11PixelShader* GetShadowPS()  { return m_ShadowPS.Get(); }

	// �X�J�C�{�b�N�X ���_�V�F�[�_�[���擾
	ID3D11VertexShader* GetSkyBoxVS() { return m_skyBoxVS.Get(); }
	// �X�J�C�{�b�N�X �s�N�Z���V�F�[�_�[���擾
	ID3D11PixelShader* GetSkyBoxPS()  { return m_skyBoxPS.Get(); }

public:
	ShaderResources(const ShaderResources&) = delete;             // �R�s�[�֎~
	ShaderResources& operator=(const ShaderResources&) = delete;  // �R�s�[����֎~
	ShaderResources(const ShaderResources&&) = delete;            // ���[�u�֎~
	ShaderResources& operator=(const ShaderResources&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static ShaderResources* GetInstance()
	{
		static ShaderResources instance;
		return &instance;
	}
	// ���\�[�X�����[�h����
	void LoadResource(const nlohmann::json& data);

private:
	// �R���X�g���N�^
	ShaderResources();

private:
	// UI
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_UIinputLayout;
	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader>   m_UI_VS;
	// �W�I���g���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_UI_GS;
	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_UI_PS;

	// �i���o�[�@�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_numberPS;
	// �i���o�[�@�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_scorePS;

	// �C
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_SeaInputLayout;
	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader>   m_SeaVS;
	// �n���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11HullShader>     m_SeaHS;
	// �h���C���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11DomainShader>   m_SeaDS;
	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_SeaPS;

	// �����x�[�X�����_�����O
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_PBRLitInputLayout;
	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader>   m_PBRLitVS;
	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_PBRLitPS;

	// ���D�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_balloonPS;

	// �e
	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader>   m_ShadowVS;
	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_ShadowPS;

	// �X�J�C�{�b�N�X
	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader>   m_skyBoxVS;
	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_skyBoxPS;

};