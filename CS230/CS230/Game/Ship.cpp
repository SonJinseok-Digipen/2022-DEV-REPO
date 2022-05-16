#include "Ship.h"
#include "..\Engine/Engine.h"
Ship::Ship(math::vec2 startPos) : rotateCounterKey(CS230::InputKey::Keyboard::A), 
counterclockwise(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W), 
dragKey(CS230::InputKey::Keyboard::S),startPos(startPos),rotation()
{
	
}

void Ship::Load()
{
	position = startPos;
	sprite.Load("assets/Ship.png", math::ivec2{50,42});

}

void Ship::Update(double dt)
{
	if (rotateCounterKey.IsKeyDown() == true) 
	{
		rotation += 0.1;
		
	}
	if (counterclockwise.IsKeyDown() == true) 
	{
		rotation -= 0.1;
	}
	if (accelerateKey.IsKeyDown() == true) 
	{
		velocity += math::RotateMatrix(rotation) * math::vec2{ 0, accel * dt };
	}
	if (dragKey.IsKeyDown() == true) 
	{
		velocity -= drag * dt*2;
	}

	velocity -= (velocity * Ship::drag * dt);
	position += velocity * dt;
	TestForWrap();
	
	objectMatrix = math::TranslateMatrix(position)*math::RotateMatrix(rotation)*math::ScaleMatrix({ 0.75, 0.75 });

}

void Ship::Draw()
{
		sprite.Draw(objectMatrix);
}

void Ship::TestForWrap()
{

	if (position.y > Engine::GetWindow().GetSize().y + sprite.GetTextureSize().y / 2.0) {
		position.y = 0 - sprite.GetTextureSize().y / 2.0;
	}
	else if (position.y < 0 - sprite.GetTextureSize().y) {
		position.y = Engine::GetWindow().GetSize().y + sprite.GetTextureSize().y / 2.0;
	}

	if (position.x > Engine::GetWindow().GetSize().x + sprite.GetTextureSize().x / 2.0) {
		position.x = 0 - sprite.GetTextureSize().x / 2.0;
	}
	else if (position.x < 0 - sprite.GetTextureSize().x) {
		position.x = Engine::GetWindow().GetSize().x + sprite.GetTextureSize().x / 2.0;
	}

}