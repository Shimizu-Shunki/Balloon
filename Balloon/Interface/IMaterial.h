// ============================================
// 
// �t�@�C����: IMaterial.h
// �T�v: �}�e���A���̕`�搧����`����i�C���^�[�t�F�[�X�j
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Framework/pch.h"

class IMaterial
{
public:
	// ���z�f�X�g���N�^
	virtual ~IMaterial() = default;
	// �}�e���A���̕`��J�n����
	virtual void BeginMaterial() = 0;
	// �}�e���A���̕`��I������
	virtual void EndMaterial() = 0;
	// �萔�o�b�t�@���X�V
	virtual void UpdateConstBuffer() = 0;
	
};