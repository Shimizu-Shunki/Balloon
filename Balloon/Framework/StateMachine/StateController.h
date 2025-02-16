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
   
    // パラメーターを取得する
    std::unordered_map<std::string, ParameterValue> GetParameters() const { return m_parameters; }

    // 現在のステートを取得する
    IState* GetState() { return m_currentState; }

public:
    // ステートを追加する
    template <typename T, typename... Args>
    void AddState(std::string stateName, Args&&... args)
    {
        m_states.emplace(stateName,std::make_unique<T>(std::forward<Args>(args)...));
    }
    
    // トランジションを追加する
    void AddTransition(std::string stateName, std::string toStateName, std::string parameterName, ParameterValue condition);


    // パラメーターを追加する
    void AddParameters(std::string parameterName, ParameterValue condition)
    {
        m_parameters.emplace(parameterName, condition);
    }
    // パラメータを設定する
    void SetParameter(std::string parameterName, ParameterValue condition);
   
   
private:
    // ステートを切り替える
    void ChageState(IState* nextState);

public:

    // ステートを設定
    void SetDeffultState(std::string stateName);

    // コンストラクタ
    StateController();
    // トランジションの判定
    void CheckTransitions();

private:
    // ステート
    std::unordered_map<std::string, std::unique_ptr<IState>> m_states;
    // パラメーター
    std::unordered_map<std::string, ParameterValue> m_parameters;
    // トランジション
    std::unordered_map<IState*, std::vector<std::unique_ptr<Transition>>> m_transitions;

    // 現在のステート
    IState* m_currentState;
};