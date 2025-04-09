// ============================================
// 
// ファイル名: IMaterial.h
// 概要: マテリアルの描画制御を定義する（インターフェース）
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Framework/pch.h"

class IMaterial
{
public:
	// 仮想デストラクタ
	virtual ~IMaterial() = default;
	// マテリアルの描画開始処理
	virtual void BeginMaterial() = 0;
	// マテリアルの描画終了処理
	virtual void EndMaterial() = 0;
	// 定数バッファを更新
	virtual void UpdateConstBuffer() = 0;
	
};