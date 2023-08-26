#pragma once
#include "BaseScene.h"
#include <unordered_map>
#include <iostream>
#include <vector>

namespace FumoEngine
{
	/// <summary>
	/// A general manager of all scenes, used for switching and adding scenes to the game.
	/// </summary>
	class SceneStateMachine
	{
	public:
		SceneStateMachine() = delete; // disallow construction of class instance

		template<typename T, typename = typename std::enable_if<std::is_base_of<BaseScene, T>::value>::type>
		static T* addScene() {
			T* newScene = new T();

			auto pair = std::make_pair(newScene->getName(), newScene);
			std::pair < std::unordered_map<std::string, BaseScene*>::iterator, bool > result = scenes.insert(pair);

			if (result.second) {
				std::cout << "Scene successfully added " << newScene->getName() << std::endl;

				sceneIdCounter++;

				return newScene;
			}
			else {
				std::cout << "Failed to add scene " << newScene->getName() << std::endl;
				delete newScene;
				return nullptr;
			}
		}

		static void loadScene(const unsigned int index);
		static void loadScene(const std::string name);
		static void update(float deltaTime);
		static void render();
		static void dispose();

		static std::string getCurrentSceneName();

	private:
		// sceneMap
		static std::unordered_map<std::string, BaseScene*> scenes;

		// currentScene
		static BaseScene* currentScene;

		// sceneIdCounter
		static unsigned int sceneIdCounter;
	};
}

