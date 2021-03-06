/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.h
Project: CS230
Author: Kevin Wright
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine/GameObject.h"
class Ball :public  CS230::GameObject
{
public:
	Ball(math::vec2 startPos);



private:

	class State_Bounce : public State {
		void Enter(GameObject* ball) override;
		void Update(GameObject* ball, double dt) override;
		void TestForExit(GameObject* ball) override;
		std::string GetName() override { return "bounce"; }
	};
	class State_Land : public State {
		void Enter(GameObject* ball) override;
		void Update(GameObject* ball, double dt) override;
		void TestForExit(GameObject* ball) override;
		std::string GetName() override { return "squish"; }
	};
	State_Bounce stateBounce;
	State_Land stateLand;


	void ChangeState(State* newState);


	static constexpr double bounceVelocity = 700;
};