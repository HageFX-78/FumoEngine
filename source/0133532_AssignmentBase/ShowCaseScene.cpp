#include "ShowCaseScene.h"

#include "Input.h"
#include "Time.h"
#include "SceneStateMachine.h"
#include "TransformComponent.h"
#include "RendererComponent.h"
#include "GameObjectCollection.h"


//Local variable and functions forward declared
GameObject* currentControlledGO;
void AddNewGameObject(std::string name = "DefaultObjectName");
void DeleteCurrentGameObject();
void AddComponentToCurrent(int compIndex);

std::string ShowCaseScene::getName() const {
	return "ShowCaseScene";
}

void ShowCaseScene::initialize() {
	std::cout << std::endl << "[ KEYS ] - - - - - - - - - - - - - -" << std::endl;
	std::cout << std::endl << "         [Z] to spawn gameobject" << std::endl;
	std::cout << std::endl << "         [X] to delete current gameobject and control another one if exists" << std::endl;
	std::cout << std::endl << "         [W][A][S][D] to move gameobject" << std::endl;
	std::cout << std::endl << "         [E] to rotate clockwise" << std::endl;
	std::cout << std::endl << "         [R] to rotate anti-clockwise" << std::endl;
	std::cout << std::endl << "         [Up] to scale up current object" << std::endl;
	std::cout << std::endl << "         [Down] to scale down current object" << std::endl;
	std::cout << std::endl << "         [1] to add TransformComponent to current object" << std::endl;
	std::cout << std::endl << "         [2] to add RendererComponent to current object" << std::endl;
	std::cout << std::endl << "         [LMB Click] to temporary change color to cyan" << std::endl;
	std::cout << std::endl << "         [LMB Release] to switch back" << std::endl << std::endl;
}

void ShowCaseScene::on_activate() {
	glClearColor(35.0f / 255.0f, 43.0f / 255.0f, 43.0f / 255.0f, 1);
}

void ShowCaseScene::on_update(float deltaTime) {
	if (currentControlledGO != nullptr)
	{
		if (Input::getMouseButtonDown(GLFW_MOUSE_BUTTON_1))
		{
			currentControlledGO->renderer->setRGB(0, 217.0f, 255.0f);
		}
		else if (Input::getMouseButtonUp(GLFW_MOUSE_BUTTON_1))
		{
			currentControlledGO->renderer->setRGB(255, 255, 255);
		}

		if (Input::getKey(GLFW_KEY_A))
		{
			currentControlledGO->transform->setXPosition(currentControlledGO->transform->getXPosition() - 100 * Time::getDeltaTime());
		}
		else if (Input::getKey(GLFW_KEY_D))
		{
			currentControlledGO->transform->setXPosition(currentControlledGO->transform->getXPosition() + 100 * Time::getDeltaTime());
		}
		if (Input::getKey(GLFW_KEY_W))
		{
			currentControlledGO->transform->setYPosition(currentControlledGO->transform->getYPosition() + 100 * Time::getDeltaTime());
		}
		else if (Input::getKey(GLFW_KEY_S))
		{
			currentControlledGO->transform->setYPosition(currentControlledGO->transform->getYPosition() - 100 * Time::getDeltaTime());
		}

		if (Input::getKey(GLFW_KEY_Q))
		{
			currentControlledGO->transform->setRotation(currentControlledGO->transform->getRotation() + 100 * Time::getDeltaTime());
		}
		else if (Input::getKey(GLFW_KEY_E))
		{
			currentControlledGO->transform->setRotation(currentControlledGO->transform->getRotation() - 100 * Time::getDeltaTime());
		}

		if (Input::getKey(GLFW_KEY_UP))
		{
			currentControlledGO->transform->setXScale(currentControlledGO->transform->getXScale() + 10 * Time::getDeltaTime());
			currentControlledGO->transform->setYScale(currentControlledGO->transform->getYScale() + 10 * Time::getDeltaTime());
		}
		else if (Input::getKey(GLFW_KEY_DOWN))
		{
			currentControlledGO->transform->setXScale(currentControlledGO->transform->getXScale() - 10 * Time::getDeltaTime());
			currentControlledGO->transform->setYScale(currentControlledGO->transform->getYScale() - 10 * Time::getDeltaTime());
		}
	}

	if (Input::getKeyDown(GLFW_KEY_Z))
	{
		AddNewGameObject();
	}
	else if (Input::getKeyDown(GLFW_KEY_X))
	{
		DeleteCurrentGameObject();
	}

	if (Input::getKeyDown(GLFW_KEY_1))
	{
		AddComponentToCurrent(0);
	}
	else if (Input::getKeyDown(GLFW_KEY_2))
	{
		AddComponentToCurrent(1);
	}
}

//Local logic functons
void AddNewGameObject(std::string name) {
	GameObject* newGO = new GameObject(name);

	if (currentControlledGO == nullptr)
		currentControlledGO = newGO;

}

void DeleteCurrentGameObject()
{
	currentControlledGO->destroy();

	GameObject* temp = GameObjectCollection::findExistingObject();//Find non destroyed objects in the scene
	if (temp != nullptr)
	{
		currentControlledGO = temp;
	}
	else
	{
		std::cout << " <!> No objects left in the scene" << std::endl;
		currentControlledGO = nullptr;
	}
}

void AddComponentToCurrent(int compIndex)
{
	if (currentControlledGO == nullptr)
	{
		std::cout << " <!> No objects to add to in the scene" << std::endl;
		return;
	}

	if (compIndex == 0)
	{
		currentControlledGO->addComponent<TransformComponent>();
	}
	else if (compIndex == 1)
	{
		currentControlledGO->addComponent<RendererComponent>();
	}
}