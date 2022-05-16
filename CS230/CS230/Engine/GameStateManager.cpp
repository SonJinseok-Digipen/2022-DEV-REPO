#include "GameStateManager.h"
#include "GameState.h"
#include "Engine.h"
CS230::GameStateManager::GameStateManager():currGameState(nullptr),nextGameState(nullptr),state(State::START)
{

}

void CS230::GameStateManager::AddGameState(GameState& gameState)
{
	gameStates.push_back(&gameState);
}

void CS230::GameStateManager::Update(double dt)
{
	switch (state)
	{
	case State::START:
		if (gameStates.empty() == true)
		{
			Engine::GetLogger().LogError("Not enough GameStage");
			state = State::SHUTDOWN;
		}
		else
		{
			nextGameState = gameStates[0];
			state = State::LOAD;
		}
		break;
	case State::LOAD:
		currGameState = nextGameState;
		Engine::GetLogger().LogEvent("Load " + currGameState->GetName());
		currGameState->Load();
		Engine::GetLogger().LogEvent("Load Complete");
		state = State::UPDATE;
		break;

	case State::UPDATE:
		if ((currGameState != nextGameState) == true)
		{
			state = State::UNLOAD;
		}
		else
		{
			Engine::GetLogger().LogVerbose("Update " + currGameState->GetName());
			currGameState->Update(dt);
			currGameState->Draw();
		}
		break;
	case State::UNLOAD:
		Engine::GetLogger().LogEvent("Unload " + currGameState->GetName());
		currGameState->Unload();
		if (nextGameState == nullptr)
		{
			state = State::SHUTDOWN;
		}
		else
		{
			state = State::LOAD;
		}
		break;;
	case State::SHUTDOWN:
		state = State::EXIT;
		Engine::GetLogger().LogEvent("Engine Shutdown");
		break;

	case State::EXIT:
		break;
	}
}

void CS230::GameStateManager::SetNextState(int initState)
{
	nextGameState = gameStates[initState];
}

void CS230::GameStateManager::Shutdown()
{
	nextGameState = nullptr;
}

void CS230::GameStateManager::ReloadState()
{
	state = State::UNLOAD;
}
