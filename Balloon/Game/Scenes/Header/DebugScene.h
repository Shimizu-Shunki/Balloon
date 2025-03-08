#pragma once
#include "Interface/IScene.h"
#include <Game/Material/SeaMaterial.h>


class CommonResources;
class PBRLit;
class SkyBox;
class Model3D;
class Player;

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

private:

	// 共有リソース
	CommonResources* m_commonResources;


	DirectX::CommonStates* m_commonStates;

	// デバッグカメラで実装
	std::unique_ptr<DebugCamera> m_debugCamera;



	// ブレンドステート
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;



	std::unique_ptr<Player> m_plaeyr;


};