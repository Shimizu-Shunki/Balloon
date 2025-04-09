// ============================================
// 
// �t�@�C����: IComposite.h
// �T�v: �����I�u�W�F�N�g�̍\���E�������`����i�C���^�[�t�F�[�X�j
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IObject.h"
#include <SimpleMath.h>


class IComposite : public IObject
{
public:
	// �I�u�W�F�N�g��ǉ�����
	virtual void Attach(std::unique_ptr<IObject> object, IObject::ObjectID objectId,
		DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One
	) = 0;
	// �I�u�W�F�N�g���폜����
	virtual void Detach(std::unique_ptr<IObject> turretPart)  = 0;
};

