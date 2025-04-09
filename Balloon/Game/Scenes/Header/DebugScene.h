// ============================================
// 
// ファイル名: DebugScene.h
// 概要: DebugScene.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IScene.h"
#include <Game/Material/SeaMaterial.h>


class CommonResources;
class ObjectMessenger;
class PBRLit;
class SkyBox;
class Model3D;
class Player;
class Cloud;
class DebugCamera;


class DebugScene : public IScene
{
public:
	// コンストラクタ
	DebugScene();
	// デストラクタ
	~DebugScene();

public:
	// 初期化処理
	void Initialize() override;
	// スタート処理
	void Start()  override;
	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;
	// 終了処理
	void Finalize() override;
	// シーンのステートを変更する
	void ChangeState(IState* newState) override;
	// 当たり判定メッセージを受け取る
	void OnSceneMessegeAccepted(Message::SceneMessageID messageID) override;

private:

	// 共有リソース
	CommonResources* m_commonResources;
	ObjectMessenger* m_objectMessenger;

	DirectX::CommonStates* m_commonStates;

	// デバッグカメラで実装
	std::unique_ptr<DebugCamera> m_debugCamera;

	std::unique_ptr<Player> m_plaeyr;

	std::unique_ptr<Cloud> m_cloud;

	
};