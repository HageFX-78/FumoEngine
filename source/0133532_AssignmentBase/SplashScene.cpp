#include "SplashScene.h"

#include "Input.h"
#include "Time.h"
#include "SceneStateMachine.h"
#include "GameObjectCollection.h"

#include "TransformComponent.h"
#include "RendererComponent.h"
#include "ProgressBar.h"
#include "SpriteRenderer.h"


std::string SplashScene::getName() const {
	return "SplashScene";
}
void SplashScene::initialize() {
	go1 = new GameObject("SplashBar");
	go1->transform->setYPosition(-80);
	go1->addComponent<ProgressBar>();
	go1->getComponent<ProgressBar>()->setProgress(1.0f);
	go1->getComponent<ProgressBar>()->setBackDropColor(255.0f, 247.0f, 212.0f, 0.6f);
	go1->getComponent<ProgressBar>()->setBarColor(171.0f, 216.0f, 238.0f, 1.0f);


	go2 = new GameObject("Fumo");
	go2->addComponent<SpriteRenderer>();
	go2->transform->setScale(2.0f, 2.0f);
	go2->transform->setYPosition(80);

	std::cout << std::endl << "[ KEY ] Space to skip" << std::endl << std::endl;

}

void SplashScene::on_activate() {
	glClearColor(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1);
	time = 0;
}

void SplashScene::on_update(float deltaTime) {
	time += deltaTime;

	if (go1 != nullptr && time <= sceneSwitchTime)
		go1->getComponent<ProgressBar>()->setProgress(time / sceneSwitchTime);

	if (time >= sceneSwitchTime)
		SceneStateMachine::loadScene("FUMONIA");

	if (Input::getKeyDown(GLFW_KEY_SPACE))
	{
		SceneStateMachine::loadScene("FUMONIA");
	}
}

void SplashScene::on_render() {

}