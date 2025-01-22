#pragma once
#pragma once
#ifndef GRAPHICS_DEFINED
#define GRAPHICS_DEFINED
#include <Framework/DeviceResources.h>
//#include "InputManager.h"

// DirectX Graphics�N���X
class Graphics final
{
public:
	// Graphics�N���X�̃C���X�^���X���擾����
	static Graphics* const GetInstance();

	// �X�N���[���T�C�Y���擾����
	void GetScreenSize(int& width, int& height) const { width = m_screenW; height = m_screenH; }
	// �X�N���[���T�C�Y��ݒ肷��
	void SetScreenSize(const int& width, const int& height) { m_screenW = width; m_screenH = height; }

	// �f�o�C�X���\�[�X���擾����
	DX::DeviceResources* GetDeviceResources() const { return m_device_resources.get(); }
	// �v���~�e�B�u�o�b�`���擾����
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* GetPrimitiveBatch() const { return m_primitive_batch_color.get(); }
	// �C���v�b�g���C�A�E�g���擾����
	ID3D11InputLayout* GetInputLayout() const { return m_input_layout.Get(); }
	// �x�C�V�b�N�G�t�F�N�g���擾����
	DirectX::BasicEffect* GetBasicEffect() { return m_basic_effect.get(); }
	// �R�����X�e�[�g���擾����
	DirectX::CommonStates* GetCommonStates() const { return m_common_states.get(); }
	// �X�v���C�g�o�b�`���擾����
	DirectX::SpriteBatch* GetSpriteBatch() { return m_sprite_batch.get(); }
	// �X�v���C�g�t�H���g���擾����
	DirectX::SpriteFont* GetFont() { return m_sprite_font.get(); }
	// �G�t�F�N�g�t�@�N�g�����擾����
	DirectX::EffectFactory* GetFX() const { return m_effect_factory.get(); }
	// �r���[�s���ݒ肷��
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& view) { m_view = view; }
	// �r���[�s����擾����
	const DirectX::SimpleMath::Matrix& GetViewMatrix() { return m_view; };
	// �ˉe�s���ݒ肷��
	void SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection) { m_projection = projection; }
	// �ˉe�s����擾����
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() { return m_projection; };

public:
	// �f�X�g���N�^
	~Graphics();
	// ����������
	void Initialize(HWND window);
	// �������`�悷��
	void DrawString(const float& x, const float& y, const wchar_t* str);
	// �v���~�e�B�u�`����J�n����
	void DrawPrimitiveBegin(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	// �v���~�e�B�u�`����I������
	void DrawPrimitiveEnd();
	// ������`�悷��(XZ����)
	void DrawLine(const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& vector, const DirectX::FXMVECTOR& color);
	// ������`�悷��
	void DrawLine(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& vector, const DirectX::FXMVECTOR& color);
	// �x�N�g����`�悷��(XZ����)
	void DrawVector(const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& vector, const DirectX::FXMVECTOR& color);
	void DrawVector(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& vector, const DirectX::FXMVECTOR& color);

	// �~��`�悷��(XZ����)
	void DrawCircle(const DirectX::SimpleMath::Vector2& center, const float& radius, const DirectX::FXMVECTOR& m_color = DirectX::Colors::White, const int& split = 32);
	// �~��`�悷��
	void DrawCircle(const DirectX::SimpleMath::Vector3& center, const float& radius, const DirectX::FXMVECTOR& m_color = DirectX::Colors::White, const int& split = 32);
	// ��`��`�悷��
	void DrawQuad(const DirectX::VertexPositionColor& vector1, const DirectX::VertexPositionColor& vector2, const DirectX::VertexPositionColor& vector3, const DirectX::VertexPositionColor& vector4);
	void DrawQuad(const DirectX::FXMVECTOR& point1, const DirectX::FXMVECTOR& point2, const DirectX::FXMVECTOR& point3, const DirectX::FXMVECTOR& point4, const DirectX::HXMVECTOR& color);
	// ���f����`�悷��
	void DrawModel(const DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection, const bool& depthBuffer = true);
	// �O���b�h����`�悷��
	void DrawGridFloor(
		DirectX::SimpleMath::Vector3 width,
		DirectX::SimpleMath::Vector3 height,
		size_t dive);
private:
	// �R���X�g���N�^
	Graphics();

	// ����͋��e���Ȃ�
	void operator=(const Graphics& object) = delete;
	// �R�s�[�R���X�g���N�^�͋��e���Ȃ�
	Graphics(const Graphics& object) = delete;

private:
	// Graphics�N���X�̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<Graphics> m_graphics;

	// �X�N���[���T�C�Y
	int m_screenW, m_screenH;

	// �f�o�C�X���\�[�X
	std::unique_ptr<DX::DeviceResources> m_device_resources;
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_common_states;

	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_sprite_batch;
	// �X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_sprite_font;

	// �x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basic_effect;
	// �v���~�e�B�u�o�b�`�@���W�@�J���[
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitive_batch_color;
	// �v���~�e�B�u�o�b�`�@���W
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPosition>> m_primitive_batch_position;
	// �v���~�e�B�u�o�b�`�@�e�N�X�`��
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitive_batch_texture;


	// �G�t�F�N�g�t�@�N�g���[
	std::unique_ptr<DirectX::EffectFactory> m_effect_factory;
	// ���X�^���C�U�[�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterrizer_state;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_input_layout;
	
	// �f�o�C�X
	ID3D11Device* m_device;
	// �f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* m_context;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;
};

#endif		// GRAPHICS_DEFINED