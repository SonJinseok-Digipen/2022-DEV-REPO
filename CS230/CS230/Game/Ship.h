#pragma once
#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include"..\Engine\TransformMatrix.h"
#include"..\Engine\GameObject.h"
class Ship :public CS230::GameObject{
public:
    Ship(math::vec2 startPos);
    void Update(double dt) override;
    void Draw(math::TransformMatrix cameraMatrix) override;
    void TestForWrap();
private:
    CS230::Sprite sprite;
    math::vec2 startPos;
    math::vec2 position;
    math::vec2 velocity;
    double rotation;
   //Todo: if the rotateCounterKey is down, change the rotation variable by the rotation rate so it rotates in the counterclockwise direction

    CS230::Sprite Leftflame;
    CS230::Sprite Rightflame;
    CS230::InputKey rotateCounterKey;
    CS230::InputKey counterclockwise;
    CS230::InputKey accelerateKey;
    CS230::InputKey dragKey;
    math::TransformMatrix objectMatrix;
    bool isAccel;
    static constexpr double accel = 400;
    static constexpr double drag = 1.0f;
    static constexpr double rotationRate = 2.0;

};