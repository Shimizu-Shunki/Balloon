//
// Game.h
//

#pragma once

#include "Framework/DeviceResources.h"
#include "Framework/StepTimer.h"
#include "Framework/Resources.h"
#include "Framework/CommonResources.h"
#include "Framework/CameraManager.h"
#include "Framework/RenderManager.h"
#include "Framework/AudioManager.h"
#include "Framework/Tween/TweenManager.h"

class SceneManager;
class InputManager;
class SeaMaterial;
class CollisionManager;
class ObjectMessenger;
class CollisionMessenger;
class SceneMessenger;


// D3D11デバイスを生成しゲームループを提供するゲームクラス
class Game final : public DX::IDeviceNotify
{
public:
    // コンストラクタ
    Game() noexcept(false);
    // デストラクタ
    ~Game();
    Game(Game&&) = default;
    Game& operator= (Game&&) = default;
    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // 初期化処理
    void Initialize(HWND window, int width, int height);

    // ゲームループ
    void Tick();

    // IDeviceNotifyインターフェース
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // メッセージハンドラー
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // 規定ウィンドウサイズプロパティを取得する
    void GetDefaultSize(int& width, int& height) const noexcept;
    // 画面モードを変更する関数（TRUE:フルスクリーン）
    void SetFullscreenState(BOOL value);
private:
    // 更新処理
    void Update(DX::StepTimer const& timer);
    // 描画処理
    void Render();

    void Clear();
    // デバイス依存したリソースを生成する
    void CreateDeviceDependentResources();
    // ウィンドウサイズに依存したリソースを生成する
    void CreateWindowSizeDependentResources();


private:
    // ウィンドウハンドル
    HWND            m_hWnd;
    // タイマー
    DX::StepTimer   m_timer;

    // デバイス
    ID3D11Device1* m_device;
    // コンテキスト
    ID3D11DeviceContext1* m_context;


    // デバイスリソース
    std::unique_ptr<DX::DeviceResources> m_deviceResources;
    // フルスクリーン
    BOOL m_full_screen;
   
    // 共有リソース
    CommonResources* m_commonResources;
    // リソース
    Resources* m_resources;
    //  コモンステート
    std::unique_ptr<DirectX::CommonStates>  m_commonStates;

    // 管理クラス
    // シーンマネージャー
    SceneManager* m_sceneManager;
    // 入力マネージャー
    InputManager* m_inputManager;
    // カメラマネージャー
    CameraManager* m_cameraManager;
    // 描画マネージャー
    RenderManager* m_renderManager;
    // オーディオマネージャー
    AudioManager* m_audioManager;
    // Tweenマネージャー
    TweenManager* m_tweenManager;
    // 当たり判定マネージャー
    CollisionManager* m_collisionManager;

    // メッセンジャー
    ObjectMessenger* m_objectMessenger;
    CollisionMessenger* m_collisionMessenger;
    SceneMessenger* m_sceneMessenger;

    // 海
    std::unique_ptr<SeaMaterial> m_seaMaterial;


    // デバッグの時のみ作成
#ifdef _DEBUG
    // ベーシックエフェクト
    std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
    // プリミティブバッチ
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
    // 入力レイアウト
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

    //	スプライトバッチ
    std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
    //	スプライトフォント
    std::unique_ptr<DirectX::SpriteFont>  m_spriteFont;
#endif
};