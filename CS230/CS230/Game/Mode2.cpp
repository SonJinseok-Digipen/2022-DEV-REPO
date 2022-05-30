#include "Mode2.h"

#include "Screens.h"
#include "..\Engine\Engine.h"
#include"..\Engine\Vec2.h"
#include"Meteor.h"
Mode2::Mode2() :modeNext(CS230::InputKey::Keyboard::Enter), modeReload(CS230::InputKey::Keyboard::R)
{
}

void Mode2::Load()
{
	gameObjectManager.Add(new Ship({ Engine::GetWindow().GetSize().x / 2.0,Engine::GetWindow().GetSize().y / 2.0 }));
	gameObjectManager.Add(new Meteor({ 1000,500 }, { -33, 66 }));
	gameObjectManager.Add(new Meteor({ 650,750 }, { 100, -21 }));
	gameObjectManager.Add(new Meteor({ 415,190 }, { -84, 23 }));
	gameObjectManager.Add(new Meteor({ 350, 75 }, { -22,-10 }));
	gameObjectManager.Add(new Meteor({ 20,50 }, { 20, 40 }));

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
	gameObjectManager.UpdateAll(dt);
}

void Mode2::Unload()
{
}

void Mode2::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);
	math::TransformMatrix cameraMatrix;
	gameObjectManager.DrawAll(cameraMatrix);
}
