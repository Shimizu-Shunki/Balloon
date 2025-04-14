// ============================================
// 
// �t�@�C����: StageResources.h
// �T�v: StageResources.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

class StageResources
{
public:
	struct StageData
	{
		int score;
		int time;
	};
public:
	// �X�e�[�W�f�[�^���擾����
	StageData GetStageData(int number) { return m_stageData[number]; }
	// �X�e�[�W�f�[�^��ݒ肷��
	void SetStageData(int number, StageData stageData) { m_stageData[number] = stageData; }

public:
	StageResources(const StageResources&) = delete;             // �R�s�[�֎~
	StageResources& operator=(const StageResources&) = delete;  // �R�s�[����֎~
	StageResources(const StageResources&&) = delete;            // ���[�u�֎~
	StageResources& operator=(const StageResources&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static StageResources* GetInstance()
	{
		static StageResources instance;
		return &instance;
	}

private:
	// �R���X�g���N�^
	StageResources();
	// �f�X�g���N�^
	~StageResources() = default;

public:
	// ���\�[�X�����[�h����
	void LoadResource(const nlohmann::json& data);

private:

	// �X�e�[�W�f�[�^
	std::unordered_map<int, StageData> m_stageData;

};