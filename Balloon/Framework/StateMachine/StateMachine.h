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
	
	// ����������
	// �X�V����
	void Update();

	void Start();

	StateMachine();

private:
	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �R���g���[���[���i�[
	std::vector<std::unique_ptr<StateController>> m_controllers;
};