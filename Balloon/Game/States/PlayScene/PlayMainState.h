#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"
#include "Game/Fade/Fade.h"


class InputManager;
class Enemy;
class Player;

class PlayMainState : public IState
{
public:

public:

    // �R���X�g���N�^
    PlayMainState(Player* player, std::vector<Enemy*> enemys);
    // �f�X�g���N�^
    ~PlayMainState() override;

public:
    // ����������
    void OnStateEnter(StateController* stateController) override;
    // �X�V����
    void OnStateUpdate(StateController* stateController, const float& deltaTime) override;
    // �I������
    void OnStateExit(StateController* stateController) override;

private:
   // ���̓}�l�[�W���[
    InputManager* m_inputManager;

    // �G�l�~�[
    std::vector<Enemy*> m_enemys;
    // �v���C���[
    Player* m_player;
};