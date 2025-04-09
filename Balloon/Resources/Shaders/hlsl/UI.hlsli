
// �萔�o�b�t�@
cbuffer ConstBuffer : register(b0)
{
    float2 windowSize : packoffset(c0); // �E�B���h�E�T�C�Y
    float2 textureSize : packoffset(c0.z); // �e�N�X�`���T�C�Y
    float useTexture : packoffset(c1); // �e�N�X�`���g�p�t���O
    float useRuleTexture : packoffset(c1.y); // ���[���摜�g�p�t���O
    float ruleProgress : packoffset(c1.z); // ���[���摜�K�p�x
    float ruleInverse : packoffset(c1.w); // ���[���̔��]
    float4 time : packoffset(c2); // �^�C��
}

// ���_����
struct VS_INPUT
{
    float4 position : SV_Position; // �摜�̒��S���W
    float3 rotate : NORMAL;    // ��]�p�i�@���Ƃ��ė��p�\�j
    float3 scale  : TEXCOORD0; // �X�P�[��
    float4 rect   : TEXCOORD1; // �e�N�X�`���̋�`���
    float4 color  : COLOR;     // ���_�J���[
};

// �W�I���g���V�F�[�_�[����
struct GS_INPUT
{
    float4 position : SV_Position; // �摜�̒��S���W
    float  rotate : TEXCOORD0; // ��]�p
    float3 scale  : TEXCOORD1; // �X�P�[��
    float4 rect   : TEXCOORD2; // �e�N�X�`���̋�`���
    float4 color  : COLOR;     // ���_�J���[
};

// ���_����
struct PS_INPUT
{
    float4 position : SV_Position; // �s�N�Z���ʒu
    float4 color    : COLOR;       // ���_�F
    float2 uv       : TEXCOORD0;   // UV���W
    float4 rect     : TEXCOORD1;   // UV���W�̋�`�͈�
};


