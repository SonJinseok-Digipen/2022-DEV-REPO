/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: main.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include <stdexcept>	//std::exception
#include <iostream>		//std::cerr

#include "Engine/Engine.h"
#include "Game/Splash.h"
#include "Game/Mode1.h"
#include "Game/Mode2.h"
#include "Game/Screens.h"


int main(void) {
	try {
		Engine& engine = Engine::Instance();
		engine.Init("Week 4 - Jinseok Son");
		Splash splash;
		Mode1 mode1;
		Mode2 mode2;

		engine.GetGameStateManager().AddGameState(splash);
		engine.GetGameStateManager().AddGameState(mode1);
		engine.GetGameStateManager().AddGameState(mode2);

		while (engine.HasGameEnded() == false) {
			engine.Update();
		}
		engine.Shutdown();
		return 0;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << "\n";
		return -1;
	}
}