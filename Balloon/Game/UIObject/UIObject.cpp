#include "pch.h"
#include "Game/UIObject/UIObject.h"

// オブジェクト番号
int UIObject::s_objectNumber = -1;

// オブジェクトをカウントアップする
int UIObject::CountUpNumber() { return s_objectNumber++; }

// 現在のオブジェクトのカウントを取得する
int UIObject::ResetNumber() { return s_objectNumber = -1; }


// コンストラクタ
UIObject::UIObject()
{
}

// デストラクタ
UIObject::~UIObject()
{
}

// 初期化する
void UIObject::Initialize()
{
}

// 更新する
void UIObject::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
}


// 後処理を行う
void UIObject::Finalize()
{
}