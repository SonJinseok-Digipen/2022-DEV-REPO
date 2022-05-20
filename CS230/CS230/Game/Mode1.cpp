#include "Mode1.h"
#include "..\Engine\Engine.h"
#include "Screens.h"
Mode1::Mode1() :modeNext(CS230::InputKey::Keyboard::Enter), modeReload(CS230::InputKey::Keyboard::R),
camera(math::rect2{ Engine::GetWindow().GetSize() * 0.15,Engine::GetWindow().GetSize() * 0.35 }),
hero({Engine::GetWindow().GetSize().x/2.0,Mode1::floor},camera),
ball({ 600, Mode1::floor },camera), 
ball2({ 2700, Mode1::floor }, camera),
ball3({ 4800, Mode1::floor }, camera)
{

}

void Mode1::Load()
{
	hero.Load();
	ball.Load();
	ball2.Load();
	ball3.Load();
	background.Add("Assets/foreground.png", 1);
	background.Add("Assets/Moutains.png", 2);
	background.Add("Assets/clouds.png", 4);
	camera.SetPosition({ 0,0 });
	camera.SetExtent({ { 0,0 }, {background.Size() - Engine::GetWindow().GetSize() } });

}
void Mode1::Update([[maybe_unused]]double dt)
{
#ifdef _DEBUG				
	if(modeReload.IsKeyReleased()==true)
	{
		Engine::GetGameStateManager().ReloadState();
	}
#else 						
	#endif
	if(modeNext.IsKeyReleased()==true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode2));
	}
	camera.Update(hero.GetPoistion());
	hero.Update(dt);
	ball.Update(dt);
	ball2.Update(dt);
	ball3.Update(dt);

	//Engine::GetLogger().LogDebug(std::to_string(camera.GetPosition().x));
}

void Mode1::Unload()
{
	background.Unload();
}

void Mode1::Draw()
{
	Engine::GetWindow().Clear(0x0000ffff);
	//back ground drawing order should be cloud mountatin foreground
	background.Draw(camera);
	math::TransformMatrix cameraMatrix = camera.GetMatrix();
	hero.Draw(cameraMatrix);
	ball.Draw(cameraMatrix);
	ball2.Draw(cameraMatrix);
	ball3.Draw(cameraMatrix);

}
