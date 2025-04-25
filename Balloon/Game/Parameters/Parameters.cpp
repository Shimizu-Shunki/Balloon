#include "pch.h"
#include <windows.h>
#include <commdlg.h>
#include "Game/Parameters/Parameters.h"
#include "Game/Parameters/ParameterKeys.h"
#include <iostream>
#include <fstream>
#include <imgui/imgui.h>


/// <summary>
/// �R���X�g���N�^
/// </summary>
Parameters::Parameters()
    :
    m_parameters{}
{
}

/// <summary>
/// JOSN�f�[�^�����[�h����
/// </summary>
/// <param name="filepath">�t�@�C���p�X</param>
void Parameters::LoadFromJson(const std::string& filepath) 
{
    // JSON�t�@�C�����J��
    std::ifstream file(filepath);
    assert(file);
    // JSON �����[�h
    json data;
    file >> data;

    for (auto& [key, val] : data.items()) {
        if (val.is_number_float()) {
            m_parameters[key] = val.get<float>();
        }
        else if (val.is_number_integer()) {
            m_parameters[key] = val.get<int>();
        }
        else if (val.is_array() && val.size() == 3) {
            DirectX::SimpleMath::Vector3 vec(val[0].get<float>(), val[1].get<float>(), val[2].get<float>());
            m_parameters[key] = vec;
        }
    }
}

/// <summary>
/// JSON�Ƀp�����[�^��ۑ�
/// </summary>
/// <param name="filepath">�t�@�C���p�X</param>
void Parameters::SaveToJson(const std::string& filepath)
{
    json j;
    for (const auto& [key, val] : m_parameters)
    {
        if (std::holds_alternative<float>(val))
        {
            j[key] = std::get<float>(val);
        }
        else if (std::holds_alternative<int>(val))
        {
            j[key] = std::get<int>(val);
        }
        else if (std::holds_alternative<DirectX::SimpleMath::Vector3>(val))
        {
            const auto& v = std::get<DirectX::SimpleMath::Vector3>(val);
            j[key] = { v.x, v.y, v.z };
        }
    }
    // �t�@�C���p�X�ɑ΂���
    std::ofstream out(filepath); 
    // JSON ���o�́i�C���f���g 4�j
    out << j.dump(4);                 
}


/// <summary>
/// �t�@�C�����J��
/// </summary>
/// <returns>�t�@�C���p�X</returns>
std::string Parameters::OpenFile() const
{
    // �t�@�C�����o�b�t�@
    char fileName[MAX_PATH] = "";

    // �t�@�C���_�C�A���O�\���̂�������
    OPENFILENAMEA ofn = {};
    // �\���̃T�C�Y
    ofn.lStructSize = sizeof(ofn);
    // ���ʂƂ��đI�����ꂽ�t�@�C���p�X������o�b�t�@
    ofn.lpstrFile = fileName;
    // �o�b�t�@�̃T�C�Y
    ofn.nMaxFile = MAX_PATH;

    // �t�@�C���I�����̃t�B���^�[
    ofn.lpstrFilter = "JSON Files\0*.json\0All Files\0*.*\0";
    // �ŏ��̃t�B���^�[���f�t�H���g
    ofn.nFilterIndex = 1;
    // �e�E�B���h�E
    ofn.hwndOwner = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST |  // �p�X�����݂���K�v����
        OFN_FILEMUSTEXIST;          // �t�@�C�������݂���K�v����

    // �t�@�C�����J���_�C�A���O��\�����A�I�����ꂽ�ꍇ�̂݃t�@�C���p�X��Ԃ�
    if (GetOpenFileNameA(&ofn)) {
        return fileName;
    }

    // �L�����Z����G���[���͋󕶎����Ԃ�
    return "";
}


/// <summary>
/// �t�@�C���̕ۑ�����w��
/// </summary>
/// <returns>�t�@�C���p�X</returns>
std::string Parameters::SaveFile() const
{
    char filename[MAX_PATH] = "params.json";
    OPENFILENAMEA ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "JSON Files\0*.json\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

    if (GetSaveFileNameA(&ofn)) {
        return filename;
    }
    return "";
}

/// <summary>
/// �p�����[�^���擾���� int
/// </summary>
/// <param name="key">�L�[</param>
/// <returns>int�l</returns>
int Parameters::GetParameter(const ParameterKeysI& key) const
{
    // enum �� string�i�L�[���ɕϊ��j
    std::string keyStr = std::string(magic_enum::enum_name(key));

    // �p�����[�^����
    auto it = m_parameters.find(keyStr);
    if (it != m_parameters.end() && std::holds_alternative<int>(it->second)) 
    {
        // �l��Ԃ�
        return std::get<int>(it->second);  
    }

    // ���s���F0�Ȃǂ̈��S�ȃf�t�H���g��Ԃ�
    return 0;
}

/// <summary>
/// �p�����[�^���擾���� float
/// </summary>
/// <param name="key">�L�[</param>
/// <returns>float�l</returns>
float Parameters::GetParameter(const ParameterKeysF& key) const
{
    // enum �� string�i�L�[���ɕϊ��j
    std::string keyStr = std::string(magic_enum::enum_name(key));

    // �p�����[�^����
    auto it = m_parameters.find(keyStr);
    if (it != m_parameters.end() && std::holds_alternative<float>(it->second))
    {
        // �l��Ԃ�
        return std::get<float>(it->second);
    }

    // ���s���F0�Ȃǂ̈��S�ȃf�t�H���g��Ԃ�
    return 0.0f;
}

/// <summary>
/// �p�����[�^���擾���� Vector3
/// </summary>
/// <param name="key">�L�[</param>
/// <returns>Vector3�l</returns>
DirectX::SimpleMath::Vector3 Parameters::GetParameter(const ParameterKeysV& key) const
{
    // enum �� string�i�L�[���ɕϊ��j
    std::string keyStr = std::string(magic_enum::enum_name(key));

    // �p�����[�^����
    auto it = m_parameters.find(keyStr);
    if (it != m_parameters.end() && std::holds_alternative<DirectX::SimpleMath::Vector3>(it->second))
    {
        // �l��Ԃ�
        return std::get<DirectX::SimpleMath::Vector3>(it->second);
    }

    // ���s���F0�Ȃǂ̈��S�ȃf�t�H���g��Ԃ�
    return DirectX::SimpleMath::Vector3::Zero;
}

/// <summary>
/// �f�o�b�O�E�B���h�E
/// </summary>
void Parameters::ShowImGuiEditor() 
{
    // �p�����[�^�}�l�[�W���[�E�B���h�E��\���i�㕔�Ƀ��j���[�o�[��L���ɂ���j
    ImGui::Begin("Parameter Editor", nullptr, ImGuiWindowFlags_MenuBar);

    // ���j���[�o�[�̕\���J�n
    if (ImGui::BeginMenuBar()) {
        // �uLoad�v�{�^���������ƃt�@�C���_�C�A���O����JSON��ǂݍ���
        if (ImGui::Button("Load")) 
        {
            // �t�@�C���I��
            const std::string path = this->OpenFile();  
            // �t�@�C���p�X���L���Ȃ烍�[�h���s
            if (!path.empty()) LoadFromJson(path);      
        }

        // �{�^���𓯈�s�ɕ\��
        ImGui::SameLine();

        // �uSave�v�{�^���������ƕۑ��_�C�A���O����JSON�ɕۑ�
        if (ImGui::Button("Save")) 
        {
            // �t�@�C���ۑ���I��
            const std::string path = this->SaveFile();  
            // �p�X���L���Ȃ�ۑ�
            if (!path.empty()) SaveToJson(path);        
        }
        // ���j���[�o�[�I��
        ImGui::EndMenuBar(); 
    }

    // �^�u�o�[�̊J�n�iView / Edit / Add �^�u�j
    if (ImGui::BeginTabBar("ParameterTabs")) {

        // �p�����[�^�\����p�^�u
        if (ImGui::BeginTabItem("View")) {
            for (const auto& [key, value] : m_parameters) {
                // float�^�̕\��
                if (std::holds_alternative<float>(value)) {
                    ImGui::Text("%s: %.2f", key.c_str(), std::get<float>(value));
                }
                // int�^�̕\��
                else if (std::holds_alternative<int>(value)) {
                    ImGui::Text("%s: %d", key.c_str(), std::get<int>(value));
                }
                // Vector3�^�̕\��
                else if (std::holds_alternative<DirectX::SimpleMath::Vector3>(value)) {
                    const auto& v = std::get<DirectX::SimpleMath::Vector3>(value);
                    ImGui::Text("%s: (%.2f, %.2f, %.2f)", key.c_str(), v.x, v.y, v.z);
                }
            }
            // �\���^�u�I��
            ImGui::EndTabItem();  
        }

        // �p�����[�^�ҏW�p�^�u
        if (ImGui::BeginTabItem("Edit")) {
            for (auto& [key, value] : m_parameters) {
                // float�̕ҏW�X���C�_�[
                if (std::holds_alternative<float>(value)) {
                    float v = std::get<float>(value);
                    if (ImGui::SliderFloat(key.c_str(), &v, 0.0f, 100.0f)) value = v;
                }
                // int�̕ҏW�X���C�_�[
                else if (std::holds_alternative<int>(value)) {
                    int v = std::get<int>(value);
                    if (ImGui::SliderInt(key.c_str(), &v, 0, 100)) value = v;
                }
                // Vector3�̕ҏW�X���C�_�[
                else if (std::holds_alternative<DirectX::SimpleMath::Vector3>(value)) {
                    auto v = std::get<DirectX::SimpleMath::Vector3>(value);
                    if (ImGui::SliderFloat3(key.c_str(), &v.x, -100.0f, 100.0f)) value = v;
                }
            }
            // �ҏW�^�u�I��
            ImGui::EndTabItem();  
        }

        // �V�K�p�����[�^�ǉ��p�^�u
        if (ImGui::BeginTabItem("Add")) {
            // ���͏�ԕێ��p�ϐ��istatic �ŏ�ԕێ��j
            static char newName[64] = "";
            static int typeIndex = 0;
            static float fval = 0.0f;
            static int ival = 0;
            static DirectX::SimpleMath::Vector3 vec3val(0, 0, 0);

            // �^�I�����X�g
            const char* types[] = { "float", "int", "Vector3" };

            // �p�����[�^���̓��͗�
            ImGui::InputText("Name", newName, sizeof(newName));
            // �p�����[�^�^�̑I���i�h���b�v�_�E���j
            ImGui::Combo("Type", &typeIndex, types, IM_ARRAYSIZE(types));

            // �^�ɉ��������͗�
            if (typeIndex == 0) ImGui::InputFloat("Value", &fval);
            else if (typeIndex == 1) ImGui::InputInt("Value", &ival);
            else if (typeIndex == 2) ImGui::InputFloat3("Value", &vec3val.x);

            // �ǉ��{�^��
            if (ImGui::Button("Add Parameter") && std::strlen(newName) > 0) {
                std::string name(newName);

                // �I�����ꂽ�^�ɉ����Ēǉ�
                if (typeIndex == 0) m_parameters[name] = fval;
                else if (typeIndex == 1) m_parameters[name] = ival;
                else if (typeIndex == 2) m_parameters[name] = vec3val;
                // ���͗����N���A
                std::memset(newName, 0, sizeof(newName)); 
            }
            // �ǉ��^�u�I��
            ImGui::EndTabItem();  
        }
        // �^�u�o�[�I��
        ImGui::EndTabBar();  
    }
    // �E�B���h�E�I��
    ImGui::End();  
}


