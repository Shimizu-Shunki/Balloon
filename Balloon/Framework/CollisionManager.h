#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Interface/ICollider.h"
#include "Interface/IObject.h"

class CommonResources;
class CollisionMessenger;
class PhysicsBody;


class CollisionManager
{
private:

	//struct CollisionPair {
	//	IObject* objA;
	//	IObject* objB;
	//	ICollider* colA;
	//	ICollider* colB;

	//	// �����Փ˃y�A���ǂ����𔻒�iunordered_map �̃L�[��r�p�j
	//	bool operator==(const CollisionPair& other) const {
	//		return objA == other.objA && objB == other.objB && colA == other.colA && colB == other.colB;
	//	}
	//};

	struct CollisionPair {
		int objA;
		int objB;
		ICollider* colA;
		ICollider* colB;

		// �����Փ˃y�A���ǂ����𔻒�iunordered_map �̃L�[��r�p�j
		bool operator==(const CollisionPair& other) const {
			return objA == other.objA && objB == other.objB && colA == other.colA && colB == other.colB;
		}
	};

	struct CollisionPairHash {
		std::size_t operator()(const CollisionPair& key) const {
			auto hash1 = std::hash<int>  {}(key.objA);
			auto hash2 = std::hash<int>  {}(key.objB);
			auto hash3 = std::hash<ICollider*>{}(key.colA);
			auto hash4 = std::hash<ICollider*>{}(key.colB);
			return hash1 ^ (hash2 << 1) ^ (hash3 << 2) ^ (hash4 << 3);
		}
	};

private:
	//	�R���X�g���N�^
	CollisionManager();
	// �f�X�g���N�^
	~CollisionManager();
public:
	CollisionManager(const CollisionManager&) = delete;             // �R�s�[�֎~
	CollisionManager& operator=(const CollisionManager&) = delete;  // �R�s�[����֎~
	CollisionManager(const CollisionManager&&) = delete;            // ���[�u�֎~
	CollisionManager& operator=(const CollisionManager&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static CollisionManager* GetInstance()
	{
		static CollisionManager instance;
		return &instance;
	}

	// ����������
	void Initialize();
	// �����蔻��̏���
	void CheckCollision();
	// �A�^�b�`
	void Attach(IObject* object , 
		std::vector<ICollider*> collider,PhysicsBody* physicsBody = nullptr);

	// �X�^�[�g����
	void Start();

	void Render();

private:
	// �Փ˔���
	bool DetectCollisions(ICollider* collider1, ICollider* collider2);
	// ���b�Z�[�W�̔���
	void HandleCollisionEvents(bool active,int index1 , int index2, IObject* object1, IObject* object2,
		ICollider* collider1, ICollider* collider2);


	// �I�u�W�F�N�g���m���~�ő�܂��ɔ�����s��
	bool CircleCollisionCheck(const DirectX::SimpleMath::Vector3& pos1, const DirectX::SimpleMath::Vector3& pos2);

private:

	
	CommonResources* m_commonResources;

	CollisionMessenger* m_collisionMessenger;

	std::unordered_map<int, PhysicsBody*> m_pendingPhysicsBodys;
	std::unordered_map<int, PhysicsBody*> m_physicsBodys;

	std::unordered_map<int, std::vector<ICollider*>> m_pendingCollider;
	std::unordered_map<int, std::vector<ICollider*>> m_Collider;

	int m_pendingObjectIndex;
	int m_objectIndex;

	// �����ۑ�����
	std::unordered_map<CollisionPair, bool, CollisionPairHash> m_collisionStates;

	// �f�o�b�O�̎��̂ݍ쐬
#ifdef _DEBUG
	// �x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
#endif
};