#pragma once
#include "Interface/IScene.h"
#include <Game/Material/SeaMaterial.h>


class CommonResources;
class PBRLit;
class SkyBox;

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

	DirectX::Model* m_sphereModel;
	DirectX::CommonStates* m_commonStates;

	// デバッグカメラで実装
	std::unique_ptr<DebugCamera> m_debugCamera;

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	// メインテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_mainTexture;
	// ノーマルマップ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_normalMap;
	// キューブマップ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_skyMap;

	// ブレンドステート
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;

	// マテリアル
	std::unique_ptr<PBRLit> m_PBRLit;

	// 定数バッファ用のバッファオブジェクト
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	std::unique_ptr<SkyBox> m_skyBox;
};