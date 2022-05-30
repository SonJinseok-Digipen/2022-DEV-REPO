/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetLogger
#include "../Engine/Camera.h"
#include "Mode1.h"	//Level1::gravity
#include "Hero.h"

#include <iostream>

#include "Hero_Anims.h"

Hero::Hero(math::vec2 startPos, const CS230::Camera& camera) : GameObject(startPos), camera(camera),
jumpKey(CS230::InputKey::Keyboard::Up),
moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right), isFlipped(false)
{
	sprite.Load("assets/Hero.spt");
	currState = &stateIdle;
	currState->Enter(this);

}



void Hero::Update(double dt)
{
	
	GameObject::Update(dt);
	// Boundry Check
	if (GetPosition().x < camera.GetPosition().x + sprite.GetFrameSize().x / 2)
	{
		SetPosition(math::vec2{ camera.GetPosition().x + sprite.GetFrameSize().x / 2 ,GetPosition().y });
		SetVelocity(math::vec2{ 0,GetVelocity().y});

	}
	if (GetPosition().x + sprite.GetFrameSize().x / 2 > camera.GetPosition().x + Engine::GetWindow().GetSize().x)
	{
		SetPosition(math::vec2{ camera.GetPosition().x + Engine::GetWindow().GetSize().x - sprite.GetFrameSize().x / 2 ,GetPosition().y });
		SetVelocity(math::vec2{ 0,GetVelocity().y });
	}
	//objectMatrix = math::TranslateMatrix(position);
	if (isFlipped == true)
	{
		SetScale(math::vec2{ -1,1 });
	}
	if (isFlipped == false)
	{
		SetScale(math::vec2{ 1,1 });
	}
}




void Hero::State_Idle::Enter(GameObject* hero)
{

	static_cast<Hero*>(hero)->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
}
void Hero::State_Idle::Update(GameObject*, double)
{

}
void Hero::State_Idle::TestForExit(GameObject* hero)
{


	if (static_cast<Hero*>(hero)->moveLeftKey.IsKeyDown() == true)
	{

	}

	if (static_cast<Hero*>(hero)->moveRightKey.IsKeyDown() == true)
	{
		static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateRunning);
	}
	if (static_cast<Hero*>(hero)->jumpKey.IsKeyDown() == true)
	{
		static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateJumping);
	}


}

void Hero::State_Running::Enter(GameObject* hero) {
	static_cast<Hero*>(hero)->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
	if (static_cast<Hero*>(hero)->moveRightKey.IsKeyDown() == true) {
		static_cast<Hero*>(hero)->isFlipped = false;
	}
	if (static_cast<Hero*>(hero)->moveLeftKey.IsKeyDown() == true) {
		static_cast<Hero*>(hero)->isFlipped = true;
	}
}
void Hero::State_Running::Update(GameObject* hero, double dt) {
	static_cast<Hero*>(hero)->UpdateXVelocity(dt);
}
void Hero::State_Running::TestForExit(GameObject* hero) {
	if (static_cast<Hero*>(hero)->moveLeftKey.IsKeyDown() == true && hero->GetVelocity().x > 0) {
		static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateSkidding);
	}
	if (static_cast<Hero*>(hero)->moveRightKey.IsKeyDown() == true && static_cast<Hero*>(hero)->GetVelocity().x < 0) {
		static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateSkidding);
	}
	if (static_cast<Hero*>(hero)->GetVelocity().x == 0) {
		static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateIdle);
	}
	if (static_cast<Hero*>(hero)->jumpKey.IsKeyDown() == true) {
		static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateJumping);
	}
}

void Hero::State_Skidding::Enter(GameObject* hero) {
	static_cast<Hero*>(hero)->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}
void Hero::State_Skidding::Update(GameObject* hero, double dt) {
	if (static_cast<Hero*>(hero)->GetVelocity().x > 0)
	{
		static_cast<Hero*>(hero)->UpdateVelocity(math::vec2{ -(xDrag + xAccel) * dt,0 });
	}
	else if (hero->GetVelocity().x < 0)
	{
		static_cast<Hero*>(hero)->UpdateVelocity(math::vec2{ (xDrag + xAccel) * dt,0 });

	}
}
void Hero::State_Skidding::TestForExit(GameObject* hero) {
	if (static_cast<Hero*>(hero)->moveLeftKey.IsKeyDown() == true) {
		if (static_cast<Hero*>(hero)->GetVelocity().x <= 0) {
			static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateRunning);
		}
	}
	else if (static_cast<Hero*>(hero)->moveRightKey.IsKeyDown() == true) {
		if (static_cast<Hero*>(hero)->GetVelocity().x >= 0) {
			static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateRunning);
		}
	}
	else {
		static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateRunning);
	}
	if (static_cast<Hero*>(hero)->jumpKey.IsKeyDown() == true) {
		static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateJumping);
	}
}

void Hero::State_Jumping::Enter(GameObject* hero) {
	static_cast<Hero*>(hero)->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
	static_cast<Hero*>(hero)->SetVelocity(math::vec2{ hero->GetVelocity().x,Hero::jumpVelocity });
}
void Hero::State_Jumping::Update(GameObject* hero, double dt)
{
	static_cast<Hero*>(hero)->UpdateVelocity(math::vec2{ 0,-Mode1::gravity * dt });
	static_cast<Hero*>(hero)->UpdateXVelocity(dt);
}
void Hero::State_Jumping::TestForExit(GameObject* hero) {
	if (static_cast<Hero*>(hero)->jumpKey.IsKeyDown() == false) {
		static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateFalling);
		static_cast<Hero*>(hero)->SetVelocity(math::vec2{ hero->GetVelocity().x,0 });
	}
	else if (static_cast<Hero*>(hero)->GetVelocity().y <= 0) {
		static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateFalling);
	}
}

void Hero::State_Falling::Enter(GameObject* hero) {
	static_cast<Hero*>(hero)->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}
void Hero::State_Falling::Update(GameObject* hero, double dt)
{
	static_cast<Hero*>(hero)->UpdateVelocity(math::vec2{ 0,-Mode1::gravity * dt });
	static_cast<Hero*>(hero)->UpdateXVelocity(dt);
}
void Hero::State_Falling::TestForExit(GameObject* hero) {
	if (hero->GetPosition().y <= Mode1::floor) {
		if (hero->GetVelocity().x > 0) {
			if (static_cast<Hero*>(hero)->moveLeftKey.IsKeyDown() == true) {
				static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateSkidding);
			}
			else {
				static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateRunning);
			}
		}
		else if (static_cast<Hero*>(hero)->GetVelocity().x < 0) {
			if (static_cast<Hero*>(hero)->moveRightKey.IsKeyDown() == true) {
				static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateSkidding);
			}
			else {
				static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateRunning);
			}
		}
		else {
			static_cast<Hero*>(hero)->ChangeState(&static_cast<Hero*>(hero)->stateIdle);
		}
		static_cast<Hero*>(hero)->SetVelocity(math::vec2{ hero->GetVelocity().x,0 });
		static_cast<Hero*>(hero)->SetPosition(math::vec2{ hero->GetPosition().x,Mode1::floor });


	}
}

void Hero::UpdateXVelocity(double dt) {
	if (moveLeftKey.IsKeyDown() == true)
	{
		UpdateVelocity(math::vec2{ -Hero::xAccel * dt,0 });
		// apply acceleration
		if (GetVelocity().x < -Hero::maxXVelocity) {
			SetVelocity(math::vec2{ -Hero::maxXVelocity ,GetVelocity().y });
		}
	}
	else if (moveRightKey.IsKeyDown() == true) {
		UpdateVelocity(math::vec2{ Hero::xAccel * dt,0 });	// apply acceleration
		if (GetVelocity().x > Hero::maxXVelocity)
		{
			SetVelocity(math::vec2{ Hero::maxXVelocity ,GetVelocity().y });
		}
	}
	else {
		// no key is down, need to apply drag to slow down
		double xDragDt = Hero::xDrag * dt;
		if (GetVelocity().x > xDragDt)
		{
			//velocity.x -= xDragDt;
			UpdateVelocity(math::vec2{ -xDragDt,0 });
		}
		else if (GetVelocity().x < -xDragDt)
		{
			//velocity.x += xDragDt;
			UpdateVelocity(math::vec2{ xDragDt,0 });
		}
		else {
			SetVelocity(math::vec2{ 0,GetVelocity().y });
		}
	}
}