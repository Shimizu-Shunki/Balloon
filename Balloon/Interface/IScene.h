// ============================================
// 
// ファイル名: IScene.h
// 概要: シーンのライフサイクル管理と状態遷移・メッセージ処理を定義する（インターフェース）
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once


class IScene
{
public:
	// デストラクタ
	virtual ~IScene() = default;

public:
	// 初期化処理
	virtual void Initialize() = 0;
	// スタート処理
	virtual void Start() = 0;
	// 更新処理
	virtual void Update() = 0;
	// 描画処理
	virtual void Render() = 0;
	// 終了処理
	virtual void Finalize() = 0;
};