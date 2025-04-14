// ============================================
// 
// ファイル名: StageResources.h
// 概要: ステージのデータのリソース（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Framework/Resources/StageResources.h"

/// <summary>
/// コンストラクタ
/// </summary>
StageResources::StageResources()
{

}

/// <summary>
/// リソースをロードする
/// </summary>
/// <param name="data"></param>
void StageResources::LoadResource(const nlohmann::json& data)
{
    // テクスチャ
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