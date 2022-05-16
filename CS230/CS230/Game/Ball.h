#pragma once
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
#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "Hero.h"
#include"..\Engine\TransformMatrix.h"
#include"..\Engine\Engine.h"
namespace CS230
{
    class Camera;
}
class Ball {
public:
    Ball(math::vec2 startPos,const CS230::Camera&camera);
    void Load();
    void Update(double dt);
    void Draw(math::TransformMatrix&camera);

private:
    CS230::Sprite sprite;
    math::vec2 initPosition;
    math::vec2 position;
    math::vec2 velocity;

    static constexpr double bounceVelocity =700*0.75;
    const CS230::Camera& camera;
    math::TransformMatrix objectMatrix;

    class State
    {
    public:
        virtual void Enter(Ball* ball) = 0;
        virtual void Update(Ball* ball, double dt) = 0;
        virtual void TestForExit(Ball* ball) = 0;
        virtual std::string GetName() = 0;
    };

    class State_Bounce : public State
    {
       void Enter(Ball* ball)  override;
       void Update(Ball* ball, double dt)  override;
       void TestForExit(Ball* ball) override;
       std::string GetName() override { return "bounce"; }
    };

    class State_Land : public State
    {
        void Enter(Ball* ball)  override;
        void Update(Ball* ball, double dt)  override;
        void TestForExit(Ball* ball) override;
        std::string GetName() override { return "land"; }
    };
    void ChangeState(State* newState);
    State* currstate;
    State_Land land;
    State_Bounce bounce;
};