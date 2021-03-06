#pragma once
/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Splash.h"

Splash::Splash() : modeNext(CS230::InputKey::Keyboard::Enter) {}

void Splash::Load()
{
	texture.Load("Assets/DigiPen_BLACK_1024px.png");
}
void Splash::Update(double dt) {


	timer += dt;
	if (timer>=3) 
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode1));
	}
	
}
void Splash::Unload() {
}

void Splash::Draw()
{
	Engine::GetWindow().Clear(0xffffffff);
	texture.Draw((Engine::GetWindow().GetSize()/2.0)-(texture.GetSize()/2.0));

}
