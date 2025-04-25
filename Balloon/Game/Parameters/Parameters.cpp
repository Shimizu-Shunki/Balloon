#include "pch.h"
#include <windows.h>
#include <commdlg.h>
#include "Game/Parameters/Parameters.h"
#include "Game/Parameters/ParameterKeys.h"
#include <iostream>
#include <fstream>
#include <imgui/imgui.h>


/// <summary>
/// コンストラクタ
/// </summary>
Parameters::Parameters()
    :
    m_parameters{}
{
}

/// <summary>
/// JOSNデータをロードする
/// </summary>
/// <param name="filepath">ファイルパス</param>
void Parameters::LoadFromJson(const std::string& filepath) 
{
    // JSONファイルを開く
    std::ifstream file(filepath);
    assert(file);
    // JSON をロード
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
/// JSONにパラメータを保存
/// </summary>
/// <param name="filepath">ファイルパス</param>
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
    // ファイルパスに対して
    std::ofstream out(filepath); 
    // JSON を出力（インデント 4）
    out << j.dump(4);                 
}


/// <summary>
/// ファイルを開く
/// </summary>
/// <returns>ファイルパス</returns>
std::string Parameters::OpenFile() const
{
    // ファイル名バッファ
    char fileName[MAX_PATH] = "";

    // ファイルダイアログ構造体を初期化
    OPENFILENAMEA ofn = {};
    // 構造体サイズ
    ofn.lStructSize = sizeof(ofn);
    // 結果として選択されたファイルパスが入るバッファ
    ofn.lpstrFile = fileName;
    // バッファのサイズ
    ofn.nMaxFile = MAX_PATH;

    // ファイル選択時のフィルター
    ofn.lpstrFilter = "JSON Files\0*.json\0All Files\0*.*\0";
    // 最初のフィルターをデフォルト
    ofn.nFilterIndex = 1;
    // 親ウィンドウ
    ofn.hwndOwner = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST |  // パスが存在する必要あり
        OFN_FILEMUSTEXIST;          // ファイルが存在する必要あり

    // ファイルを開くダイアログを表示し、選択された場合のみファイルパスを返す
    if (GetOpenFileNameA(&ofn)) {
        return fileName;
    }

    // キャンセルやエラー時は空文字列を返す
    return "";
}


/// <summary>
/// ファイルの保存先を指定
/// </summary>
/// <returns>ファイルパス</returns>
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
/// パラメータを取得する int
/// </summary>
/// <param name="key">キー</param>
/// <returns>int値</returns>
int Parameters::GetParameter(const ParameterKeysI& key) const
{
    // enum → string（キー名に変換）
    std::string keyStr = std::string(magic_enum::enum_name(key));

    // パラメータ検索
    auto it = m_parameters.find(keyStr);
    if (it != m_parameters.end() && std::holds_alternative<int>(it->second)) 
    {
        // 値を返す
        return std::get<int>(it->second);  
    }

    // 失敗時：0などの安全なデフォルトを返す
    return 0;
}

/// <summary>
/// パラメータを取得する float
/// </summary>
/// <param name="key">キー</param>
/// <returns>float値</returns>
float Parameters::GetParameter(const ParameterKeysF& key) const
{
    // enum → string（キー名に変換）
    std::string keyStr = std::string(magic_enum::enum_name(key));

    // パラメータ検索
    auto it = m_parameters.find(keyStr);
    if (it != m_parameters.end() && std::holds_alternative<float>(it->second))
    {
        // 値を返す
        return std::get<float>(it->second);
    }

    // 失敗時：0などの安全なデフォルトを返す
    return 0.0f;
}

/// <summary>
/// パラメータを取得する Vector3
/// </summary>
/// <param name="key">キー</param>
/// <returns>Vector3値</returns>
DirectX::SimpleMath::Vector3 Parameters::GetParameter(const ParameterKeysV& key) const
{
    // enum → string（キー名に変換）
    std::string keyStr = std::string(magic_enum::enum_name(key));

    // パラメータ検索
    auto it = m_parameters.find(keyStr);
    if (it != m_parameters.end() && std::holds_alternative<DirectX::SimpleMath::Vector3>(it->second))
    {
        // 値を返す
        return std::get<DirectX::SimpleMath::Vector3>(it->second);
    }

    // 失敗時：0などの安全なデフォルトを返す
    return DirectX::SimpleMath::Vector3::Zero;
}

/// <summary>
/// デバッグウィンドウ
/// </summary>
void Parameters::ShowImGuiEditor() 
{
    // パラメータマネージャーウィンドウを表示（上部にメニューバーを有効にする）
    ImGui::Begin("Parameter Editor", nullptr, ImGuiWindowFlags_MenuBar);

    // メニューバーの表示開始
    if (ImGui::BeginMenuBar()) {
        // 「Load」ボタンを押すとファイルダイアログからJSONを読み込む
        if (ImGui::Button("Load")) 
        {
            // ファイル選択
            const std::string path = this->OpenFile();  
            // ファイルパスが有効ならロード実行
            if (!path.empty()) LoadFromJson(path);      
        }

        // ボタンを同一行に表示
        ImGui::SameLine();

        // 「Save」ボタンを押すと保存ダイアログからJSONに保存
        if (ImGui::Button("Save")) 
        {
            // ファイル保存先選択
            const std::string path = this->SaveFile();  
            // パスが有効なら保存
            if (!path.empty()) SaveToJson(path);        
        }
        // メニューバー終了
        ImGui::EndMenuBar(); 
    }

    // タブバーの開始（View / Edit / Add タブ）
    if (ImGui::BeginTabBar("ParameterTabs")) {

        // パラメータ表示専用タブ
        if (ImGui::BeginTabItem("View")) {
            for (const auto& [key, value] : m_parameters) {
                // float型の表示
                if (std::holds_alternative<float>(value)) {
                    ImGui::Text("%s: %.2f", key.c_str(), std::get<float>(value));
                }
                // int型の表示
                else if (std::holds_alternative<int>(value)) {
                    ImGui::Text("%s: %d", key.c_str(), std::get<int>(value));
                }
                // Vector3型の表示
                else if (std::holds_alternative<DirectX::SimpleMath::Vector3>(value)) {
                    const auto& v = std::get<DirectX::SimpleMath::Vector3>(value);
                    ImGui::Text("%s: (%.2f, %.2f, %.2f)", key.c_str(), v.x, v.y, v.z);
                }
            }
            // 表示タブ終了
            ImGui::EndTabItem();  
        }

        // パラメータ編集用タブ
        if (ImGui::BeginTabItem("Edit")) {
            for (auto& [key, value] : m_parameters) {
                // floatの編集スライダー
                if (std::holds_alternative<float>(value)) {
                    float v = std::get<float>(value);
                    if (ImGui::SliderFloat(key.c_str(), &v, 0.0f, 100.0f)) value = v;
                }
                // intの編集スライダー
                else if (std::holds_alternative<int>(value)) {
                    int v = std::get<int>(value);
                    if (ImGui::SliderInt(key.c_str(), &v, 0, 100)) value = v;
                }
                // Vector3の編集スライダー
                else if (std::holds_alternative<DirectX::SimpleMath::Vector3>(value)) {
                    auto v = std::get<DirectX::SimpleMath::Vector3>(value);
                    if (ImGui::SliderFloat3(key.c_str(), &v.x, -100.0f, 100.0f)) value = v;
                }
            }
            // 編集タブ終了
            ImGui::EndTabItem();  
        }

        // 新規パラメータ追加用タブ
        if (ImGui::BeginTabItem("Add")) {
            // 入力状態保持用変数（static で状態保持）
            static char newName[64] = "";
            static int typeIndex = 0;
            static float fval = 0.0f;
            static int ival = 0;
            static DirectX::SimpleMath::Vector3 vec3val(0, 0, 0);

            // 型選択リスト
            const char* types[] = { "float", "int", "Vector3" };

            // パラメータ名の入力欄
            ImGui::InputText("Name", newName, sizeof(newName));
            // パラメータ型の選択（ドロップダウン）
            ImGui::Combo("Type", &typeIndex, types, IM_ARRAYSIZE(types));

            // 型に応じた入力欄
            if (typeIndex == 0) ImGui::InputFloat("Value", &fval);
            else if (typeIndex == 1) ImGui::InputInt("Value", &ival);
            else if (typeIndex == 2) ImGui::InputFloat3("Value", &vec3val.x);

            // 追加ボタン
            if (ImGui::Button("Add Parameter") && std::strlen(newName) > 0) {
                std::string name(newName);

                // 選択された型に応じて追加
                if (typeIndex == 0) m_parameters[name] = fval;
                else if (typeIndex == 1) m_parameters[name] = ival;
                else if (typeIndex == 2) m_parameters[name] = vec3val;
                // 入力欄をクリア
                std::memset(newName, 0, sizeof(newName)); 
            }
            // 追加タブ終了
            ImGui::EndTabItem();  
        }
        // タブバー終了
        ImGui::EndTabBar();  
    }
    // ウィンドウ終了
    ImGui::End();  
}


