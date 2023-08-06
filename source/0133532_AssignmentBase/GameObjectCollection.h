#pragma once
#include <string>
#include <vector>
#include <unordered_set>

class GameObject;
class GameObjectCollection
{
public:
	GameObjectCollection() = delete; // disallow construction of class instance

	static void add(GameObject* go);
	static GameObject* add(std::string name);
	static GameObject* find(std::string name);
	static GameObject* findExistingObject();

	static void update(float deltaTime);
	static void render();
	static void dispose();


private:

	static std::unordered_set<GameObject*> gameObjects;
	static std::unordered_set<GameObject*> gameObjectsToAdd;
};
