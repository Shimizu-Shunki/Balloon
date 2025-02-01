#pragma once
#include "Interface/IScene.h"


class CommonResources;

class ResultScene : public IScene
{
public:
	// コンストラクタ
	ResultScene();
	// デストラクタ
	~ResultScene();

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



};