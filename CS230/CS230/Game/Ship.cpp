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
	sprite.Load("assets/Ship.spt");
	Leftflame.Load("assets/Flame.spt");
	Rightflame.Load("assets/Flame.spt");
}

void Ship::Update(double dt)
{
	if (rotateCounterKey.IsKeyDown() == true) 
	{
		rotation += 0.1;
		Leftflame.ShowFrame(0);
		Rightflame.ShowFrame(0);
	}
	else if (counterclockwise.IsKeyDown() == true) 
	{
		rotation -= 0.1;
		Leftflame.ShowFrame(0);
		Rightflame.ShowFrame(0);
	}
	else if (accelerateKey.IsKeyDown() == true) 
	{
		velocity += math::RotateMatrix(rotation) * math::vec2{ 0, accel * dt };
		Leftflame.ShowFrame(0);
		Rightflame.ShowFrame(0);
	}
	else if (dragKey.IsKeyDown() == true) 
	{
		velocity -= drag * dt*2;
		Leftflame.ShowFrame(0);
		Rightflame.ShowFrame(0);
	}
	else
	{
		Leftflame.ShowFrame(4);
		Rightflame.ShowFrame(4);
	}

	velocity -= (velocity * Ship::drag * dt);
	position += velocity * dt;
	TestForWrap();
	
	objectMatrix = math::TranslateMatrix(position)*math::RotateMatrix(rotation)*math::ScaleMatrix({ 0.75, 0.75 });

}

void Ship::Draw()
{
		sprite.Draw(objectMatrix);
		Leftflame.Draw( objectMatrix*math::TranslateMatrix( sprite.GetHotSpot(1)));
	    Rightflame.Draw(objectMatrix* math::TranslateMatrix(sprite.GetHotSpot(2)));
}

void Ship::TestForWrap()
{

	if (position.y > Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0) {
		position.y = 0 - sprite.GetFrameSize().y / 2.0;
	}
	else if (position.y < 0 - sprite.GetFrameSize().y) {
		position.y = Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0;
	}

	if (position.x > Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0) {
		position.x = 0 - sprite.GetFrameSize().x / 2.0;
	}
	else if (position.x < 0 - sprite.GetFrameSize().x) {
		position.x = Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0;
	}

}