#include "Hero.h"
#include"..\Engine\Engine.h"
#include"Mode1.h"
#include"..\Engine\Camera.h"
#include"Hero_Anims.h"
Hero::Hero(math::vec2 startPos,const CS230::Camera&camera) :moveLeftKey(CS230::InputKey::Keyboard::Left),moveRightKey(CS230::InputKey::Keyboard::Right),
moveJumpKey(CS230::InputKey::Keyboard::Up),currState(&stateIdle),
position(startPos),camera(camera),IsJumping(false),isRising(false)
{
	sprite.Load("Assets/Hero.spt");
	
	
}



void Hero::Update(double dt)
{
	
	


	currState->Update(this, dt);
	position += velocity * dt;
	sprite.Update(dt);
	currState->TestForExit(this);

	position += velocity * dt;
	if (position.x < camera.GetPosition().x + sprite.GetFrameSize().x / 2)
	{
		position.x = camera.GetPosition().x + sprite.GetFrameSize().x / 2;
		velocity.x = 0;
	}
	if (position.x + sprite.GetFrameSize().x / 2 > camera.GetPosition().x + Engine::GetWindow().GetSize().x) 
	{
		position.x = camera.GetPosition().x + Engine::GetWindow().GetSize().x - sprite.GetFrameSize().x / 2;
		velocity.x = 0;
	}
	objectMatrix = math::TranslateMatrix(position);
	if (isFliped == true)
	{
		objectMatrix *= math::ScaleMatrix({ -1.0, 1 });
	}
	
	
}


void Hero::UpdateXVelocity(double dt)
{
	if (moveRightKey.IsKeyDown() == true)
	{
		
		if (velocity.x > 0)
		{
			velocity.x += xAcceleration.x * dt;

			if (velocity.x >= MaxXvelocity.x)
			{
				velocity.x = MaxXvelocity.x;
				Engine::GetLogger().LogDebug("+Max Velocity");
			}
			else
			{
				Engine::GetLogger().LogDebug("+Accelerating");
			}


		}
		else
		{
			velocity.x += xDrag.x * dt;
			Engine::GetLogger().LogDebug("+Skidding");
		}
	}
	else if (moveLeftKey.IsKeyDown() == true)
	{
		
		if (velocity.x < 0)
		{
			velocity.x -= xAcceleration.x * dt;

			if (velocity.x <= -1 * MaxXvelocity.x)
			{
				velocity.x = -1 * MaxXvelocity.x;
				Engine::GetLogger().LogDebug("-Max Velocity");
			}
			else
			{
				Engine::GetLogger().LogDebug("-Accelerating");
			}


		}
		else
		{
			velocity.x -= xDrag.x * dt;
			Engine::GetLogger().LogDebug("-Skidding");
		}
	}
	else
	{
		if (velocity.x > xDrag.x * dt) {
			Engine::GetLogger().LogDebug("-Dragging");
			velocity.x -= xDrag.x * dt;
		}
		else if (velocity.x < -xDrag.x * dt) {
			Engine::GetLogger().LogDebug("+Dragging");
			velocity.x += xDrag.x * dt;
		}
		else
		{
			if (velocity.x != 0)
			{
				Engine::GetLogger().LogDebug("Stopped");
			}
			velocity.x = 0;
		}
	}
	
}




void Hero::ChangeState(State* newState)
{
	Engine::GetLogger().LogDebug("Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
	currState = newState;
	currState->Enter(this);
}


void Hero::Draw(math::TransformMatrix cameraMaxtrix)
{
	sprite.Draw(cameraMaxtrix*objectMatrix);
}

math::vec2 Hero::GetPoistion()
{
	return position;
}


void Hero::State_Idle::Enter(Hero* hero)
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
}

void Hero::State_Idle::Update(Hero* hero, double dt)
{

}

void Hero::State_Idle::TestForExit(Hero* hero)
{
	if (hero->moveLeftKey.IsKeyDown() == true) 
	{
		hero->ChangeState(&hero->stateRunning);
		
	}
	if (hero->moveRightKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateRunning);
		
	}
	if (hero->moveJumpKey.IsKeyDown() == true) 
	{
		hero->ChangeState(&hero->stateJumping);
		
	}
	
}





void Hero::State_Running::Enter(Hero* hero)
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
	if (hero->moveRightKey.IsKeyDown() == true) 
	{
		hero->isFliped = false;
		
	}
	if (hero->moveLeftKey.IsKeyDown() == true) {
		hero->isFliped = true;
		
	}
}

void Hero::State_Running::Update(Hero* hero, double dt)
{
	hero->UpdateXVelocity(dt);
}

void Hero::State_Running::TestForExit(Hero* hero)
{

	if (hero->moveLeftKey.IsKeyDown() == true && hero->velocity.x > 0)
	{
		hero->ChangeState(&hero->stateSkidding);
	}
	if (hero->moveRightKey.IsKeyDown() == true && hero->velocity.x < 0)
	{
		hero->ChangeState(&hero->stateSkidding);
	}
	if (hero->velocity.x == 0)
	{
		hero->ChangeState(&hero->stateIdle);
	}
	if (hero->moveJumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Skidding::Enter(Hero* hero)
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Skid_Anim));
}

void Hero::State_Skidding::Update(Hero* hero, double dt)
{
	if (hero->velocity.x > 0) {
		hero->velocity.x -= (xDrag.x + xAcceleration.x) * dt;
	}
	else if (hero->velocity.x < 0) {
		hero->velocity.x += (xDrag.x + xAcceleration.x) * dt;
	}
}

void Hero::State_Skidding::TestForExit(Hero* hero)
{
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		if (hero->velocity.x <= 0) {
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		if (hero->velocity.x >= 0) {
			hero->ChangeState(&hero->stateRunning);
		}
	}
	if (hero->moveJumpKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Jumping::Enter(Hero* hero)
{
	hero->velocity.y = Hero::InstaneousJumpVelocity;
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
}

void Hero::State_Jumping::Update(Hero* hero, double dt)
{
	hero->velocity.y -= Mode1::gravity * dt;
	hero->UpdateXVelocity(dt);
}

void Hero::State_Jumping::TestForExit(Hero* hero)
{
	if (hero->moveJumpKey.IsKeyDown() == false)
	{
		hero->velocity.y = 0;
		hero->ChangeState(&hero->stateFalling);

	}
	else if (hero->velocity.y <= 0)
	{
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Falling::Enter(Hero* hero)
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}

void Hero::State_Falling::Update(Hero* hero, double dt)
{
	hero->velocity.y -= Mode1::gravity * dt;
	hero->UpdateXVelocity(dt);
}

void Hero::State_Falling::TestForExit(Hero* hero)
{
	if (hero->GetPoistion().y <= Mode1::floor)
	{
		hero->velocity.y = 0;
		hero->position.y = Mode1::floor;
		if (hero->velocity.x > 0)
		{
			if (hero->moveLeftKey.IsKeyDown() == true)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
			else
			{
				hero->ChangeState(&hero->stateRunning);
			}
		}

		else if (hero->velocity.x < 0)
		{
			if (hero->moveRightKey.IsKeyDown() == true) {
				hero->ChangeState(&hero->stateSkidding);
			}
			else {
				hero->ChangeState(&hero->stateRunning);
			}
		}
		else
		{
			hero->ChangeState(&hero->stateRunning);
		}
		if (hero->moveJumpKey.IsKeyDown() == true) {
			hero->ChangeState(&hero->stateJumping);
		}
	
	}
}
