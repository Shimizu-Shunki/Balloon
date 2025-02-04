#pragma once
#include <vector>
#include <iostream>
#include "Interface/IState.h"
#include "Framework/StateMachine/Parameters.h"
#include "Framework/StateMachine/Transition.h"
#include <unordered_map>


class IState;
class Transition;
class Parameters;

class StateController
{
public:
   
    // パラメーターを取得する
    std::unordered_map<std::string, Parameters::ParameterValue> GetParameters() const { return m_parameters; }
    // 現在のステートを取得する
    IState* GetState() { return m_currentState; }

public:
    // ステートを追加する
    template <typename T, typename... Args>
    void AddState(std::string stateName, Args&&... args)
    {
        m_states.emplace(stateName,std::make_unique<T>(std::forward<Args>(args)...));
    }
    // パラメーターを追加する
    void AddParameters(std::string parameterName, Parameters::ParameterValue condition)
    {
        m_parameters.emplace(parameterName,condition);
    }
    // トランジションを追加する
    void AddTransition(std::string stateName, std::string toStateName, std::string parameterName, Parameters::ParameterValue condition);
    // パラメータを設定する
    void SetParameter(std::string parameterName, Parameters::ParameterValue condition);
   
private:
    // ステートを切り替える
    void ChageState(IState* nextState);

public:

    // ステートを設定
    void SetDeffultState(std::string stateName);

    // コンストラクタ
    StateController(bool mapMode = false);
    // トランジションの判定
    void CheckTransitions();


private:
    // パラメーター
    std::unordered_map<std::string, Parameters::ParameterValue> m_parameters;
    // トランジション
    std::unordered_map<IState*, std::vector<std::unique_ptr<Transition>>> m_transitions;

    // ステートの管理方法
    bool m_useMap;
    // ステート　管理方法　vector unordered_map
    // ステートの数　頻繁に切り替えを行う際などに応じて切り替える
    std::unordered_map<std::string, std::unique_ptr<IState>> m_states;

    // 現在のステート
    IState* m_currentState;
};