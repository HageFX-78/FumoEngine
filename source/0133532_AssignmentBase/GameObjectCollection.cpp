#include "GameObjectCollection.h"
#include "GameObject.h"
#include <iostream>

std::unordered_set<GameObject*> GameObjectCollection::gameObjects;
std::unordered_set<GameObject*> GameObjectCollection::gameObjectsToAdd;

void GameObjectCollection::add(GameObject* go)
{
	gameObjectsToAdd.insert(go);
}

GameObject* GameObjectCollection::add(std::string name)
{
	GameObject* go = new GameObject(name);
	gameObjectsToAdd.insert(go);
	return go;
}

GameObject* GameObjectCollection::find(std::string name)
{
	for (auto go : gameObjects)
	{
		if (go->getName() == name)
		{
			std::cout << "Found : " << name << std::endl;
			return go;
		}
	}
	std::cout << "Cant find the object " << name << std::endl;
	return nullptr;
}

//Find any object that is in the scene, for showcase purpose
GameObject* GameObjectCollection::findExistingObject()
{
	for (auto go : gameObjects)
	{
		if (!go->shouldDestroy())
		{
			return go;
		}
	}
	return nullptr;
}

void GameObjectCollection::update(float deltaTime)
{

	for (auto it = gameObjects.begin(); it != gameObjects.end();)
	{
		if ((*it)->shouldDestroy())
		{
			std::cout << "<?> Deleting game object: " << (*it)->getName() << std::endl;
			delete* it;
			it = gameObjects.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (gameObjectsToAdd.size() > 0)
	{
		//Run all awake functions before running start
		for (auto go : gameObjectsToAdd)
		{
			go->runComponentAwake();
		}
		for (auto go : gameObjectsToAdd)
		{		
			go->runComponentStart();
			gameObjects.insert(go);
		}
		
		gameObjectsToAdd.clear();
	}
	
	for (auto go : gameObjects)
	{
		go->runComponentUpdate(deltaTime);
	}
	
}

void GameObjectCollection::render()
{
	for (auto go : gameObjects)
	{
		go->runComponentRender();
	}
}

void GameObjectCollection::dispose()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
	for (auto go : gameObjectsToAdd)
	{
		delete go;
	}

	gameObjects.clear();
	gameObjectsToAdd.clear();
}