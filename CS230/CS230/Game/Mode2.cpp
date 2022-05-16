#include "Mode2.h"

#include "Screens.h"
#include "..\Engine\Engine.h"
#include"..\Engine\Vec2.h"
Mode2::Mode2() :modeNext(CS230::InputKey::Keyboard::Enter), modeReload(CS230::InputKey::Keyboard::R), 
ship({ static_cast<double>(Engine::GetWindow().GetSize().x /2.0),static_cast<double>(Engine::GetWindow().GetSize().y /2.0) })
{
}

void Mode2::Load()
{
	ship.Load();
}

void Mode2::Update([[maybe_unused]]double dt)
{
#ifdef _DEBUG				
	if (modeReload.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}
#else 						
#endif
	if (modeNext.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().Shutdown();
	}
	ship.Update(dt);
}

void Mode2::Unload()
{
}

void Mode2::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);
	ship.Draw();
}
