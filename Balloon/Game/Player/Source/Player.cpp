#include "pch.h"
#include "Game/Player/Player.h"
#include "Game/Player/Character.h"
#include "Framework/CollisionManager.h"
#include "Game/Balloon/Balloon.h"
#include "Framework/InputManager.h"
#include "Game/Player/Enemy.h"
#include "Game/Collider/Collider.h"
#include "Game/Player/Hand.h"
#include "Game/Player/Jump.h"


Player::Player(ICamera* camera,IComponent* parent, const int balloonIndex, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_balloonIndex(balloonIndex),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle))
{
	
	m_inputManager = InputManager::GetInstance();
	m_camera = camera;
}

Player::~Player()
{

}


void Player::Initialize(ObjectID objectID, const bool& active)
{
	// オブジェクトIDを設定
	m_objectId = objectID;
	// オブジェクトアクティブを設定
	m_isActive = active;

	m_isKinematic = false;

	// オブジェクトIDを設定
	m_objectId = ObjectID::PLAYER;

	// 現在の座標を初期化
	m_currentPosition = m_initialPosition;
	// 現在の回転を初期化
	m_rotationTurretAngle = m_initialAngle;
	// 大きさを初期化
	m_scale = DirectX::SimpleMath::Vector3::One;

	// ジャンプ処理作成
	m_jump = std::make_unique<Jump>();
	m_jump->Initialize();

	
	// キャラクターをアタッチする
	this->Attach(std::make_unique<Character>());
	// 風船の初期座標
	DirectX::SimpleMath::Vector3 initPosition = { 0.0f,1.0f,0.0f };
	// 風船の数に応じて生成する
	for (int i = 0; i < m_balloonIndex; i++)
	{
		// 風船をアタッチする
		this->Attach(std::make_unique<Balloon>(this,initPosition,DirectX::XMConvertToRadians(20.0f * static_cast<float>(i) - 20.0f) ));
	}

	// 手をアタッチ
	this->Attach(std::make_unique<Hand>());

	// 当たり判定生成
	std::unique_ptr<Collider> collider = std::make_unique<Collider>();
	collider->Initialize<DirectX::BoundingBox>(DirectX::SimpleMath::Vector3::Up * 0.5f, DirectX::SimpleMath::Vector3::One / 2.0f);

	// 格納
	m_colliders.push_back(std::move(collider));

	collider = std::make_unique<Collider>();
	collider->Initialize<DirectX::BoundingSphere>(DirectX::SimpleMath::Vector3::Up * 2.0f, DirectX::SimpleMath::Vector3::One / 2.0f , true);

	// 格納
	m_colliders.push_back(std::move(collider));
}

void Player::Update(const float elapsedTime, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	// 入力に基づく方向ベクトルを取得
	DirectX::SimpleMath::Vector3 movementDirection = this->GetMovementDirection(m_camera->GetRotation());

	if (movementDirection.LengthSquared() > 0.0f)
	{
		// 入力がある場合：加速を適用
		m_velocity += movementDirection * 20.0f * elapsedTime;

		// 摩擦を弱める
		m_velocity.x *= 0.95f; // 入力があるときの摩擦
		m_velocity.z *= 0.95f; // 入力があるときの摩擦
	}
	else
	{
		// 入力がない場合：摩擦を強める
		m_velocity.x *= 0.85f; // 入力がないときの摩擦
		m_velocity.z *= 0.85f; // 入力がないときの摩擦
	}

	// 重力が有効でキネマティック出ない時
	if (m_isGravity && !m_isKinematic)
	{
		// 重力数値
		m_gravity = ( - 9.81f + 2.0f * m_balloonIndex) * elapsedTime;
		// 重力を速度に加算
		m_velocity.y = m_velocity.y + m_gravity;
	}

	// ジャンプ処理
	if (m_inputManager->GetKeyboardTracker()->IsKeyPressed(DirectX::Keyboard::Space))
	{
		m_velocity.y += m_jump->TryJump(elapsedTime);
	}

	m_jump->Update(elapsedTime);
	// 座標に速度を加算する
	m_currentPosition += m_velocity * elapsedTime;

	// 当たり判定の更新
	for (auto& collider : m_colliders)
	{
		collider->Update(m_currentPosition);
	}


	// 風船を更新する
	for (auto& child : m_child)
	{
		// 風船を更新する
		child->Update(elapsedTime, m_currentPosition, m_rotationTurretAngle);
	}
}

// 描画処理
void Player::Render()
{

	// this->DebugImguiRender();
	m_jump->Render();
	m_jump->DebugRender();
	// 当たり判定デバッグ描画
	// 当たり判定の更新
	for (auto& collider : m_colliders)
	{
		//collider->DebugRender();
	}

	// 子オブジェクトを描画する
	for (auto& childes : m_child)
	{
		// 子オブジェクトを描画する
		childes->Render();
	}
}

void Player::Attach(std::unique_ptr<IComponent> turretParts)
{
	// 砲塔部品を追加する
	turretParts->Initialize(IComponent::ObjectID::BALLOON, true);
	//m_collisionManager->Attach(turretParts.get());
	m_child.emplace_back(std::move(turretParts));
}

void Player::OnCollisionEnter(IComponent* component)
{
	m_gravity = 0.0f;
	m_velocity.y = 0.0f;
	m_isGravity = false;
}



void Player::OnCollisionStay(IComponent* component)
{

}

void Player::OnCollisionExit(IComponent* component)
{
	m_isGravity = true;
}

void Player::OnTriggerEnter(IComponent* component)
{
	// プレイヤーが当たった時
 	if (component->GetObjectID() == ObjectID::ENEMY)
	{
		this->BalloonDetach();
	}

	
}

//void Player::OnTriggerStay(IComponent* component)
//{
//
//}
//
//void Player::OnTriggerExit(IComponent* component)
//{
//
//}



void Player::RecoverJump()
{
	// ジャンプが行われたとき
	if (m_jumpIndex != 10)
	{
		// ジャンプ回数の回復

	}
}




void Player::Detach(std::unique_ptr<IComponent> turretParts)
{

}

void Player::Finalize()
{

}

void Player::BalloonDetach()
{
	// バルーンを非表示にする
	// bool true false 無敵状態を作る
	// すべての風船がない場合　ある程度の速度で踏むと死ぬ　落ちる
	if (m_balloonIndex != 0)
	{
		m_child[m_balloonIndex - 1]->SetIsActive(false);
		m_balloonIndex--;
	}
}

// 移動方向を取得する
DirectX::SimpleMath::Vector3 Player::GetMovementDirection(const DirectX::SimpleMath::Quaternion& angle)
{
	// 方向
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	// 上キー
	if (m_inputManager->GetKeyboardState().W)
	{
		direction += DirectX::SimpleMath::Vector3::Forward;
	}
	// 下キー
	if (m_inputManager->GetKeyboardState().S)
	{
		direction += DirectX::SimpleMath::Vector3::Backward;
	}
	// 右キー
	if (m_inputManager->GetKeyboardState().D)
	{
		direction += DirectX::SimpleMath::Vector3::Right;
	}
	// 左キー
	if (m_inputManager->GetKeyboardState().A)
	{
		direction += DirectX::SimpleMath::Vector3::Left;
	}

	// プレイヤーの回転角（クォータニオン）に基づいて方向を回転させる
	direction = DirectX::SimpleMath::Vector3::Transform(direction, angle);

	// Y成分をゼロにして水平面に制限
	direction.y = 0.0f;

	// 正規化して移動方向を返す
	direction.Normalize();

	return direction;
}

void Player::DebugImguiRender()
{
	// 親の情報を表示
	ImGui::Begin("Hierarchy");

	if (ImGui::TreeNode("Player")) {
		RenderComponent(this);  // プレイヤー自身の情報を表示

		// 子要素を再帰的に描画
		for (const auto& child : m_child) {
			if (ImGui::TreeNode(child.get(), "Child")) {
				RenderComponent(child.get());
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}

	ImGui::End();
	
}

void Player::RenderComponent(IComponent* component)
{
	// 親の情報を描画
	float position[3] = { component->GetPosition().x, component->GetPosition().y, component->GetPosition().z };
	float scale[3] = { component->GetScale().x, component->GetScale().y, component->GetScale().z };

	ImGui::Text("Position");
	ImGui::InputFloat3("##Position", position);
	ImGui::Text("Scale");
	ImGui::InputFloat3("##Scale", scale);

	// 値を反映
	component->SetPosition({ position[0], position[1], position[2] });
	component->SetScale({ scale[0], scale[1], scale[2] });
}