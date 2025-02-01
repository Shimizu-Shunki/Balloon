#pragma once
#include "StateController.h"
#include "Parameters.h"
#include <iostream>
#include <vector>

class CommonResources;

class StateMachine
{
public:
	// コントローラーを追加する
	void AddController(std::unique_ptr<StateController> controller)
	{
		m_controllers.push_back(std::move(controller));
	}
	
	// 初期化処理
	// 更新処理
	void Update();

	void Start();

	StateMachine();

private:
	// 共有リソース
	CommonResources* m_commonResources;
	// コントローラーを格納
	std::vector<std::unique_ptr<StateController>> m_controllers;
};