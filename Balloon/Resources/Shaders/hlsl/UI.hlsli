
// 定数バッファ
cbuffer ConstBuffer : register(b0)
{
    float2 windowSize : packoffset(c0); // ウィンドウサイズ
    float2 textureSize : packoffset(c0.z); // テクスチャサイズ
    float useTexture : packoffset(c1); // テクスチャ使用フラグ
    float useRuleTexture : packoffset(c1.y); // ルール画像使用フラグ
    float ruleProgress : packoffset(c1.z); // ルール画像適用度
    float ruleInverse : packoffset(c1.w); // ルールの反転
    float4 time : packoffset(c2); // タイム
}

// 頂点入力
struct VS_INPUT
{
    float4 position : SV_Position; // 画像の中心座標
    float3 rotate : NORMAL;    // 回転角（法線として利用可能）
    float3 scale  : TEXCOORD0; // スケール
    float4 rect   : TEXCOORD1; // テクスチャの矩形情報
    float4 color  : COLOR;     // 頂点カラー
};

// ジオメトリシェーダー入力
struct GS_INPUT
{
    float4 position : SV_Position; // 画像の中心座標
    float  rotate : TEXCOORD0; // 回転角
    float3 scale  : TEXCOORD1; // スケール
    float4 rect   : TEXCOORD2; // テクスチャの矩形情報
    float4 color  : COLOR;     // 頂点カラー
};

// 頂点入力
struct PS_INPUT
{
    float4 position : SV_Position; // ピクセル位置
    float4 color    : COLOR;       // 頂点色
    float2 uv       : TEXCOORD0;   // UV座標
    float4 rect     : TEXCOORD1;   // UV座標の矩形範囲
};


