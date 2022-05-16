#pragma once
/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.h
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include"Hero.h"
#include"Ball.h"
#include"..\Engine\Camera.h"
#include"Background.h"
class Mode1 : public CS230::GameState 
{
public:
	static constexpr double floor = 126.0f;
	static constexpr double gravity = 940;
	Mode1();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;
	std::string GetName() override { return "Mode 1"; }
private:
	CS230::Camera camera;
	Hero hero;
	Ball ball;
	Ball ball2;
	Ball ball3;
	Background background;
	
	
	CS230::InputKey modeNext;
	CS230::InputKey modeReload;
};