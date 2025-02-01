#pragma once
// ���_�����E�L�[�ŉ�]�@�X�e�[�W�̏�̕��ɂ���Ƃ��͏ォ�猩���낷�`�A�X�e�[�W�̐^�񒆂�����ɂ���Ƃ��͒�������A�X�e�[�W�̉��̕��ɂ���Ƃ��͉�����@�㉺�L�[�őO��ړ�

class Graphics;
class InputManager;

class TPSCamera2
{
private:
	const int MIN_VALUE    = 4 ;
	const int MEDIAN_VALUE = 8 ;
	const int MAX_VALUE    = 16;


public:
	// �R���X�g���N�^
	TPSCamera2();
	// �f�X�g���N�^
	~TPSCamera2();

public:

	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsed_time, DirectX::SimpleMath::Vector3 const& position);
	// �r���[�s��v�Z����
	void CalculateViewMatrix();

private:

	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// �C���v�b�g�}�l�[�W���[
	InputManager* m_inputManager;

	// ���_
	DirectX::SimpleMath::Vector3 m_eye;
	// �����_
	DirectX::SimpleMath::Vector3 m_target;
	// ���̌���
	DirectX::SimpleMath::Vector3 m_up;

	// ���_���璍���_�܂ł̋���
	DirectX::SimpleMath::Vector3 m_distance;

	// ����]�i�x����]�j
	float m_pitch;
	// �c��]�i�w����]�j
	float m_yaw;

	// ��������I�u�W�F�N�g�̍��W
	DirectX::SimpleMath::Vector3 m_targetObjectPosition;

	// ���x
	float m_sensitivity;

	// ������]�p
	DirectX::SimpleMath::Quaternion m_initial_angle;
	// ���݂̉�]�p
	DirectX::SimpleMath::Quaternion m_current_angle;
};