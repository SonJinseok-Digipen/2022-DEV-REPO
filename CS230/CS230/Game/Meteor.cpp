#include"Meteor.h"
#include"..\Engine\Engine.h"
Meteor::Meteor(math::vec2 pos, math::vec2 velocity) : GameObject(pos, 0.5, { 1.0, 1.0 }) {
	sprite.Load("assets/Meteor.spt");

	SetVelocity(velocity);
}

void Meteor::Update(double dt)
{
	GameObject::Update(dt);
}

void Meteor::TestForWrap()
{
	if (GetPosition().y > Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0)
	{
		//position.y = 0 - sprite.GetFrameSize().y / 2.0;
		SetPosition(math::vec2{ GetPosition().x, 0 - sprite.GetFrameSize().y / 2.0 });
	}
	else if (GetPosition().y < 0 - sprite.GetFrameSize().y / 2.0)
	{
		SetPosition(math::vec2{ GetPosition().x, Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0 });
	}
	if (GetPosition().x > Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0)
	{
		SetPosition(math::vec2{ 0 - sprite.GetFrameSize().x / 2.0 ,GetPosition().y });

	}
	else if (GetPosition().x < 0 - sprite.GetFrameSize().x / 2.0)
	{
		SetPosition(math::vec2{ Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0 ,GetPosition().y });
	}
}