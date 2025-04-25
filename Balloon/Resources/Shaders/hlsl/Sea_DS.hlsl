#include "Sea.hlsli"


// 入力パッチの制御点
struct DS_CONTROL_POINT
{
    float3 position : POSITION; // 制御点の位置
    float2 uv : TEXCOORD; // UV座標
};

[domain("quad")] // 四角形パッチ
DS_OUTPUT main(
    DS_INPUT input, // テッセレーターからの入力
    const OutputPatch<HS_OUTPUT, 4> patch, // ハルシェーダーからの制御点データ
    const HS_CONSTANT_OUTPUT patchConstants // ハルシェーダーからのテッセレーション定数
)
{
    DS_OUTPUT output;

    // 制御点を補間してワールド空間の頂点位置を計算
    float3 worldPosition =
        patch[0].position * (1.0f - input.uvw.x) * (1.0f - input.uvw.y) +
        patch[1].position * input.uvw.x * (1.0f - input.uvw.y) +
        patch[2].position * input.uvw.x * input.uvw.y +
        patch[3].position * (1.0f - input.uvw.x) * input.uvw.y;

    // 波の計算
    float amplitude = 20.0f; // 波の振幅
    float frequency = 2.0f; // 波の密度
    float speed = 0.7f; // 波の速度
    worldPosition.y += amplitude * sin(frequency * worldPosition.x + speed * TessellationFactor.y);

    // ワールド空間 → クリップ空間に変換
    output.position = mul(float4(worldPosition, 1.0f), matWorld);
    output.position = mul(output.position, matView);
    output.position = mul(output.position, matProj);
    
    output.uv = input.uvw;

    return output;
}