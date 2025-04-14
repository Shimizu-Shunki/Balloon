// ============================================
// 
// �t�@�C����: StageResources.h
// �T�v: �X�e�[�W�̃f�[�^�̃��\�[�X�i�V���O���g���j
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Framework/Resources/StageResources.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
StageResources::StageResources()
{

}

/// <summary>
/// ���\�[�X�����[�h����
/// </summary>
/// <param name="data"></param>
void StageResources::LoadResource(const nlohmann::json& data)
{
    // �e�N�X�`��
    std::unordered_map<std::string, int> stageData;

    for (int i = 1; i < 6; i++)
    {
        std::string stage = "Stage" + std::to_string(i);

        if (data.contains(stage)) {
            for (const auto& entry : data[stage]) {

                for (const auto& [key, value] : entry.items()) {

                    stageData[key] = value;

                    m_stageData[i] = StageData{
                        stageData["score"],
                        stageData["time"]
                    };
                }
            }
        }
    }
}