#include "SceneStateMachine.h"

namespace FumoEngine
{
	std::unordered_map<std::string, BaseScene*> SceneStateMachine::scenes;
	BaseScene* SceneStateMachine::currentScene;
	unsigned int SceneStateMachine::sceneIdCounter;

	void SceneStateMachine::loadScene(const unsigned int index)
	{
		if (index < sceneIdCounter)
		{
			// Retrieve the scene by index and activate it
			auto it = scenes.begin();
			std::advance(it, index);
			BaseScene* sceneToLoad = it->second;

			if (currentScene) currentScene->deactivate();
			currentScene = sceneToLoad;
			currentScene->activate();
		}
		else
		{
			std::cout << "<!> Invalid scene index. No scene loaded." << std::endl;
		}
	}

	void SceneStateMachine::loadScene(const std::string name)
	{

		auto it = scenes.find(name);

		if (it != scenes.end())
		{
			if (currentScene) currentScene->deactivate();
			currentScene = it->second;
			currentScene->activate();
			std::cout << "<*> Loaded scene with name: " << name << std::endl;
		}
		else
		{
			std::cout << "<!> Failed to load scene with name: " << name << std::endl;
		}
	}

	void SceneStateMachine::update(float deltaTime)
	{
		if (currentScene) currentScene->update(deltaTime);
	}

	void SceneStateMachine::render()
	{
		if (currentScene) currentScene->render();
	}

	void SceneStateMachine::dispose()
	{
		for (auto sceneInstance : scenes)
		{
			sceneInstance.second->deactivate();
			delete sceneInstance.second;
		}
		currentScene = nullptr;
	}

	std::string SceneStateMachine::getCurrentSceneName()
	{
		return (currentScene == nullptr) ? "No current scene!" : currentScene->getName();
	}
}

