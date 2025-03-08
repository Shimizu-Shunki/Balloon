#pragma once
#include "Interface/IScene.h"
#include <Game/Material/SeaMaterial.h>


class CommonResources;
class PBRLit;
class SkyBox;
class Model3D;
class Player;

class DebugScene : public IScene
{
public:
	// �R���X�g���N�^
	DebugScene();
	// �f�X�g���N�^
	~DebugScene();

public:
	// ����������
	void Initialize() override;
	// �X�^�[�g����
	void Start()  override;
	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;
	// �I������
	void Finalize() override;

private:

	// ���L���\�[�X
	CommonResources* m_commonResources;


	DirectX::CommonStates* m_commonStates;

	// �f�o�b�O�J�����Ŏ���
	std::unique_ptr<DebugCamera> m_debugCamera;



	// �u�����h�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;



	std::unique_ptr<Player> m_plaeyr;


};