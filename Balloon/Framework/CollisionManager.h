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

	//	// 同じ衝突ペアかどうかを判定（unordered_map のキー比較用）
	//	bool operator==(const CollisionPair& other) const {
	//		return objA == other.objA && objB == other.objB && colA == other.colA && colB == other.colB;
	//	}
	//};

	struct CollisionPair {
		int objA;
		int objB;
		ICollider* colA;
		ICollider* colB;

		// 同じ衝突ペアかどうかを判定（unordered_map のキー比較用）
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
	//	コンストラクタ
	CollisionManager();
	// デストラクタ
	~CollisionManager();
public:
	CollisionManager(const CollisionManager&) = delete;             // コピー禁止
	CollisionManager& operator=(const CollisionManager&) = delete;  // コピー代入禁止
	CollisionManager(const CollisionManager&&) = delete;            // ムーブ禁止
	CollisionManager& operator=(const CollisionManager&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static CollisionManager* GetInstance()
	{
		static CollisionManager instance;
		return &instance;
	}

	// 初期化処理
	void Initialize();
	// 当たり判定の処理
	void CheckCollision();
	// アタッチ
	void Attach(IObject* object , 
		std::vector<ICollider*> collider,PhysicsBody* physicsBody = nullptr);

	// スタート処理
	void Start();

	void Render();

private:
	// 衝突判定
	bool DetectCollisions(ICollider* collider1, ICollider* collider2);
	// メッセージの判定
	void HandleCollisionEvents(bool active,int index1 , int index2, IObject* object1, IObject* object2,
		ICollider* collider1, ICollider* collider2);


	// オブジェクト同士を円で大まかに判定を行う
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

	// 判定を保存する
	std::unordered_map<CollisionPair, bool, CollisionPairHash> m_collisionStates;

	// デバッグの時のみ作成
#ifdef _DEBUG
	// ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
#endif
};