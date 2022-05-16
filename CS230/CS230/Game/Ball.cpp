#include"Ball.h"
#include"Mode1.h"
#include"..\Engine\Camera.h"
Ball::Ball(math::vec2 startPos,const CS230::Camera&camera):initPosition(startPos),camera(camera),currstate(&land)
{

}

void Ball::Load()
{
	
	sprite.Load("Assets/ball.png", math::ivec2{43,2});
	position = initPosition;
	velocity = { 0, 0 };
	currstate = &land;
	currstate->Enter(this);
	
}


void Ball::Update(double dt)
{
	currstate->Update(this, dt);
	position += velocity * dt;
	currstate->TestForExit(this);

	objectMatrix = math::TranslateMatrix(position);
}


void Ball::Draw(math::TransformMatrix& cameraMatrix) 
{
	sprite.Draw(cameraMatrix*objectMatrix);
}

void Ball::ChangeState(State* newState)
{
	Engine::GetLogger().LogDebug("Ball Leaving State: " + currstate->GetName() + " Entering State: " + newState->GetName());
	currstate = newState;
	currstate->Enter(this);
}



void Ball::State_Bounce::Enter(Ball* ball)
{
	ball->velocity.y = Ball::bounceVelocity;
}
void Ball::State_Bounce::Update(Ball* ball, double dt) {
	ball->velocity.y -= Mode1::gravity * dt;
}
void Ball::State_Bounce::TestForExit(Ball* ball) {
	if (ball->position.y < Mode1::floor)
	{
		ball->position.y = Mode1::floor;
		ball->velocity.y = 0;
		ball->ChangeState(&ball->land);
	}
}

void Ball::State_Land::Enter(Ball*) { }
void Ball::State_Land::Update([[maybe_unused]] Ball* ball, [[maybe_unused]] double dt) {}
void Ball::State_Land::TestForExit(Ball* ball)
{
	ball->ChangeState(&ball->bounce);
}