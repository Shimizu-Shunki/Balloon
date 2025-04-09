// ============================================
// 
// �t�@�C����: AABB.cpp
// �T�v: AABB�̔��菈��
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Framework/Collider/AABB.h"
#include "Game/PhysicsBody/PhysicsBody.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
AABB::AABB()
{

}

/// <summary>
/// ���菈��
/// </summary>
/// <param name="box1">�{�b�N�X1</param>
/// <param name="box2">�{�b�N�X2</param>
/// <returns>�Փ˂��Ă��邩</returns>
const bool AABB::Intersects(const DirectX::BoundingBox& box1, const DirectX::BoundingBox& box2)
{
	return box1.Intersects(box2);
}

/// <summary>
/// �����߂�����
/// </summary>
/// <param name="object1">�I�u�W�F�N�g1</param>
/// <param name="collider1">�����蔻��1</param>
/// <param name="physicsBody1">��������1</param>
/// <param name="object2">�I�u�W�F�N�g2</param>
/// <param name="collider2">�����蔻��2</param>
/// <param name="physicsBody2">��������2</param>
/// <returns></returns>
const void AABB::PushBack(IObject* object1, ICollider* collider1, PhysicsBody* physicsBody1,
    IObject* object2, ICollider* collider2, PhysicsBody* physicsBody2)
{
    // �I�u�W�F�N�g1�ƃI�u�W�F�N�g2�̃o�E���f�B���O�{�b�N�X���擾
    DirectX::BoundingBox collision1;
    DirectX::BoundingBox collision2;

    collision1.Center = collider1->GetTransform()->GetWorldPosition();
    collision2.Center = collider2->GetTransform()->GetWorldPosition();

    collision1.Extents = collider1->GetTransform()->GetWorldScale() / 2.0f;
    collision2.Extents = collider2->GetTransform()->GetWorldScale() / 2.0f;


    // ���S���W���擾
    const auto& center1 = collision1.Center;
    const auto& center2 = collision2.Center;

    // �e���ł̃I�[�o�[���b�v�ʂ��v�Z
    float xOverlap = (collision1.Extents.x + collision2.Extents.x) - std::abs(center1.x - center2.x);
    float yOverlap = (collision1.Extents.y + collision2.Extents.y) - std::abs(center1.y - center2.y);
    float zOverlap = (collision1.Extents.z + collision2.Extents.z) - std::abs(center1.z - center2.z);

    // �d�Ȃ肪�Ȃ��ꍇ�͉����߂��������s��Ȃ�
    if (xOverlap <= 0 || yOverlap <= 0 || zOverlap <= 0)
        return;

    // �ŏ��I�[�o�[���b�v���v�Z
    float minOverlap = std::min({ xOverlap, yOverlap, zOverlap });

    // **�I�u�W�F�N�g1���I�u�W�F�N�g2��Top�ɐڐG���Ă��邩����**
    bool isTopCollision = (minOverlap == yOverlap) && (center1.y > center2.y);

    // �����߂�����������
    DirectX::SimpleMath::Vector3 pushback = DirectX::SimpleMath::Vector3::Zero;
    if (minOverlap == xOverlap)
    {
        pushback.x = (center1.x > center2.x ? xOverlap : -xOverlap);
    }
    else if (minOverlap == yOverlap)
    {
        pushback.y = (center1.y > center2.y ? yOverlap : -yOverlap);
    }
    else if (minOverlap == zOverlap)
    {
        pushback.z = (center1.z > center2.z ? zOverlap : -zOverlap);
    }

    // �I�u�W�F�N�g�̎��ʂ��擾
    float mass1 = 1.0f;
    float mass2 = 1.0f;

    bool kinematic1 = false;
    bool kinematic2 = false;

    // �������W�b�g�{�f�B���Ȃ��ꍇ�����߂����������Ȃ�
    if (physicsBody1 == nullptr && physicsBody2 == nullptr)
    {
        return;
    }

    // ���ʂƃL�l�}�e�B�b�N���擾
    if (physicsBody1 != nullptr)
    {
        mass1      = physicsBody1->GetMass();
        kinematic1 = physicsBody1->GetIsKinematic();
    }
    if (physicsBody2 != nullptr)
    {
        mass2      = physicsBody2->GetMass();
        kinematic2 = physicsBody2->GetIsKinematic();
    }
       
    float totalMass = mass1 + mass2;

    DirectX::SimpleMath::Vector3 pushback1;
    DirectX::SimpleMath::Vector3 pushback2;

    // �����߂��𕪔z����
    if (!kinematic1 && !kinematic2 && physicsBody1 != nullptr && physicsBody2 != nullptr)
    {
        // �����߂������ʔ�ŕ��z
        pushback1 = pushback * (mass2 / totalMass);
        pushback2 = pushback * -(mass1 / totalMass);
    }
    else if (!kinematic1 && kinematic2)
    {
        // �����߂������ʔ�ŕ��z
        pushback1 = pushback;
        pushback2 = DirectX::SimpleMath::Vector3::Zero;
    }
    DirectX::SimpleMath::Vector3 as = object1->GetTransform()->GetLocalPosition();
    // �e��Transform�̃��[�J�����W�̈ʒu���X�V
    object1->GetTransform()->SetLocalPosition(object1->GetTransform()->GetLocalPosition() + pushback1);

    object2->GetTransform()->SetLocalPosition(object2->GetTransform()->GetLocalPosition() + pushback2);


    // �d�͐ݒ�
    if (isTopCollision && physicsBody1 != nullptr)
    {
        // Y�̑��x��0�ɂ���
        physicsBody1->SetVelocity({
            physicsBody1->GetVelocity().x,
            0.0f,
            physicsBody1->GetVelocity().z
         });

        // �d�͂𖳌���
        physicsBody1->SetUseGravity(false);
    }
    else if(!isTopCollision && physicsBody1 != nullptr)
    {
        // �d�͂�L����
        physicsBody1->SetUseGravity(true);
    }

    DirectX::SimpleMath::Vector3 ss = object1->GetTransform()->GetLocalPosition();

    // Transform�̍X�V���ēx�s��
    object1->GetTransform()->Update();
    object2->GetTransform()->Update();
}


/// <summary>
/// �㉺���E�O��̔��菈��
/// </summary>
/// <param name="box1">�����蔻��1</param>
/// <param name="box2">�����蔻��2</param>
/// <returns>���茋��</returns>
const int AABB::DetermineCollisionDirection(const DirectX::BoundingBox& box1, const DirectX::BoundingBox& box2)
{
    int direction = CollisionDirection::NONE;

    // ���S���W�ƃT�C�Y���擾
    DirectX::XMFLOAT3 center1 = box1.Center;
    DirectX::XMFLOAT3 extents1 = box1.Extents;

    DirectX::XMFLOAT3 center2 = box2.Center;
    DirectX::XMFLOAT3 extents2 = box2.Extents;

    // ���S���W�̍���
    float xDiff = center2.x - center1.x;
    float yDiff = center2.y - center1.y;
    float zDiff = center2.z - center1.z;

    // �������̔���i���E�j
    if (std::abs(xDiff) < (extents1.x + extents2.x)) {
        if (xDiff > 0) {
            direction |= CollisionDirection::RIGHT;  // �E���ɏՓ�
        }
        else if (xDiff < 0) {
            direction |= CollisionDirection::LEFT;   // �����ɏՓ�
        }
    }

    // �c�����̔���i�㉺�j
    if (std::abs(yDiff) < (extents1.y + extents2.y)) {
        if (yDiff > 0) {
            direction |= CollisionDirection::UP;     // �㑤�ɏՓ�
        }
        else if (yDiff < 0) {
            direction |= CollisionDirection::DOWN;   // �����ɏՓ�
        }
    }

    // ���s�������̔���i�O��j
    if (std::abs(zDiff) < (extents1.z + extents2.z)) {
        if (zDiff > 0) {
            direction |= CollisionDirection::FRONT;  // �O���ɏՓ�
        }
        else if (zDiff < 0) {
            direction |= CollisionDirection::BACK;   // �㑤�ɏՓ�
        }
    }

    return direction;
}