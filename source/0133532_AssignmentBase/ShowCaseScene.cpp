#define _USE_MATH_DEFINES
#include <cmath>

#include "ShowCaseScene.h"

#include "Input.h"
#include "Time.h"
#include "SceneStateMachine.h"
#include "GameObjectCollection.h"

#include "SpriteRenderer.h"
#include "ProgressBar.h"
#include "CircleCollider.h"

//Local variable and functions forward declared
std::string ShowCaseScene::getName() const {
	return "ShowCaseScene";
}

void ShowCaseScene::initialize() {
	player = new GameObject();
	player->addComponent<SpriteRenderer>("../assets/player.png", Vector4(0.0f, 255.0f, 0.0f, 0.5f), Vector2(0, 0), Vector2(0.05f, 0.05f));
	player->addComponent<CircleCollider>(false, 15.0f);

	go1 = new GameObject();
	go1->addComponent<SpriteRenderer>("../assets/herta.png", Vector4(255.0f, 255.0f, 255.0f, 0.5f));
	go1->getComponent<SpriteRenderer>()->setSize(0.05f, 0.05f);
	go1->addComponent<CircleCollider>();

	/*go2 = new GameObject();
	go2->addComponent<SpriteRenderer>("../assets/herta.png");
	go2->getComponent<SpriteRenderer>()->setSize(0.05f, 0.05f);*/

	/*progressbar = new GameObject();
	progressbar->addComponent<ProgressBar>();
	progressbar->getComponent<ProgressBar>()->setPivot(-progressbar->getComponent<ProgressBar>()->getBarLength()/2, 0);*/
}

void ShowCaseScene::on_activate() {
	glClearColor(35.0f / 255.0f, 43.0f / 255.0f, 43.0f / 255.0f, 1);
}

void ShowCaseScene::on_update(float deltaTime) {

	if (player)
	{
		float angle = std::atan2(Input::getMousePositionCentered().y - player->transform->getYPosition(),
								Input::getMousePositionCentered().x - player->transform->getXPosition());

		// Convert the angle to degrees
		float angleInDegrees = angle * (180.0f / M_PI);

		if (angleInDegrees < 0.0f)
		{
			angleInDegrees += 360.0f;
		}

		player->transform->setRotation(angleInDegrees);
	}

	if (player->getComponent<CircleCollider>()->checkCircleCollision(*go1->getComponent<CircleCollider>()))
	{
		if (!player->getComponent<CircleCollider>()->getIsColliding())
		{
			std::cout << " Just Collided! " << std::endl;
			player->getComponent<CircleCollider>()->setIsColliding(true);
		}	
	}
	else
	{
		if (player->getComponent<CircleCollider>()->getIsColliding())
		{
			std::cout << " Collider Exited " << std::endl;
			player->getComponent<CircleCollider>()->setIsColliding(false);
		}
	}



	//  - - - -  Scene Input handling
	if (Input::getKey(GLFW_KEY_D))
	{
		player->transform->setXPosition(player->transform->getXPosition() + 100.0f * deltaTime);
	}
	else if (Input::getKey(GLFW_KEY_A))
	{
		player->transform->setXPosition(player->transform->getXPosition() - 100.0f * deltaTime);
	}
	if (Input::getKey(GLFW_KEY_W))
	{
		player->transform->setYPosition(player->transform->getYPosition() + 100.0f * deltaTime);
	}
	else if (Input::getKey(GLFW_KEY_S))
	{
		player->transform->setYPosition(player->transform->getYPosition() - 100.0f * deltaTime);
	}

	if (Input::getKey(GLFW_KEY_Q))
	{
		go1->destroy();
	}
}

//Local logic functons
