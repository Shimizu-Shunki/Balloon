#include "UI.hlsli"

// 頂点シェーダー
GS_INPUT main(VS_INPUT input)
{
    GS_INPUT output;
    
    // 頂点位置を2Dスクリーン空間に変換
    output.position = float4(input.position.xy, 0.0f, 1.0f);
    // 頂点カラーを設定
    output.color = input.color;
    // NormalのZ成分を回転角度として利用
    output.rotate = input.rotate;
    // 大きさを渡す
    output.scale = input.scale;
    // 矩形情報を渡す
    output.rect = input.rect;

    return output;
}