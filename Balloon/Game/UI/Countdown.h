#pragma once

class Graphics;
class Sprite2DShader;

class Countdown
{
public:

	// �R���X�g���N�^
	Countdown();
	// �f�X�g���N�^
	~Countdown();


public:
	// ������
	void Initialize();
	// �X�V����
	bool Update(const float& elapsedTime);
	// �`�揈��
	void Render();

private:

	// �O���t�B�b�N
	Graphics* m_graphics;
	// 2D�}�e���A��
	std::unique_ptr<Sprite2DShader> m_FrameMaterial;
	std::unique_ptr<Sprite2DShader> m_ReadyMaterial;
	std::unique_ptr<Sprite2DShader> m_GoMaterial;

	float m_angle;

	// ���݂̎���
	float m_currentTime;
	// ���l
	float m_timer;
};