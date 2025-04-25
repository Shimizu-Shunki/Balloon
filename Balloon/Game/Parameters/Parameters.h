#pragma once
#include <variant>
#include <SimpleMath.h>
#include <string>
#include "Game/Parameters/ParameterKeys.h"

class Parameters
{
public:

	// �o���A���g
	using ParameterValue = std::variant<float, int, DirectX::SimpleMath::Vector3>;
	using json = nlohmann::json;

	// �p�����[�^���擾 int
	int GetParameter(const ParameterKeysI& key) const;
	// �p�����[�^���擾 float
	float GetParameter(const ParameterKeysF& key) const;
	// �p�����[�^���擾 Vector3
	DirectX::SimpleMath::Vector3 GetParameter(const ParameterKeysV& key) const;

	// �f�o�b�O�E�B���h�E
	void ShowImGuiEditor();
private:

	// �t�@�C�����J��
	std::string OpenFile() const;
	// JSON�f�[�^�����[�h
	void LoadFromJson(const std::string& filepath);
	// �f�[�^��ۑ�
	std::string SaveFile() const;
	// JSON�f�[�^��ۑ�
	void SaveToJson(const std::string& filepath);

private:
	//	�R���X�g���N�^
	Parameters();
	//	�f�X�g���N�^
	~Parameters() = default;
public:
	Parameters(const Parameters&) = delete;             // �R�s�[�֎~
	Parameters& operator=(const Parameters&) = delete;  // �R�s�[����֎~
	Parameters(const Parameters&&) = delete;            // ���[�u�֎~
	Parameters& operator=(const Parameters&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static Parameters* GetInstance()
	{
		static Parameters instance;
		return &instance;
	}

private:

	// �p�����[�^�[
	std::unordered_map<std::string, ParameterValue> m_parameters;
};