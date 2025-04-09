// ============================================
// 
// �t�@�C����: ISprite.h
// �T�v: UI�X�v���C�g�̒��_���擾���`����i�C���^�[�t�F�[�X�j
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Framework/pch.h"
#include "Game/Material/Buffers.h"
#include "Interface/IMaterial.h"

class ISprite : public IMaterial
{
public:
	virtual const UIVertexBuffer* GetVertexBuffer() const = 0;
};