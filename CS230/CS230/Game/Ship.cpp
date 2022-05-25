#include "Ship.h"
#include "..\Engine/Engine.h"
#include"Flame_Anims.h"
Ship::Ship(math::vec2 startPos) : rotateCounterKey(CS230::InputKey::Keyboard::A), 
counterclockwise(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W), 
dragKey(CS230::InputKey::Keyboard::S),startPos(startPos),rotation(),isAccel(false)
{
	position = startPos;
	sprite.Load("Assets/Ship.spt");
	Leftflame.Load("Assets/Flame.spt");
	Rightflame.Load("Assets/Flame.spt");
}


void Ship::Update(double dt)
{
	if (rotateCounterKey.IsKeyDown() == true) 
	{
		rotation += 0.1;
		
	}
	else if (counterclockwise.IsKeyDown() == true) 
	{
		rotation -= 0.1;
		
	}
	else if (accelerateKey.IsKeyDown() == true) 
	{
		velocity += math::RotateMatrix(rotation) * math::vec2{ 0, accel * dt };
		if (isAccel == false) {
			Leftflame.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			Rightflame.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			isAccel = true;
		}
		
	}
	else if (dragKey.IsKeyDown() == true) 
	{
		velocity -= drag * dt*2;
		
	}
	else
	{
		if (isAccel == true) {
			Engine::GetLogger().LogDebug("Stopped Accelerating");
			Leftflame.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			Rightflame.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			isAccel = false;
		}
	}

	velocity -= (velocity * Ship::drag * dt);
	position += velocity * dt;
	TestForWrap();
	sprite.Update(dt);
	Leftflame.Update(dt);
	Rightflame.Update(dt);
	objectMatrix = math::TranslateMatrix(position)*math::RotateMatrix(rotation)*math::ScaleMatrix({ 0.75, 0.75 });

}

void Ship::Draw(math::TransformMatrix cameraMatrix)
{
		sprite.Draw(objectMatrix);
		if (isAccel == true)
		{
			Leftflame.Draw((objectMatrix *cameraMatrix) * math::TranslateMatrix(sprite.GetHotSpot(1)));
			Rightflame.Draw((objectMatrix * cameraMatrix) * math::TranslateMatrix(sprite.GetHotSpot(2)));

		}


		if (isAccel == false)
		{
			Leftflame.Draw((objectMatrix * cameraMatrix) * math::TranslateMatrix(sprite.GetHotSpot(1)));
			Rightflame.Draw((objectMatrix * cameraMatrix) * math::TranslateMatrix(sprite.GetHotSpot(2)));

		}
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