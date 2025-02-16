#pragma once
#include "StateController.h"
#include "Parameters.h"
#include <iostream>
#include <vector>

class CommonResources;

class StateMachine
{
public:
	// �R���g���[���[��ǉ�����
	void AddController(std::unique_ptr<StateController> controller)
	{
		m_controllers.push_back(std::move(controller));
	}

public:
	// �R���X�g���N�^
	StateMachine();
	// �f�X�g���N�^
	~StateMachine() = default;
	
	// �X�V����
	void Update();
	// ��������
	void Start();


private:
	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �R���g���[���[���i�[
	std::vector<std::unique_ptr<StateController>> m_controllers;
};