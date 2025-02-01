#pragma once

class TweenManager;
class Tween;

class Transform
{
public:
    // 設定
    // ローカル座標を設定
    void SetLocalPosition(const DirectX::SimpleMath::Vector3& localPosition) { m_localPosition = localPosition; }
    // ローカル座標を設定
    void SetLocalRotation(const DirectX::SimpleMath::Quaternion& localRotation) { m_localRotation = localRotation; }
    // ローカルスケールを設定
    void SetLocalScale(const DirectX::SimpleMath::Vector3& localScale) { m_localScale = localScale; }
	

    // 取得
    // ローカル座標を設定
    DirectX::SimpleMath::Vector3 GetLocalPosition() const { return m_localPosition; }
    // ローカル回転角を設定
    DirectX::SimpleMath::Quaternion GetLocalRotation() const { return m_localRotation; }
    // ローカルスケールを設定
    DirectX::SimpleMath::Vector3 GetLocalScale() const { return m_localScale; }


	// ワールド行列を取得する
	DirectX::SimpleMath::Matrix GetWorldMatrix() const { return m_worldMatrix; }

    // ワールド座標を取得
    DirectX::SimpleMath::Vector3 GetWorldPosition() const
    {
        // ワールド行列の第4列 (41, 42, 43) が平行移動成分
        return DirectX::SimpleMath::Vector3(m_worldMatrix._41, m_worldMatrix._42, m_worldMatrix._43);
    }

    // ワールド回転を取得
    DirectX::SimpleMath::Quaternion GetWorldRotation() const
    {
        using namespace DirectX::SimpleMath;

        // スケールを除去して回転行列を取り出す
        Vector3 scale = GetWorldScale();

        Matrix rotationMatrix = m_worldMatrix;
        rotationMatrix._11 /= scale.x;
        rotationMatrix._12 /= scale.x;
        rotationMatrix._13 /= scale.x;

        rotationMatrix._21 /= scale.y;
        rotationMatrix._22 /= scale.y;
        rotationMatrix._23 /= scale.y;

        rotationMatrix._31 /= scale.z;
        rotationMatrix._32 /= scale.z;
        rotationMatrix._33 /= scale.z;

        // 回転行列からクォータニオンを作成
        return Quaternion::CreateFromRotationMatrix(rotationMatrix);
    }

    // ワールドスケールを取得
    DirectX::SimpleMath::Vector3 GetWorldScale() const
    {
        using namespace DirectX::SimpleMath;

        // 各軸のスケールを計算
        float scaleX = Vector3(m_worldMatrix._11, m_worldMatrix._12, m_worldMatrix._13).Length();
        float scaleY = Vector3(m_worldMatrix._21, m_worldMatrix._22, m_worldMatrix._23).Length();
        float scaleZ = Vector3(m_worldMatrix._31, m_worldMatrix._32, m_worldMatrix._33).Length();

        return Vector3(scaleX, scaleY, scaleZ);
    }

    // 親を設定
    void SetParent(Transform* parent) { m_parent = parent; }
    // 子供を設定
    void SetChild(Transform* child) { m_childs.push_back(child); }

    // 親を取得する
    Transform* GetTransform() const { return m_parent; }
    // 子供を取得する
    std::vector<Transform*> GetChilds() const { return m_childs; }

public:
    // コンストラクタ
    Transform();
    // デストラクタ
    ~Transform() = default;

public:
    // 更新処理
    void Update();

    // Tweenを取得する
    Tween* GetTween();

   
private:
	// 親のTransform
	Transform* m_parent;
	// 子のTransform
	std::vector<Transform*> m_childs;

	// ローカル座標
	DirectX::SimpleMath::Vector3 m_localPosition;
	// ローカル回転角
	DirectX::SimpleMath::Quaternion m_localRotation;
	// ローカルスケール
	DirectX::SimpleMath::Vector3 m_localScale;

	// ワールド行列
	DirectX::SimpleMath::Matrix m_worldMatrix;

    // TweenManagerのインスタンス
    TweenManager* m_tweenManager;
};