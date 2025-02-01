#pragma once
#include <variant>
#include <string>
#include <unordered_map>
#include "Interface/IState.h"
#include "Parameters.h"

class IState;

class Transition
{
public:
    Transition(IState* nextState,std::string parameterName, Parameters::ParameterValue condition,int priority = 0);

   // �R���f�B�V�������擾����
    std::unordered_map<std::string, Parameters::ParameterValue> GetCondition() const {return m_condition;}

    // ���̃X�e�[�g���擾����
    IState* GetNextState() const { return m_nextState; }

private:
    // �J�ڐ�̃|�C���^��ۑ�
    IState* m_nextState;
    // �p�����[�^�[�̖��O�Ə���
    std::unordered_map<std::string, Parameters::ParameterValue> m_condition;
    // �D��x
    int m_priority;
};