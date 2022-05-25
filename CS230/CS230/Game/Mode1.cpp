#include "Mode1.h"
#include "..\Engine\Engine.h"
#include "Screens.h"
Mode1::Mode1() : camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, {0.35 * Engine::GetWindow().GetSize().x, 0 } }),
modeReload(CS230::InputKey::Keyboard::R), modeNext(CS230::InputKey::Keyboard::Enter) {}

void Mode1::Load()
{
	heroPtr = new Hero({ 150, Mode1::floor }, camera);
	gameObjectManager.Add(heroPtr);

	 
	gameObjectManager.Add(new Ball({ 600, Mode1::floor },camera));
	gameObjectManager.Add(new Ball({ 2700, Mode1::floor },camera));
	gameObjectManager.Add(new Ball({ 4800, Mode1::floor },camera));
	   
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
	if (modeNext.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode2));
	}
	gameObjectManager.UpdateAll(dt);
	camera.Update(heroPtr->GetPoistion());
	

	Engine::GetLogger().LogDebug(std::to_string(camera.GetPosition().x));
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
	gameObjectManager.DrawAll(cameraMatrix);

}
