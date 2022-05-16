#include "Engine.h"
Engine::Engine() :
#ifdef _DEBUG				
	logger(CS230::Logger::Severity::Debug, true),lastTick(std::chrono::system_clock::now()),frameCount(0)
#else 						
	logger(CS230::Logger::Severity::Event, false),lastTick(std::chrono::system_clock::now()), frameCount(0)
#endif
{}
Engine::~Engine() {}
void Engine::Init(std::string windowName)
{
	logger.LogEvent("Engine Init");
	window.Init(windowName);
	fpsCalcTime = lastTick;
}

void Engine::Shutdown()
{
	gameStateManager.Shutdown();
}

void Engine::Update()
{

	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	double dt = std::chrono::duration<double>(now - lastTick).count();
	if (dt >= 1 / Engine::Target_FPS)
	{
		logger.LogVerbose("Engine Update");
		gameStateManager.Update(dt);
		input.Update();
		window.Update();
		frameCount++;
		lastTick = now;
		if (frameCount >= FPS_IntervalFrameCount)
		{
			double averageTime = std::chrono::duration<double>(lastTick - fpsCalcTime).count();
			double averageFrameRate = frameCount / averageTime;
			fpsCalcTime = lastTick;
			Engine::GetLogger().LogEvent("FPS: " + std::to_string(averageFrameRate));
			frameCount = 0;
		}
		

	}









	

}

bool Engine::HasGameEnded()
{
	return gameStateManager.HasGameEnded();
}

 

