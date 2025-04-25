#include "Sea.hlsli"


// ���̓p�b�`�̐���_
struct DS_CONTROL_POINT
{
    float3 position : POSITION; // ����_�̈ʒu
    float2 uv : TEXCOORD; // UV���W
};

[domain("quad")] // �l�p�`�p�b�`
DS_OUTPUT main(
    DS_INPUT input, // �e�b�Z���[�^�[����̓���
    const OutputPatch<HS_OUTPUT, 4> patch, // �n���V�F�[�_�[����̐���_�f�[�^
    const HS_CONSTANT_OUTPUT patchConstants // �n���V�F�[�_�[����̃e�b�Z���[�V�����萔
)
{
    DS_OUTPUT output;

    // ����_���Ԃ��ă��[���h��Ԃ̒��_�ʒu���v�Z
    float3 worldPosition =
        patch[0].position * (1.0f - input.uvw.x) * (1.0f - input.uvw.y) +
        patch[1].position * input.uvw.x * (1.0f - input.uvw.y) +
        patch[2].position * input.uvw.x * input.uvw.y +
        patch[3].position * (1.0f - input.uvw.x) * input.uvw.y;

    // �g�̌v�Z
    float amplitude = 20.0f; // �g�̐U��
    float frequency = 2.0f; // �g�̖��x
    float speed = 0.7f; // �g�̑��x
    worldPosition.y += amplitude * sin(frequency * worldPosition.x + speed * TessellationFactor.y);

    // ���[���h��� �� �N���b�v��Ԃɕϊ�
    output.position = mul(float4(worldPosition, 1.0f), matWorld);
    output.position = mul(output.position, matView);
    output.position = mul(output.position, matProj);
    
    output.uv = input.uvw;

    return output;
}