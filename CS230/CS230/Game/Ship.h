#pragma once
#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include"..\Engine\TransformMatrix.h"
class Ship {
public:
    Ship(math::vec2 startPos);
    void Load();
    void Update(double dt);
    void Draw();
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
    static constexpr double accel = 400;
    static constexpr double drag = 1.0f;

};