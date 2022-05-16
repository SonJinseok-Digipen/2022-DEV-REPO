#include "Input.h"
#include "Engine.h"
CS230::Input::Input()
{
	keyDown.resize(static_cast<int>(InputKey::Keyboard::Count),false);
	wasKeyDown.resize(static_cast<int>(InputKey::Keyboard::Count),false); 
}

bool CS230::Input::IsKeyDown(InputKey::Keyboard key) const
{
	return keyDown[static_cast<int>(key)];
}

bool CS230::Input::IsKeyReleased(InputKey::Keyboard key) const
{
	return (keyDown[static_cast<int>(key)] == false && wasKeyDown[static_cast<int>(key)] == true);
}

void CS230::Input::SetKeyDown(InputKey::Keyboard key, bool value)
{
	keyDown[static_cast<int>(key)] = value;
}

void CS230::Input::Update()
{
	wasKeyDown = keyDown;
}

CS230::InputKey::InputKey(Keyboard button):button(button)
{
	
}

bool CS230::InputKey::IsKeyDown() const
{
	return Engine::GetInput().IsKeyDown(button);
}

bool CS230::InputKey::IsKeyReleased() const
{
	return Engine::GetInput().IsKeyReleased(button);
}
