#pragma once
#include <vector>
#include <iostream>
#include "Interface/IState.h"
#include "Framework/StateMachine/Transition.h"
#include <unordered_map>


class IState;
class Transition;

class StateController
{
public:

    using ParameterValue = std::variant<int, float, bool>;
   
    // �p�����[�^�[���擾����
    std::unordered_map<std::string, ParameterValue> GetParameters() const { return m_parameters; }

    // ���݂̃X�e�[�g���擾����
    IState* GetState() { return m_currentState; }

public:
    // �X�e�[�g��ǉ�����
    template <typename T, typename... Args>
    void AddState(std::string stateName, Args&&... args)
    {
        m_states.emplace(stateName,std::make_unique<T>(std::forward<Args>(args)...));
    }
    
    // �g�����W�V������ǉ�����
    void AddTransition(std::string stateName, std::string toStateName, std::string parameterName, ParameterValue condition);


    // �p�����[�^�[��ǉ�����
    void AddParameters(std::string parameterName, ParameterValue condition)
    {
        m_parameters.emplace(parameterName, condition);
    }
    // �p�����[�^��ݒ肷��
    void SetParameter(std::string parameterName, ParameterValue condition);
   
   
private:
    // �X�e�[�g��؂�ւ���
    void ChageState(IState* nextState);

public:

    // �X�e�[�g��ݒ�
    void SetDeffultState(std::string stateName);

    // �R���X�g���N�^
    StateController();
    // �g�����W�V�����̔���
    void CheckTransitions();

private:
    // �X�e�[�g
    std::unordered_map<std::string, std::unique_ptr<IState>> m_states;
    // �p�����[�^�[
    std::unordered_map<std::string, ParameterValue> m_parameters;
    // �g�����W�V����
    std::unordered_map<IState*, std::vector<std::unique_ptr<Transition>>> m_transitions;

    // ���݂̃X�e�[�g
    IState* m_currentState;
};