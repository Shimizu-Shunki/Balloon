#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Interface/ICollider.h"
#include "Interface/IObject.h"

class CommonResources;


class CollisionManager
{
private:

	struct CollisionPair {
		IObject* objA;
		IObject* objB;
		ICollider* colA;
		ICollider* colB;

		// 同じ衝突ペアかどうかを判定（unordered_map のキー比較用）
		bool operator==(const CollisionPair& other) const {
			return objA == other.objA && objB == other.objB && colA == other.colA && colB == other.colB;
		}
	};

	struct CollisionPairHash {
		std::size_t operator()(const CollisionPair& key) const {
			auto hash1 = std::hash<IObject*>  {}(key.objA);
			auto hash2 = std::hash<IObject*>  {}(key.objB);
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
	void Attach(IObject* object, ICollider* collider);
	// スタート処理
	void Start();

	void Render();

private:
	// 衝突判定
	void DetectCollisions(IObject* object1, IObject* object2, ICollider* collider1, ICollider* collider2);
	// オブジェクト同士を円で大まかに判定を行う
	bool CircleCollisionCheck(const DirectX::SimpleMath::Vector3& pos1, const DirectX::SimpleMath::Vector3& pos2);

private:

	// グラフィックス
	CommonResources* m_commonResources;

	// オブジェクト
	std::unordered_map<IObject*, std::vector<ICollider*>> m_objects;

	// 準備段階オブジェクト
	std::unordered_map<IObject*, std::vector<ICollider*>> m_pendingObjects;

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