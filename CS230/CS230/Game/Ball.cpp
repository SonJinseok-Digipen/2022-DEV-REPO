/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"  //GetLogger
#include "Mode1.h"	//Level1::gravity, floor
#include "Ball.h"
#include "Ball_Anims.h"
#include "../Engine/Input.h"

Ball::Ball(math::vec2 startPos) : GameObject(startPos) {
    sprite.Load("Assets/Ball.spt");
    currState = &stateBounce;
    currState->Enter(this);
}

void Ball::ChangeState(State* newState) {
    //Engine::GetLogger().LogDebug("Ball Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
    currState = newState;
    currState->Enter(this);
}

void Ball::State_Bounce::Enter(GameObject* object) {
    static_cast<Ball*>(object)->sprite.PlayAnimation(static_cast<int>(Ball_Anim::None_Anim));
    static_cast<Ball*>(object)->SetVelocity(math::vec2{ 0, Ball::bounceVelocity });
}
void Ball::State_Bounce::Update(GameObject* object, double dt)
{
    static_cast<Ball*>(object)->UpdateVelocity(math::vec2{ 0,-Mode1::gravity * dt });
}
void Ball::State_Bounce::TestForExit(GameObject* object)
{
    if (static_cast<Ball*>(object)->GetPosition().y < Mode1::floor) {
        static_cast<Ball*>(object)->SetPosition({ static_cast<Ball*>(object)->GetPosition().x, Mode1::floor });
        static_cast<Ball*>(object)->SetVelocity({ 0, 0 });
        static_cast<Ball*>(object)->ChangeState(&static_cast<Ball*>(object)->stateLand);
    }
}

void Ball::State_Land::Enter(GameObject* object) {
    static_cast<Ball*>(object)->sprite.PlayAnimation(static_cast<int>(Ball_Anim::Squish_Anim));
}
void Ball::State_Land::Update(GameObject* object, double dt) {}
void Ball::State_Land::TestForExit(GameObject* object) {
    if (static_cast<Ball*>(object)->sprite.IsAnimationDone() == true) {
        static_cast<Ball*>(object)->ChangeState(&static_cast<Ball*>(object)->stateBounce);
    }
}