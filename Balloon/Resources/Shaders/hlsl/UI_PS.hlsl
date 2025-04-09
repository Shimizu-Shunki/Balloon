
#include "UI.hlsli"


// UIシェーダーの基本構造

// テクスチャ
Texture2D tex : register(t0);
Texture2D ruleTex : register(t1);

// サンプラー
SamplerState sam : register(s0);

// ルール画像のアルファ値を取得する関数
float GetRuleAlpha(float2 uv)
{
    // ルール画像から値をサンプリング
    float4 rule = ruleTex.Sample(sam, uv);

    // アルファ値を線形補間
    float ret = lerp(0.0f, 1.0f, smoothstep(rule.r, rule.r + 0.1f, ruleProgress));

    // ルールの反転を適用
    ret = (ruleInverse != 0) ? 1.0f - ret : ret;

    return ret;
}

// メインのピクセルシェーダー
float4 main(PS_INPUT input) : SV_Target
{
    // UV座標の計算
    float2 uv;
    uv.x = lerp(input.rect.x, input.rect.z, input.uv.x) / textureSize.x;
    uv.y = lerp(input.rect.y, input.rect.w, input.uv.y) / textureSize.y;

    // テクスチャの色を取得
    float4 col = lerp(float4(0.0f,0.0f,0.0f,1.0f), tex.Sample(sam, uv), useTexture);
    
    // 頂点色を乗算
    col *= input.color;

    // ルール画像のアルファ値を適用
    col.a *= lerp(1.0f, GetRuleAlpha(input.uv), useRuleTexture);

    // 最終的な色を返す
    return col;
}