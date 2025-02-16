#pragma once
#include "Game/UI/JumpMemory.h"
#include "Game/UI/JumpFrame.h"
#include "Interface/ISprite.h"


class JumpFrame;
class JumpMemory;
class CommonResources;
class IObject;
class PhysicsBody;

class Jump
{
private:
	// �ő�W�����v��
	const int MAX_JUMPS = 10;
public:
	// �R���X�g���N�^
	Jump(PhysicsBody* physicBody);
	// �f�X�g���N�^
	~Jump() = default;

public:

	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �W�����v����
	float TryJump();

private:

	// ���L���\�[�X
	CommonResources* m_commonResources;

	// �ΏۃI�u�W�F�N�g
	IObject* m_object;

	PhysicsBody* m_physicBody;

	// ���݂̃W�����v��
	int currentJumps;
	// �N�[���_�E�����ԁi�b�j
	float cooldownTime;
	// 1�񕜂��Ƃ̎��ԁi�b�j
	float recoveryRate;
	// �Ō�̃W�����v����̌o�ߎ���
	float elapsedTimeSinceLastJump;
	// �N�[���_�E�������ǂ���
	bool isCooldown;

	// �W�����v�t���[��
	std::unique_ptr<ISprite> m_jumpFrame;
	// �W�����v������
	std::unique_ptr<ISprite> m_jumpMemory;
};