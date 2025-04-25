#pragma once
#include "Interface/IState.h"

class PlayerAttackState : public IState
{
public:
	// �R���X�g���N�^
	PlayerAttackState();
	// �f�X�g���N�^
	~PlayerAttackState() = default;
	// ����������
	void Initialize() override;
	// ���O�X�V����
	void PreUpdate() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// ����X�V����
	void PostUpdate() override;
	// �㏈�����s��
	void Finalize() override;

public:




};