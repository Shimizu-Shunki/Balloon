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

    // �p�����[�^�[��ǉ�����
    void AddParameter(const std::string& name, ParameterValue value) {
        parameters[name] = value;
    }
    // �p�����[�^�[���擾����
    std::unordered_map<std::string, ParameterValue> GetParameter() const {
        return parameters;
    }

    bool HasParameter(const std::string& name) const {
        return parameters.find(name) != parameters.end();
    }

private:
    // �p�����[�^�[
    std::unordered_map<std::string, ParameterValue> parameters;
};