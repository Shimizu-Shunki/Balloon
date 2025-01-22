//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"


extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    // グラフィックスのインスタンスを取得する
    m_graphics = Graphics::GetInstance();
   
    // デバイスリソースを取得する
    m_deviceResources = m_graphics->GetDeviceResources();
    // デバイスの通知先を設定する
    m_deviceResources->RegisterDeviceNotify(this);
}

Game::~Game()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

// Direct3Dリソースを初期化する
void Game::Initialize(HWND window, int width, int height)
{
    // ウィンドウハンドルを設定する
    m_hWnd = window;
    // デバイスリソースに「ウィンドウハンドル」「幅」「高さ」を設定する
    m_deviceResources->SetWindow(window, width, height);
    // デバイスリソースを生成する
    m_deviceResources->CreateDeviceResources();
    // デバイスに依存したリソースを生成する
    CreateDeviceDependentResources();
    // ウィンドウサイズに依存したリソースを生成する
    m_deviceResources->CreateWindowSizeDependentResources();
    // ウィンドウサイズに依存したリソースを生成する
    CreateWindowSizeDependentResources();

    // タイマー設定を変更する   
    m_timer.SetFixedTimeStep(true);
    // タイマーにターゲット経過秒(60FPS)を設定する
    m_timer.SetTargetElapsedSeconds(1.0 / 60);

    // グラフィックスの初期化
    m_graphics->Initialize(window);
    // 画面サイズ
    int screenWidth, screenHeight;
    // 画面サイズを取得する
    GetDefaultSize(screenWidth, screenHeight);
    // 画面サイズを設定する
    m_graphics->SetScreenSize(screenWidth, screenHeight);
    // 射影行列を生成する 
    DirectX::SimpleMath::Matrix projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
        DirectX::XMConvertToRadians(45.0f),
        screenWidth / (float)screenHeight,
        0.1f,
        10000.0f
    );
    // 射影行列を設定する
    m_graphics->SetProjectionMatrix(projection);

    //  バージョンの確認
    IMGUI_CHECKVERSION();
    //  コンテキストの作成
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // キーボードによるナビゲーションの有効化
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // コントローラーによるナビゲーションの有効化
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    // マルチビューポート有効化
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    // ドッキング有効化
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    //  Win32用の初期化
    ImGui_ImplWin32_Init(window);
    //  DirectX11用の初期化
    ID3D11Device* device = m_deviceResources->GetD3DDevice();
    ID3D11DeviceContext* context = m_deviceResources->GetD3DDeviceContext();
    ImGui_ImplDX11_Init(device, context);

    // io.Fonts->AddFontFromFileTTF("Resources\\font\\YOzREX_.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());



}

#pragma region Frame Update
// ゲームループを実行する
void Game::Tick()
{
    m_timer.Tick([&]()
        {
            Update(m_timer);
        });
    // 描画する
    Render();
}

// ワールドを更新する
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;
}
#pragma endregion

#pragma region Frame Render
// シーンを描画する
void Game::Render()
{
    // 描画可能でない場合は復帰する
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    // バックバッファをクリアする
    Clear();

    //  新フレームの開始（メインループの一番上に記述）
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigViewportsNoTaskBarIcon = false; // OSのタスクバーにアイコンを表示しない
    io.ConfigViewportsNoDecoration = false; // OSウィンドウの枠を消す


    // PIX開始イベント
    m_deviceResources->PIXBeginEvent(L"Render");


    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

    int screen_w, screen_h;
    m_graphics->GetScreenSize(screen_w, screen_h);

    wchar_t stringBuffer[128];




    //  ImGuiの描画処理
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        // TODO for OpenGL: restore current GL context.
    }


    m_graphics->GetSpriteBatch()->Begin();
    // FPS
    swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"FPS : %d", m_timer.GetFramesPerSecond());
    m_graphics->DrawString(10.0f, 20.0f, stringBuffer);

    // スクリーンサイズ
    swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"ScreenW : %d ScreenH : %d", screen_w, screen_h);
    m_graphics->DrawString(10.0f, 40.0f, stringBuffer);

    m_graphics->GetSpriteBatch()->End();

    // PIX終了イベント
    m_deviceResources->PIXEndEvent();
    // 新規フレームを描画する
    m_deviceResources->Present();
}

// バックバッファをクリアする
void Game::Clear()
{
    // ビューをクリアする
    auto context = m_deviceResources->GetD3DDeviceContext();
    // レンダーターゲットを取得する
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    // 深度ステンシルビューを取得する
    auto depthStencil = m_deviceResources->GetDepthStencilView();
    // レンダーターゲットビューをクリアする
    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    // 深度ステンシルビューをクリアする
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    // レンダーターゲットを設定する
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // スクリーンビューポートを取得する
    auto const viewport = m_deviceResources->GetScreenViewport();
    // ビューポートを設定する
    context->RSSetViewports(1, &viewport);
    // PIX終了イベント
    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// メッセージハンドラ
void Game::OnActivated()
{
    // ゲームがアクティブウィンドウになったときの処理を記述する
}

void Game::OnDeactivated()
{
    // ゲームが背景ウィンドウになった時の処理を記述する
}

void Game::OnSuspending()
{
    // ゲームの実行中に電源が停止した時の処理を記述する
}

void Game::OnResuming()
{
    // 経過時間をリセットする
    m_timer.ResetElapsedTime();

    // ゲームの実行中に電源が復帰した時の処理を記述する
}

// ウィンドウが移動したときの処理を記述する
void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

// ウィンドウサイズが変更された時の処理を記述する
void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;
    // ウィンドウサイズに依存したリソースを生成する
    CreateWindowSizeDependentResources();

    // ゲームウィンドウのサイズが変更された時の処理を記述する
    m_graphics->SetScreenSize(width, height);
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // 規定のウィンドウサイズ
    width = 1280;
    height = 720;
}
#pragma endregion

#pragma region Direct3D Resources
// デバイスに依存したリソースを生成する
void Game::CreateDeviceDependentResources()
{
    // デバイスに依存したオブジェクトを初期化する
    int width, height;
    // ウィンドウの既定サイズを取得する
    GetDefaultSize(width, height);
    // 「ウィンドウハンドル」「幅」「高さ」を設定する
    m_graphics->GetDeviceResources()->SetWindow(m_hWnd, width, height);
    // グラフィックスを初期化する
    m_graphics->Initialize(m_hWnd);
}

// ウィンドウサイズが変更されたイベントによりメモリリソースを確保する
void Game::CreateWindowSizeDependentResources()
{
    // ウィンドウサイズに依存したオブジェクトを初期化するコードを記述する
     // 出力サイズを取得する
    auto m_size = m_deviceResources->GetOutputSize();
    // アスペクト率を計算する
    float aspectRatio = float(m_size.right) / float(m_size.bottom);
    // 視野角を設定する
    float fovAngleY = 45.0f * DirectX::XM_PI / 180.0f;
    // アプリが縦向きまたはスナップビューのときに変更する
    if (aspectRatio < 1.0f) { fovAngleY *= 2.0f; }
    // 射影行列を生成する
    DirectX::SimpleMath::Matrix projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
        fovAngleY,
        aspectRatio,
        0.1f,
        1000.0f
    );
    // 射影行列を設定する
    m_graphics->SetProjectionMatrix(projection);
}

// デバイスロストが発生した時の処理を記述する
void Game::OnDeviceLost()
{
    // Direct3Dリソースをクリーンアップする処理を記述する
}

// デバイスが復帰した時の処理を記述する
void Game::OnDeviceRestored()
{
    // デバイスに依存したリソースを生成する
    CreateDeviceDependentResources();
    // ウィンドウサイズに依存したリソースを生成する
    CreateWindowSizeDependentResources();
}
// フルスクリーン対応
void Game::SetFullscreenState(BOOL value)
{
    m_full_screen = value;
    m_deviceResources->GetSwapChain()->SetFullscreenState(m_full_screen, nullptr);
    if (value) m_deviceResources->CreateWindowSizeDependentResources();
}

#pragma endregion
