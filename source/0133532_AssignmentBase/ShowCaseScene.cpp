#include "ShowCaseScene.h"

#include "Input.h"
#include "Time.h"
#include "SceneStateMachine.h"
#include "GameObjectCollection.h"
#include "SpriteRenderer.h"


//Local variable and functions forward declared
std::string ShowCaseScene::getName() const {
	return "ShowCaseScene";
}

void ShowCaseScene::initialize() {
	go1 = new GameObject();
	go1->addComponent<SpriteRenderer>("../assets/herta.png", Vector4(255,255,255,0.8f), Vector2(0, 0), Vector2(0.05f, 0.05f));

	go2 = new GameObject();
	go2->addComponent<SpriteRenderer>("../assets/alice.png", Vector4(255.0f, 255.0f, 255.0f, 0.1f), Vector2(0,0));
}

void ShowCaseScene::on_activate() {
	glClearColor(35.0f / 255.0f, 43.0f / 255.0f, 43.0f / 255.0f, 1);
}

void ShowCaseScene::on_update(float deltaTime) {
	testVal += 50.0f * deltaTime;
	go1->transform->setRotation(testVal);

	if (Input::getKey(GLFW_KEY_A))
	{
		go1->transform->setXScale(go1->transform->getXScale() + 1.0f * deltaTime);
	}
	else if (Input::getKey(GLFW_KEY_D))
	{
		go1->transform->setXScale(go1->transform->getXScale() - 1.0f * deltaTime);
	}
	if (Input::getKey(GLFW_KEY_W))
	{
		go1->transform->setYScale(go1->transform->getYScale() + 1.0f * deltaTime);
	}
	else if (Input::getKey(GLFW_KEY_S))
	{
		go1->transform->setYScale(go1->transform->getYScale() - 1.0f * deltaTime);
	}

	if (Input::getKey(GLFW_KEY_Q))
	{
		std::cout << go1->getComponent<SpriteRenderer>()->getSize().data[0] << std::endl;
	}
}

//Local logic functons
