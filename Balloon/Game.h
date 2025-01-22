//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"

#include "Framework/Graphics.h"


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

    // デバイスリソース
    DX::DeviceResources* m_deviceResources;
    // フルスクリーン
    BOOL m_full_screen;

    // グラフィックス
    Graphics* m_graphics;
};