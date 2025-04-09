
// DirectXTK�ŕW���I�ɒ�`����Ă���p�����[�^
Texture2D<float4> Texture : register(t0);
sampler Sampler : register(s0);

cbuffer Parameters : register(b0)
{
    float4 DiffuseColor  : packoffset(c0);
    float3 EmissiveColor : packoffset(c1);
    float3 SpecularColor : packoffset(c2);
    float SpecularPower  : packoffset(c2.w);

    float3 LightDirection[3]     : packoffset(c3);
    float3 LightDiffuseColor[3]  : packoffset(c6);
    float3 LightSpecularColor[3] : packoffset(c9);

    float3 EyePosition : packoffset(c12);

    float3 FogColor  : packoffset(c13);
    float4 FogVector : packoffset(c14);

    float4x4 World                 : packoffset(c15);
    float3x3 WorldInverseTranspose : packoffset(c19);
    float4x4 WorldViewProj         : packoffset(c22);
};

// ���C�g�p�萔�o�b�t�@
cbuffer LightParameters : register(b1)
{
    float4x4 lightViewProjection : packoffset(c0);
    float4 lightPosition         : packoffset(c4);
    float3 lightDirirection      : packoffset(c5);
    float3 lightAmbient          : packoffset(c6);
};

// �X�J�C�X�t�B�A�e�N�X�`��
// Texture2D<float4> skySphereTexture : register(t1);

