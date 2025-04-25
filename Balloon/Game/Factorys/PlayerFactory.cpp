#include "pch.h"
#include "Interface/IObject.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Message/Message.h"
#include "Game/Message/KeyboardMessenger.h"

// プレイヤーパーツ
#include "Game/Player/Player.h"
#include "Game/Player/Body.h"
#include "Game/Player/Head.h"
#include "Game/Player/LeftArm.h"
#include "Game/Player/LeftFoot.h"
#include "Game/Player/RightArm.h"
#include "Game/Player/RightFoot.h"


// プレイヤーの作成
std::unique_ptr<IObject> PlayerFactory::CreatePlayer(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		PlayerFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> player;
	// Turretクラスのインスタンスを生成する
	player.reset(new Player(parent , IObject::ObjectID::PLAYER , initialPosition, rotation , initialScale , Message::MessageID::PLAYER_IDLING));
	// 初期化する
	player->Initialize();

	// キーボードメッセンジャーに登録
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY, DirectX::Keyboard::Keys::Left, player.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY, DirectX::Keyboard::Keys::Right, player.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_DOWN, DirectX::Keyboard::Keys::Up, player.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_UP, DirectX::Keyboard::Keys::Up, player.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_UP, DirectX::Keyboard::Keys::Down, player.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_DOWN, DirectX::Keyboard::Keys::Down, player.get());

	// プレイヤークラスのインスタンスを返す
	return std::move(player);
}

// プレイヤーの体を作成
std::unique_ptr<IObject> PlayerFactory::CreatePlayerBody(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		PlayerFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> playerBody;
	// Turretクラスのインスタンスを生成する
	playerBody.reset(new Body(parent, IObject::ObjectID::PLAYER_BODY, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// 初期化する
	playerBody->Initialize();
	// プレイヤークラスのインスタンスを返す
	return std::move(playerBody);
}


// プレイヤーの頭を作成
std::unique_ptr<IObject> PlayerFactory::CreatePlayerHead(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		PlayerFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> playerHead;
	// Turretクラスのインスタンスを生成する
	playerHead.reset(new Head(parent, IObject::ObjectID::PLAYER_HEAD, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// 初期化する
	playerHead->Initialize();
	// プレイヤークラスのインスタンスを返す
	return std::move(playerHead);
}


// プレイヤーの左腕を作成
std::unique_ptr<IObject> PlayerFactory::CreatePlayerLeftArm(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		PlayerFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> playerleftArm;
	// Turretクラスのインスタンスを生成する
	playerleftArm.reset(new LeftArm(parent, IObject::ObjectID::PLAYER_LEFT_ARM, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// 初期化する
	playerleftArm->Initialize();
	// プレイヤークラスのインスタンスを返す
	return std::move(playerleftArm);
}

// プレイヤーの左足を作成
std::unique_ptr<IObject> PlayerFactory::CreatePlayerLeftFoot(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		PlayerFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> playerLeftFoot;
	// Turretクラスのインスタンスを生成する
	playerLeftFoot.reset(new LeftFoot(parent, IObject::ObjectID::PLAYER_LEFT_FOOT, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// 初期化する
	playerLeftFoot->Initialize();
	// プレイヤークラスのインスタンスを返す
	return std::move(playerLeftFoot);
}


// プレイヤーの右腕を作成
std::unique_ptr<IObject> PlayerFactory::CreatePlayerRightArm(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		PlayerFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> playerRightArm;
	// Turretクラスのインスタンスを生成する
	playerRightArm.reset(new RightArm(parent, IObject::ObjectID::PLAYER_RIGHT_ARM, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// 初期化する
	playerRightArm->Initialize();
	// プレイヤークラスのインスタンスを返す
	return std::move(playerRightArm);
}

// プレイヤーの右足を作成
std::unique_ptr<IObject> PlayerFactory::CreatePlayerRightFoot(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		PlayerFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> playerRightFoot;
	// Turretクラスのインスタンスを生成する
	playerRightFoot.reset(new RightFoot(parent, IObject::ObjectID::PLAYER_RIGHT_FOOT, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// 初期化する
	playerRightFoot->Initialize();
	// プレイヤークラスのインスタンスを返す
	return std::move(playerRightFoot);
}



/// <summary>
/// 回転ベクトルをクォータニオンに変換する。
/// </summary>
/// <param name="rotation">回転を表すベクトル（度数法）</param>
/// <returns>変換後のクォータニオン</returns>
DirectX::SimpleMath::Quaternion PlayerFactory::ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation) {
	return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(rotation.y),
		DirectX::XMConvertToRadians(rotation.x),
		DirectX::XMConvertToRadians(rotation.z)
	);
}