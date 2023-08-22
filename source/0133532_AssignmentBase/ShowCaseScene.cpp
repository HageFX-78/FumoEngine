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
	go1->addComponent<SpriteRenderer>();

	go2 = new GameObject();
	go2->addComponent<SpriteRenderer>("../assets/alice.png");
}

void ShowCaseScene::on_activate() {
	glClearColor(35.0f / 255.0f, 43.0f / 255.0f, 43.0f / 255.0f, 1);
}

void ShowCaseScene::on_update(float deltaTime) {
	testVal += 50.0f * deltaTime;
	go1->transform->setRotation(testVal);
	
}

//Local logic functons
