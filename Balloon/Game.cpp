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
    // �O���t�B�b�N�X�̃C���X�^���X���擾����
    m_graphics = Graphics::GetInstance();
   
    // �f�o�C�X���\�[�X���擾����
    m_deviceResources = m_graphics->GetDeviceResources();
    // �f�o�C�X�̒ʒm���ݒ肷��
    m_deviceResources->RegisterDeviceNotify(this);
}

Game::~Game()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

// Direct3D���\�[�X������������
void Game::Initialize(HWND window, int width, int height)
{
    // �E�B���h�E�n���h����ݒ肷��
    m_hWnd = window;
    // �f�o�C�X���\�[�X�Ɂu�E�B���h�E�n���h���v�u���v�u�����v��ݒ肷��
    m_deviceResources->SetWindow(window, width, height);
    // �f�o�C�X���\�[�X�𐶐�����
    m_deviceResources->CreateDeviceResources();
    // �f�o�C�X�Ɉˑ��������\�[�X�𐶐�����
    CreateDeviceDependentResources();
    // �E�B���h�E�T�C�Y�Ɉˑ��������\�[�X�𐶐�����
    m_deviceResources->CreateWindowSizeDependentResources();
    // �E�B���h�E�T�C�Y�Ɉˑ��������\�[�X�𐶐�����
    CreateWindowSizeDependentResources();

    // �^�C�}�[�ݒ��ύX����   
    m_timer.SetFixedTimeStep(true);
    // �^�C�}�[�Ƀ^�[�Q�b�g�o�ߕb(60FPS)��ݒ肷��
    m_timer.SetTargetElapsedSeconds(1.0 / 60);

    // �O���t�B�b�N�X�̏�����
    m_graphics->Initialize(window);
    // ��ʃT�C�Y
    int screenWidth, screenHeight;
    // ��ʃT�C�Y���擾����
    GetDefaultSize(screenWidth, screenHeight);
    // ��ʃT�C�Y��ݒ肷��
    m_graphics->SetScreenSize(screenWidth, screenHeight);
    // �ˉe�s��𐶐����� 
    DirectX::SimpleMath::Matrix projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
        DirectX::XMConvertToRadians(45.0f),
        screenWidth / (float)screenHeight,
        0.1f,
        10000.0f
    );
    // �ˉe�s���ݒ肷��
    m_graphics->SetProjectionMatrix(projection);

    //  �o�[�W�����̊m�F
    IMGUI_CHECKVERSION();
    //  �R���e�L�X�g�̍쐬
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // �L�[�{�[�h�ɂ��i�r�Q�[�V�����̗L����
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // �R���g���[���[�ɂ��i�r�Q�[�V�����̗L����
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    // �}���`�r���[�|�[�g�L����
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    // �h�b�L���O�L����
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    //  Win32�p�̏�����
    ImGui_ImplWin32_Init(window);
    //  DirectX11�p�̏�����
    ID3D11Device* device = m_deviceResources->GetD3DDevice();
    ID3D11DeviceContext* context = m_deviceResources->GetD3DDeviceContext();
    ImGui_ImplDX11_Init(device, context);

    // io.Fonts->AddFontFromFileTTF("Resources\\font\\YOzREX_.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());



}

#pragma region Frame Update
// �Q�[�����[�v�����s����
void Game::Tick()
{
    m_timer.Tick([&]()
        {
            Update(m_timer);
        });
    // �`�悷��
    Render();
}

// ���[���h���X�V����
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;
}
#pragma endregion

#pragma region Frame Render
// �V�[����`�悷��
void Game::Render()
{
    // �`��\�łȂ��ꍇ�͕��A����
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    // �o�b�N�o�b�t�@���N���A����
    Clear();

    //  �V�t���[���̊J�n�i���C�����[�v�̈�ԏ�ɋL�q�j
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigViewportsNoTaskBarIcon = false; // OS�̃^�X�N�o�[�ɃA�C�R����\�����Ȃ�
    io.ConfigViewportsNoDecoration = false; // OS�E�B���h�E�̘g������


    // PIX�J�n�C�x���g
    m_deviceResources->PIXBeginEvent(L"Render");


    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

    int screen_w, screen_h;
    m_graphics->GetScreenSize(screen_w, screen_h);

    wchar_t stringBuffer[128];




    //  ImGui�̕`�揈��
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

    // �X�N���[���T�C�Y
    swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"ScreenW : %d ScreenH : %d", screen_w, screen_h);
    m_graphics->DrawString(10.0f, 40.0f, stringBuffer);

    m_graphics->GetSpriteBatch()->End();

    // PIX�I���C�x���g
    m_deviceResources->PIXEndEvent();
    // �V�K�t���[����`�悷��
    m_deviceResources->Present();
}

// �o�b�N�o�b�t�@���N���A����
void Game::Clear()
{
    // �r���[���N���A����
    auto context = m_deviceResources->GetD3DDeviceContext();
    // �����_�[�^�[�Q�b�g���擾����
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    // �[�x�X�e���V���r���[���擾����
    auto depthStencil = m_deviceResources->GetDepthStencilView();
    // �����_�[�^�[�Q�b�g�r���[���N���A����
    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    // �[�x�X�e���V���r���[���N���A����
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    // �����_�[�^�[�Q�b�g��ݒ肷��
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // �X�N���[���r���[�|�[�g���擾����
    auto const viewport = m_deviceResources->GetScreenViewport();
    // �r���[�|�[�g��ݒ肷��
    context->RSSetViewports(1, &viewport);
    // PIX�I���C�x���g
    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// ���b�Z�[�W�n���h��
void Game::OnActivated()
{
    // �Q�[�����A�N�e�B�u�E�B���h�E�ɂȂ����Ƃ��̏������L�q����
}

void Game::OnDeactivated()
{
    // �Q�[�����w�i�E�B���h�E�ɂȂ������̏������L�q����
}

void Game::OnSuspending()
{
    // �Q�[���̎��s���ɓd������~�������̏������L�q����
}

void Game::OnResuming()
{
    // �o�ߎ��Ԃ����Z�b�g����
    m_timer.ResetElapsedTime();

    // �Q�[���̎��s���ɓd�������A�������̏������L�q����
}

// �E�B���h�E���ړ������Ƃ��̏������L�q����
void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

// �E�B���h�E�T�C�Y���ύX���ꂽ���̏������L�q����
void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;
    // �E�B���h�E�T�C�Y�Ɉˑ��������\�[�X�𐶐�����
    CreateWindowSizeDependentResources();

    // �Q�[���E�B���h�E�̃T�C�Y���ύX���ꂽ���̏������L�q����
    m_graphics->SetScreenSize(width, height);
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // �K��̃E�B���h�E�T�C�Y
    width = 1280;
    height = 720;
}
#pragma endregion

#pragma region Direct3D Resources
// �f�o�C�X�Ɉˑ��������\�[�X�𐶐�����
void Game::CreateDeviceDependentResources()
{
    // �f�o�C�X�Ɉˑ������I�u�W�F�N�g������������
    int width, height;
    // �E�B���h�E�̊���T�C�Y���擾����
    GetDefaultSize(width, height);
    // �u�E�B���h�E�n���h���v�u���v�u�����v��ݒ肷��
    m_graphics->GetDeviceResources()->SetWindow(m_hWnd, width, height);
    // �O���t�B�b�N�X������������
    m_graphics->Initialize(m_hWnd);
}

// �E�B���h�E�T�C�Y���ύX���ꂽ�C�x���g�ɂ�胁�������\�[�X���m�ۂ���
void Game::CreateWindowSizeDependentResources()
{
    // �E�B���h�E�T�C�Y�Ɉˑ������I�u�W�F�N�g������������R�[�h���L�q����
     // �o�̓T�C�Y���擾����
    auto m_size = m_deviceResources->GetOutputSize();
    // �A�X�y�N�g�����v�Z����
    float aspectRatio = float(m_size.right) / float(m_size.bottom);
    // ����p��ݒ肷��
    float fovAngleY = 45.0f * DirectX::XM_PI / 180.0f;
    // �A�v�����c�����܂��̓X�i�b�v�r���[�̂Ƃ��ɕύX����
    if (aspectRatio < 1.0f) { fovAngleY *= 2.0f; }
    // �ˉe�s��𐶐�����
    DirectX::SimpleMath::Matrix projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
        fovAngleY,
        aspectRatio,
        0.1f,
        1000.0f
    );
    // �ˉe�s���ݒ肷��
    m_graphics->SetProjectionMatrix(projection);
}

// �f�o�C�X���X�g�������������̏������L�q����
void Game::OnDeviceLost()
{
    // Direct3D���\�[�X���N���[���A�b�v���鏈�����L�q����
}

// �f�o�C�X�����A�������̏������L�q����
void Game::OnDeviceRestored()
{
    // �f�o�C�X�Ɉˑ��������\�[�X�𐶐�����
    CreateDeviceDependentResources();
    // �E�B���h�E�T�C�Y�Ɉˑ��������\�[�X�𐶐�����
    CreateWindowSizeDependentResources();
}
// �t���X�N���[���Ή�
void Game::SetFullscreenState(BOOL value)
{
    m_full_screen = value;
    m_deviceResources->GetSwapChain()->SetFullscreenState(m_full_screen, nullptr);
    if (value) m_deviceResources->CreateWindowSizeDependentResources();
}

#pragma endregion
