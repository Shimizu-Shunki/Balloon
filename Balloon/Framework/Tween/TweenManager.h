#pragma once
#include <memory>
#include "Framework/Tween/Tween.h"
#include "Framework/StepTimer.h"

class Tween;
class CommonResources;

class TweenManager {

private:

	static const int INITIAL_TWEEN_COUNT;

private:
	//	�R���X�g���N�^
	TweenManager();
	// �f�X�g���N�^
	~TweenManager();
public:
	TweenManager(const TweenManager&) = delete;             // �R�s�[�֎~
	TweenManager& operator=(const TweenManager&) = delete;  // �R�s�[����֎~
	TweenManager(const TweenManager&&) = delete;            // ���[�u�֎~
	TweenManager& operator=(const TweenManager&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static TweenManager* GetInstance()
	{
		static TweenManager instance;
		return &instance;
	}

public:
    // �X�V����
    void Update();
	// ��A�N�e�B�u��Tween���擾����
	Tween* GetTween();

private:
	// ���L���\�[�X
	CommonResources* m_commonResources;
    // tween���i�[
    std::vector<std::unique_ptr<Tween>> tweens;
};