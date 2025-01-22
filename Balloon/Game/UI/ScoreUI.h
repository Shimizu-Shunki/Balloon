#pragma once

class Graphics;
class Sprite2DShader;

class Score
{
public:
	// �X�R�A�̒l��ݒ肷��
	void SetScore(const int score) { m_score = score; }
	// �X�R�A�̒l���擾����
	int GetScore() const { return m_score; }
	// �X�R�A���Z�b�g
	void ResetScore() { m_score = 0; }

public:

	// �R���X�g���N�^
	Score();
	// �f�X�g���N�^
	~Score();

public:

	// ������
	void Initialize();
	// �`�揈��
	void Render();

private:
	// ���l
	int m_score;
	// 2D�}�e���A��
	std::unique_ptr<Sprite2DShader> m_scoreMaterial;
};