// ============================================
// 
// ファイル名: DefaultUi.h
// 概要: DefaultUi.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Buffers.h"
#include "Interface/IMaterial.h"

class IMaterial;

class DefaultUi : public IMaterial
{
public:
	// ピクセルシェーダーを設定
	void SetPixelShader(ID3D11PixelShader* pixelShader) { m_pixelShader = pixelShader; }

	// 定数バッファのセッターとゲッター
	// まとめて更新（全ての値を一度にセット）
	void SetUIConstBuffer(
		const DirectX::SimpleMath::Vector2& winSize,
		const DirectX::SimpleMath::Vector2& texSize,
		float useTex, float useRuleTex, float ruleProg, float ruleInv);

	// 個別の値を変更
	void SetWindowSize(const DirectX::SimpleMath::Vector2& size) { m_constBuffer.windowSize = size; }
	void SetTextureSize(const DirectX::SimpleMath::Vector2& size) { m_constBuffer.textureSize = size; }
	void SetUseTexture(bool flag) { m_constBuffer.useTexture = flag; }
	void SetUseRuleTexture(bool flag) { m_constBuffer.useRuleTexture = flag; }
	void SetRuleProgress(float progress) { m_constBuffer.ruleProgress = progress; }
	void SetRuleInverse(float inverse) { m_constBuffer.ruleInverse = inverse; }

private:
	// スクリーンサイズ
	const float SCREEN_WIDTH = 1280.0f;
	const float SCREEN_HEIGHT = 720.0f;

public:
	// コンストラクタ
	DefaultUi();
	// デストラクタ
	~DefaultUi();
	
	// マテリアルを適応する
	void BeginMaterial() override;
	// マテリアルの解放
	void EndMaterial() override;
	// 定数バッファを更新する
	void UpdateConstBuffer() override;


private:
	// UIの定数バッファオブジェクトを作成
	void UiCreateBuffer();

private:
	// デバイス
	ID3D11Device1* m_device;
	// コンテキスト
	ID3D11DeviceContext1* m_context;

	// 定数バッファ
	UIConstBuffer m_constBuffer;
	// 定数バッファオブジェクト
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constBufferObject;

	// ピクセルシェーダー
	ID3D11PixelShader*    m_pixelShader;
};