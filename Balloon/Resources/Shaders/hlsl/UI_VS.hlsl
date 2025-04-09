#include "UI.hlsli"

// ���_�V�F�[�_�[
GS_INPUT main(VS_INPUT input)
{
    GS_INPUT output;
    
    // ���_�ʒu��2D�X�N���[����Ԃɕϊ�
    output.position = float4(input.position.xy, 0.0f, 1.0f);
    // ���_�J���[��ݒ�
    output.color = input.color;
    // Normal��Z��������]�p�x�Ƃ��ė��p
    output.rotate = input.rotate;
    // �傫����n��
    output.scale = input.scale;
    // ��`����n��
    output.rect = input.rect;

    return output;
}