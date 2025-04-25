#include "pch.h"
#include "Game/Factorys/BalloonFactory.h"

// �p�[�c
#include "Game/Balloon/Balloon.h"
#include "Game/Balloon/BalloonBody.h"
#include "Game/Balloon/BalloonRope.h"


// �G�̍쐬
std::unique_ptr<IObject> BalloonFactory::CreateBalloon(
	IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		BalloonFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> player;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	player.reset(new Balloon(parent, objectID, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	player->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(player);
}

// �G�̑̂��쐬
std::unique_ptr<IObject> BalloonFactory::CreateBalloonBody(
	IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		BalloonFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> enemyBody;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	enemyBody.reset(new BalloonBody(parent, objectID, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	enemyBody->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(enemyBody);
}


// �G�̓����쐬
std::unique_ptr<IObject> BalloonFactory::CreateBalloonRope(
	IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		BalloonFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> enemyHead;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	enemyHead.reset(new BalloonRope(parent, objectID, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	enemyHead->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(enemyHead);
}


/// <summary>
/// ��]�x�N�g�����N�H�[�^�j�I���ɕϊ�����B
/// </summary>
/// <param name="rotation">��]��\���x�N�g���i�x���@�j</param>
/// <returns>�ϊ���̃N�H�[�^�j�I��</returns>
DirectX::SimpleMath::Quaternion BalloonFactory::ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation) {
	return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(rotation.y),
		DirectX::XMConvertToRadians(rotation.x),
		DirectX::XMConvertToRadians(rotation.z)
	);
}