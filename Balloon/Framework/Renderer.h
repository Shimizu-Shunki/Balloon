#pragma once
#include "Interface/IObject.h"
#include "Interface/IRenderableObject.h"

class CommonResources;

class Renderer
{

public:
	// コンストラクタ
	Renderer();
	// デストラクタ
	~Renderer() = default;

	// 描画オブジェクト追加
	void Attach(IObject* object, IRenderableObject* renderableObject);
	// 描画処理
	void Render();
private:
	// 共有リソース
	CommonResources* m_commonResources;
	// コンテキスト
	ID3D11DeviceContext1* m_context;
	// コモンステート
	DirectX::CommonStates* m_commonStates;

	// 描画オブジェクト
	std::unordered_map<IObject*, IRenderableObject*> m_renderableObjects;
};