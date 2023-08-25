#include "SplashScene.h"

#include "Input.h"
#include "Time.h"
#include "SceneStateMachine.h"
#include "TransformComponent.h"
#include "RendererComponent.h"
#include "GameObjectCollection.h"



std::string SplashScene::getName() const {
	return "SplashScene";
}
void SplashScene::initialize()  {
	go1 = new GameObject("TestLoadingBar");
	go1->transform->setXPosition(-200);
	go1->transform->setYPosition(-50);
	go1->transform->setXScale(0.0);
	go1->transform->setYScale(0.2f);


	go2 = new GameObject("Triangle");
	go2->transform->setYPosition(50);
	go2->transform->setRotation(270);

	std::cout << std::endl << "[ KEY ] Space to skip" << std::endl << std::endl;

}

void SplashScene::on_activate()  {
	glClearColor(35.0f / 255.0f, 43.0f / 255.0f, 43.0f / 255.0f, 1);
	time = 0;
}

void SplashScene::on_update(float deltaTime)  {
	time += deltaTime;

	if(go1 != nullptr && time < sceneSwitchTime)
		go1->transform->setXScale((4.0f/ sceneSwitchTime) * time);

	if (time > sceneSwitchTime)
		SceneStateMachine::loadScene("ShowCaseScene");

	if (Input::getKeyDown(GLFW_KEY_SPACE))
	{
		SceneStateMachine::loadScene("ShowCaseScene");
	}
}

void SplashScene::on_render()  {

}