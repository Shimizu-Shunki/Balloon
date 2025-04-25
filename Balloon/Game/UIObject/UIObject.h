#pragma once
#include "Interface/IObject.h"
#include "Interface/IState.h"

class UIObject : public IObject
{
public:
	// オブジェクトをカウントアップする
	static int CountUpNumber();
	// 現在のオブジェクトカウントを取得
	static int ResetNumber();

public:

	// コンストラクタ
	UIObject();
	// デストラクタ
	~UIObject();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const float& elapsedTime);
	// 後処理を行う
	void Finalize();

private:
	// オブジェクト番号
	static int s_objectNumber;
	// 現在のメッセージ
	Message m_currentMessage;
};