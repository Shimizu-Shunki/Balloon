#pragma once
#include "Interface/IScene.h"


class CommonResources;
class IObject;
class Transform;
class DebugCamera;


class PlayScene : public IScene
{
public:
	// コンストラクタ
	PlayScene();
	// デストラクタ
	~PlayScene();

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

private:

	// 共有リソース
	CommonResources* m_commonResources;

	// オブジェクトのルート
	std::vector<std::unique_ptr<IObject>> m_rootObject;
	// Transformのルート
	std::unique_ptr<Transform> m_rootTransform;
	// デバッグカメラで実装
	std::unique_ptr<DebugCamera> m_debugCamera;
};