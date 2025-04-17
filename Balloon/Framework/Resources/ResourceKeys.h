#pragma once
#include <iostream>
#include <unordered_map>
 

// テクスチャID
enum class TextureKeyID : int
{
    Logo,
    Fade,
    ClearText,
    FailedText,
    Player,
    Enemy,
    Sea,
    ReadyGo,
    Numbers,
    Numbers1,
    MenuButton,
    MenuButtonFrame,
    MenuButtonFrame2,
    KeyGuide,
    StartText,
    PlayerIcon,
    PlaySceneKeysGuide,
    TimeFrame,
    ScoreFrame,
    BalloonGageFrame,
    BalloonGage,
    HeightMeter,
    HPGage,
    HPGageFrame,
    CloudFrame,
    StageSelectTexts,
    StageSelectKeyGuide,
    ResultText,
    ResultSceneKeyGuide,
    ResultSceneText,

    Meat,
    Wood,
    Rock,
    Cloud,

    CubeMap,
    EveningCubeMap,
    Balloon,
};
// モデルID
enum class ModelKeyID : int
{
    Head,
    EHead,
    Body,
    LeftArm,
    RightArm,
    LeftFoot,
    RightFoot,
    Balloon,
    Box,
    Cloud,
    Sphere,
    Torus
};

// ピクセルシェーダーID
enum class PS_ID : int
{
    PBRLit_PS,
    Balloon_PS,
    ShadowMap_PS,
    SkyBox_PS,
    Sea_PS,
    UI_PS,
    NumberUI_PS,
    ScoreUI_PS,
};


// 頂点シェーダーID
enum class VS_ID : int
{
    PBRLit_VS,
    ShadowMap_VS,
    SkyBox_VS,
    Sea_VS,
    UI_VS,
};

// ジオメトリシェーダーID
enum class GS_ID : int
{
    UI_GS,
};

// ハルシェーダーID
enum class HS_ID : int
{
    Sea_HS,
};

// ドメインシェーダーID
enum class DS_ID : int
{
    Sea_DS,
};
