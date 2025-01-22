#pragma once

class Graphics;
class Sprite2DShader;

class Timer
{
public:
	// �\���ݒ������
	void SetIsActive(bool isActive) { m_isActive = isActive; }

public:

	// �R���X�g���N�^
	Timer();
	// �f�X�g���N�^
	~Timer();


public:
	// ������
	void Initialize(const bool &isCountingUp , const float &timeLimit);
	// �X�V����
	void Update(const float& elapsedTime);
	// �`�揈��
	void Render();

public:
	// ���Z�b�g����
	void Reset();

private:

	// �O���t�B�b�N
	Graphics* m_graphics;
	// 2D�}�e���A��
	std::unique_ptr<Sprite2DShader> m_timerMaterial;

	std::unique_ptr<Sprite2DShader> m_timerFrameMaterial;

	std::unique_ptr<Sprite2DShader> m_timerNumberMaterial;

	// �\�����邩
	bool m_isActive;

	// �^�C�}�[���J�E���g�A�b�v���ǂ���
	bool m_isCountingUp;


	// ���݂̎���
	float m_currentTime;

	// ���l
	float m_timer;
};