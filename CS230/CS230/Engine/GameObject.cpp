#include"..\Engine\GameObject.h"
#include <iostream>
#include "..\Engine\Engine.h"
CS230::GameObject::GameObject(math::vec2 position) : GameObject(position, 0, { 1, 1 }) {}

CS230::GameObject::GameObject(math::vec2 position, double rotation, math::vec2 scale)
    : velocity{ 0,0 }, position(position), updateMatrix(true),
    scale(scale), rotation(rotation), currState(&state_nothing)
{
    currState->Enter(this);
    SetRotation(rotation);
}

void CS230::GameObject::Update(double dt)
{

    currState->Update(this, dt);
    sprite.Update(dt);
    UpdatePosition(velocity * dt);
    currState->TestForExit(this);

}

void CS230::GameObject::ChangeState(State* newState) {
    currState = newState;
    currState->Enter(this);
}

void CS230::GameObject::Draw(math::TransformMatrix cameraMatrix) {
    sprite.Draw(cameraMatrix * GetMatrix());
}

const math::TransformMatrix& CS230::GameObject::GetMatrix()
{
    if (updateMatrix == true)
    {
        objectMatrix = math::TranslateMatrix(position) * math::RotateMatrix(rotation) * math::ScaleMatrix(scale);
        updateMatrix = false;
    }
    return objectMatrix;
}

void CS230::GameObject::SetPosition(math::vec2 newPosition) {
    position = newPosition;
    updateMatrix = true;
}

void CS230::GameObject::SetVelocity(math::vec2 newVelocity) {
    velocity = newVelocity;
}

void CS230::GameObject::UpdatePosition(math::vec2 adjustPosition) {
    position += adjustPosition;
    updateMatrix = true;
}

const math::vec2& CS230::GameObject::GetPosition() const { return position; }


const math::vec2& CS230::GameObject::GetVelocity() const
{
    return velocity;
}

const math::vec2& CS230::GameObject::GetScale() const
{
    return scale;
}

double CS230::GameObject::GetRotation() const
{
    return rotation;
}

void CS230::GameObject::SetRotation(double newRotationAmount)
{
    rotation = newRotationAmount;
}

void CS230::GameObject::SetScale(math::vec2 newScale)
{
    scale = newScale;
}

void CS230::GameObject::UpdateRotation(double newRotationAmount)
{
    rotation += newRotationAmount;
    updateMatrix = true;
}

void CS230::GameObject::UpdateVelocity(math::vec2 adjustPosition)
{
    velocity += adjustPosition;
    updateMatrix = true;
}
