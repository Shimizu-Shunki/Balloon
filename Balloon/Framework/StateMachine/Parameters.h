#pragma once
#include <variant>
#include <string>
#include <unordered_map>


class Parameters
{

public:
    Parameters();
    ~Parameters();

public:
    using ParameterValue = std::variant<int, float, bool>;

    // パラメーターを追加する
    void AddParameter(const std::string& name, ParameterValue value) {
        parameters[name] = value;
    }
    // パラメーターを取得する
    std::unordered_map<std::string, ParameterValue> GetParameter() const {
        return parameters;
    }

    bool HasParameter(const std::string& name) const {
        return parameters.find(name) != parameters.end();
    }

private:
    // パラメーター
    std::unordered_map<std::string, ParameterValue> parameters;
};