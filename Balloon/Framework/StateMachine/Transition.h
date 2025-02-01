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

   // コンディションを取得する
    std::unordered_map<std::string, Parameters::ParameterValue> GetCondition() const {return m_condition;}

    // 次のステートを取得する
    IState* GetNextState() const { return m_nextState; }

private:
    // 遷移先のポインタを保存
    IState* m_nextState;
    // パラメーターの名前と条件
    std::unordered_map<std::string, Parameters::ParameterValue> m_condition;
    // 優先度
    int m_priority;
};