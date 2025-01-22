//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"

#include "Framework/Graphics.h"


// D3D11�f�o�C�X�𐶐����Q�[�����[�v��񋟂���Q�[���N���X
class Game final : public DX::IDeviceNotify
{
public:
    // �R���X�g���N�^
    Game() noexcept(false);
    // �f�X�g���N�^
    ~Game();
    Game(Game&&) = default;
    Game& operator= (Game&&) = default;
    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // ����������
    void Initialize(HWND window, int width, int height);

    // �Q�[�����[�v
    void Tick();

    // IDeviceNotify�C���^�[�t�F�[�X
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // ���b�Z�[�W�n���h���[
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // �K��E�B���h�E�T�C�Y�v���p�e�B���擾����
    void GetDefaultSize(int& width, int& height) const noexcept;
    // ��ʃ��[�h��ύX����֐��iTRUE:�t���X�N���[���j
    void SetFullscreenState(BOOL value);
private:
    // �X�V����
    void Update(DX::StepTimer const& timer);
    // �`�揈��
    void Render();

    void Clear();
    // �f�o�C�X�ˑ��������\�[�X�𐶐�����
    void CreateDeviceDependentResources();
    // �E�B���h�E�T�C�Y�Ɉˑ��������\�[�X�𐶐�����
    void CreateWindowSizeDependentResources();

private:
    // �E�B���h�E�n���h��
    HWND            m_hWnd;
    // �^�C�}�[
    DX::StepTimer   m_timer;

    // �f�o�C�X���\�[�X
    DX::DeviceResources* m_deviceResources;
    // �t���X�N���[��
    BOOL m_full_screen;

    // �O���t�B�b�N�X
    Graphics* m_graphics;
};