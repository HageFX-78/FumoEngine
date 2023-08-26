#pragma once
#include <string>
#include <vector>
#include <unordered_set>

namespace FumoEngine
{
	class GameObject;
	/// <summary>
	/// The manager that oversees and update game objects every frame.
	/// </summary>
	class GameObjectCollection
	{
	public:
		GameObjectCollection() = delete; // disallow construction of class instance

		static void add(GameObject* go);
		static GameObject* add(std::string name);
		static GameObject* find(std::string name);

		/// <summary>
		/// A global function that can get all game objects in the scene, used by CircleCollider to check for collision between gameObjects.
		/// </summary>
		/// <returns></returns>
		static std::unordered_set<GameObject*> getCurrentSceneGameObjects();

		static void update(float deltaTime);
		static void render();
		static void dispose();
	private:

		static std::unordered_set<GameObject*> gameObjects;
		static std::unordered_set<GameObject*> gameObjectsToAdd;
	};
}

