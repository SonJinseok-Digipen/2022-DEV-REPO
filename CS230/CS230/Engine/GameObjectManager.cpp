#include"GameObjectManager.h"
#include"TransformMatrix.h"
#include"GameObject.h"
void CS230::GameObjectManager::Add(GameObject* obj)
{
	gameObjects.push_back(obj);
}

void CS230::GameObjectManager::Unload()
{
	for (GameObject* obj : gameObjects)
	{
		delete obj;
	}
	gameObjects.clear();
}

void CS230::GameObjectManager::UpdateAll(double dt)
{
	for (GameObject* obj : gameObjects)
	{
		obj->Update(dt);
	}
}

void CS230::GameObjectManager::DrawAll(math::TransformMatrix& cameraMatrix)
{
	for (GameObject* obj : gameObjects)
	{
		obj->Draw(cameraMatrix);
	}
}


